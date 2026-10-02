# the xft library builds (main + the variants the harnesses need), the
# subprojects built once per variant, and the install rules.
# needs sources.cmake and flags.cmake

include(GNUInstallDirs)

# headers only xft and its in-tree users (subprojects, harnesses) may see;
# never installed
set(XFT_INTERNAL_DIR ${PROJECT_SOURCE_DIR}/src/internal)

function(xft_srcs out libc)
  set(_s "")
  foreach(m IN LISTS MODULES)
    list(APPEND _s ${SRCS_${m}})
  endforeach()
  foreach(a IN LISTS XFT_BACKEND_ARCHS)
    list(APPEND _s ${SRCS_ARCH_${a}})
  endforeach()
  if(XFT_WIN64)
    list(APPEND _s ${SRCS_WIN64})
    if(XFT_RT)
      if(libc)
        list(APPEND _s ${SRCS_RT_ENTRY_libc})
      else()
        list(APPEND _s ${SRCS_RT_ENTRY_win64})
      endif()
    endif()
  elseif(libc)
    list(APPEND _s ${SRCS_LIBC})
    if(XFT_RT)
      list(APPEND _s ${SRCS_RT_ENTRY_libc})
    endif()
  else()
    foreach(a IN LISTS XFT_BACKEND_ARCHS)
      list(APPEND _s ${SRCS_FREESTANDING_${a}})
      if(XFT_RT)
        list(APPEND _s ${SRCS_RT_ENTRY_${a}})
      endif()
    endforeach()
  endif()
  set(${out} "${_s}" PARENT_SCOPE)
endfunction()

# stack clash protection probes the stack in page steps; freestanding win64
# builds drop the probes (-mno-stack-arg-probe, no __chkstk), every other
# flavor keeps them
function(xft_stack_clash_flags out libc)
  if(libc OR NOT XFT_WIN64)
    set(${out} "${CFLAGS_STACK_CLASH}" PARENT_SCOPE)
  else()
    set(${out} "" PARENT_SCOPE)
  endif()
endfunction()

