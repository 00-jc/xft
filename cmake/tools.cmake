# static analysis of the main lib's sources, with the flags it builds with.
# needs variants.cmake

xft_srcs(_xft_analyze_srcs ${XFT_LIBC})
list(TRANSFORM _xft_analyze_srcs PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(_xft_analyze_flags
  ${CMAKE_C23_EXTENSION_COMPILE_OPTION}
  ${CFLAGS}
  ${XFT_WARNS}
  -I${CMAKE_CURRENT_SOURCE_DIR}/include
  -I${XFT_INTERNAL_DIR})
foreach(_xft_d IN LISTS XFT_DEFINES_PUBLIC XFT_DEFINES_PRIVATE)
  list(APPEND _xft_analyze_flags "-D${_xft_d}")
endforeach()
if(XFT_LIBC)
  list(APPEND _xft_analyze_flags ${CFLAGS_HOSTED})
else()
  list(APPEND _xft_analyze_flags ${CFLAGS_FREESTANDING})
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(_xft_analyze_dir ${CMAKE_CURRENT_BINARY_DIR}/analyze)
  file(MAKE_DIRECTORY ${_xft_analyze_dir})
  add_custom_target(
    analyze
    COMMAND
      ${CMAKE_C_COMPILER} ${_xft_analyze_flags} -fanalyzer -c
      ${_xft_analyze_srcs}
    WORKING_DIRECTORY ${_xft_analyze_dir}
    COMMENT "static analysis (${XFT_FLAVOR}, gcc -fanalyzer)"
    VERBATIM
  )
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
  add_custom_target(
    analyze
    COMMAND
      ${CMAKE_C_COMPILER} ${_xft_analyze_flags} --analyze --analyzer-output
      text ${_xft_analyze_srcs}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "static analysis (${XFT_FLAVOR}, clang --analyze)"
    VERBATIM
  )
else()
  message(STATUS "xft: no analyze target for ${CMAKE_C_COMPILER_ID}")
endif()