function(xft_add_lib name)
  cmake_parse_arguments(L "LIBC;SANITIZE;LTO" "" "" ${ARGN})
  if(L_SANITIZE)
    set(L_LIBC ON)
    set(L_LTO OFF)
  endif()

  xft_srcs(_srcs ${L_LIBC})
  add_library(${name} STATIC ${_srcs})

  set_target_properties(
    ${name}
    PROPERTIES
      OUTPUT_NAME ${name}
      PREFIX "lib"
      C_VISIBILITY_PRESET hidden
      POSITION_INDEPENDENT_CODE OFF
      XFT_IS_LIBC "${L_LIBC}"
  )

  target_include_directories(
    ${name}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
  )
  target_include_directories(${name} PRIVATE ${XFT_INTERNAL_DIR})

  target_compile_definitions(${name} PRIVATE ${XFT_DEFINES_PRIVATE})
  target_compile_options(
    ${name}
    PRIVATE ${CFLAGS} ${XFT_WARNS} $<$<CONFIG:Release,RelWithDebInfo,>:-O3>
  )

  if(NOT XFT_RT)
    target_compile_definitions(${name} PUBLIC XFT_NO_RT)
  endif()

  # the win64 syscall backend calls into these with or without a libc
  if(XFT_WIN64)
    target_link_libraries(${name} INTERFACE kernel32 ntdll shell32)
  endif()

  xft_stack_clash_flags(_clash "${L_LIBC}")
  target_compile_options(${name} PRIVATE ${_clash})

  if(L_LIBC)
    target_compile_definitions(${name} PUBLIC XFT_REQUIRE_LIBC)
    if(NOT XFT_WIN64)
      target_compile_definitions(${name} PUBLIC _GNU_SOURCE)
    endif()
    target_compile_options(${name} PRIVATE ${CFLAGS_HOSTED})
  else()
    target_compile_options(${name} PRIVATE ${CFLAGS_FREESTANDING})
    target_compile_options(${name} INTERFACE ${CFLAGS_FREESTANDING})
    target_link_options(${name} INTERFACE -nostdlib -static)
    if(XFT_WIN64 AND XFT_RT)
      if(MSVC)
        target_link_options(${name} INTERFACE /ENTRY:_start)
      else()
        target_link_options(${name} INTERFACE -Wl,-e,_start)
      endif()
    endif()
  endif()

  if(L_SANITIZE)
    target_compile_options(
      ${name}
      PUBLIC ${XFT_SAN_FLAGS} ${CFLAGS_STACK_CHECK}
    )
    target_link_options(${name} PUBLIC ${XFT_SAN_FLAGS})
  endif()

  if(L_LTO)
    if(XFT_IPO_OK)
      set_property(TARGET ${name} PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
      target_link_options(${name} INTERFACE ${XFT_LTO_LINK_OPTIONS})
    else()
      message(WARNING "xft: LTO unavailable: ${XFT_IPO_MSG}")
    endif()
  endif()
endfunction()

set(_xft_main_args "")
if(XFT_LIBC)
  list(APPEND _xft_main_args LIBC)
endif()
if(XFT_SANITIZE)
  list(APPEND _xft_main_args SANITIZE)
endif()
if(XFT_LTO)
  list(APPEND _xft_main_args LTO)
endif()

xft_add_lib(xft ${_xft_main_args})
add_library(xft::xft ALIAS xft)

# the extra xft builds the harnesses link against; subprojects get built
# once per variant so a harness never mixes flavors
set(XFT_VARIANTS xft)

if(XFT_BUILD_TESTS OR XFT_BUILD_FUZZ)
  if(XFT_SANITIZE)
    set(XFT_HARNESS_LIB xft) # main lib is already the sanitized hosted build
  else()
    xft_add_lib(xft-san SANITIZE)
    set(XFT_HARNESS_LIB xft-san)
    list(APPEND XFT_VARIANTS xft-san)
  endif()
endif()

if(XFT_BUILD_BENCH)
  if(XFT_LIBC AND NOT XFT_SANITIZE)
    set(XFT_LIBC_BENCH_LIB xft)
  else()
    set(_xft_libc_bench_args LIBC)
    if(XFT_LTO)
      list(APPEND _xft_libc_bench_args LTO)
    endif()
    xft_add_lib(xft-libc ${_xft_libc_bench_args})
    set(XFT_LIBC_BENCH_LIB xft-libc)
    list(APPEND XFT_VARIANTS xft-libc)
  endif()
  # benchmarks are never sanitized: with XFT_SANITIZE the main lib is, so
  # they take xft-libc, the same hosted flavor without the sanitizers
  if(XFT_SANITIZE)
    set(XFT_BENCH_LIB xft-libc)
  else()
    set(XFT_BENCH_LIB xft)
  endif()
endif()

# xft_add_subproject(<name> SOURCES <src>... [DEPS <subproject>...])
#   builds <variant>-<name> for every xft variant, with the variant's flavor,
#   sanitizers and LTO, exporting the subproject's include/ dir
function(xft_add_subproject name)
  cmake_parse_arguments(S "" "" "SOURCES;DEPS" ${ARGN})
  list(TRANSFORM S_SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
  foreach(v IN LISTS XFT_VARIANTS)
    set(t ${v}-${name})
    add_library(${t} STATIC ${S_SOURCES})
    set_target_properties(
      ${t}
      PROPERTIES
        OUTPUT_NAME ${t}
        PREFIX "lib"
        C_VISIBILITY_PRESET hidden
        POSITION_INDEPENDENT_CODE OFF
    )
    target_include_directories(
      ${t}
      PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_include_directories(
      ${t}
      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/internal ${XFT_INTERNAL_DIR}
    )
    foreach(d IN LISTS S_DEPS)
      target_link_libraries(${t} PUBLIC ${v}-${d})
    endforeach()
    target_link_libraries(${t} PUBLIC ${v})
    target_compile_definitions(${t} PRIVATE ${XFT_DEFINES_PRIVATE})
    target_compile_options(
      ${t}
      PRIVATE ${CFLAGS} ${XFT_WARNS} $<$<CONFIG:Release,RelWithDebInfo,>:-O3>
    )
    get_target_property(_libc ${v} XFT_IS_LIBC)
    set_target_properties(${t} PROPERTIES XFT_IS_LIBC "${_libc}")
    if(_libc)
      target_compile_options(${t} PRIVATE ${CFLAGS_HOSTED})
    endif()
    xft_stack_clash_flags(_clash "${_libc}")
    target_compile_options(${t} PRIVATE ${_clash})
    get_target_property(_ipo ${v} INTERPROCEDURAL_OPTIMIZATION)
    if(_ipo)
      set_property(TARGET ${t} PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
    endif()
  endforeach()
  install(TARGETS xft-${name} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endfunction()

# perf and tailor sit on perf_event_open: linux only, their headers #error
# anywhere else
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_subdirectory(subprojects/perf)
  add_subdirectory(subprojects/tailor)
endif()

install(TARGETS xft ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
