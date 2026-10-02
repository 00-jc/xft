# unit tests, fuzz targets and benchmarks. needs variants.cmake

set(FUZZ_TARGETS
  fuzz_mem fuzz/mem_fuzz.c
  fuzz_vec fuzz/vec_fuzz.c
  fuzz_map fuzz/map_fuzz.c)

set(BENCH_TARGETS
  memcpy_bench
  memcpy_stream_bench
  memmove_bench
  memset_bench
  memset_stream_bench
  strlen_bench
  gpa_bench
  arena_bench
  vec_bench)

function(xft_add_harness name)
  cmake_parse_arguments(H "" "LIB" "SOURCES;INCLUDES" ${ARGN})
  add_executable(${name} ${H_SOURCES})
  target_link_libraries(${name} PRIVATE ${H_LIB})
  target_include_directories(${name} PRIVATE ${H_INCLUDES} ${XFT_INTERNAL_DIR})
  target_compile_definitions(${name} PRIVATE ${XFT_DEFINES_PRIVATE})
  target_compile_options(
    ${name}
    PRIVATE ${CFLAGS} ${XFT_WARNS} $<$<CONFIG:Release,RelWithDebInfo,>:-O3>
  )
endfunction()

if(XFT_BUILD_TESTS OR XFT_BUILD_FUZZ)
  enable_testing()
endif()

if(XFT_BUILD_TESTS)
  xft_add_harness(
    tests
    LIB ${XFT_HARNESS_LIB}
    SOURCES ${SRCS_TEST}
    INCLUDES tests/include
  )
  add_test(NAME tests COMMAND tests)
  set_tests_properties(tests PROPERTIES LABELS unit)
endif()

if(XFT_BUILD_FUZZ)
  add_custom_target(fuzz COMMENT "fuzz targets")
  while(FUZZ_TARGETS)
    list(POP_FRONT FUZZ_TARGETS _xft_name _xft_src)
    xft_add_harness(
      ${_xft_name}
      LIB ${XFT_HARNESS_LIB}
      SOURCES ${_xft_src}
      INCLUDES fuzz
    )
    add_dependencies(fuzz ${_xft_name})
    add_test(NAME ${_xft_name} COMMAND ${_xft_name})
    set_tests_properties(${_xft_name} PROPERTIES LABELS fuzz)
  endwhile()
endif()

if(XFT_BUILD_BENCH)
  add_custom_target(bench COMMENT "benchmarks")
  set(_xft_bench_run "")
  foreach(_xft_b IN LISTS BENCH_TARGETS)
    xft_add_harness(
      ${_xft_b}
      LIB ${XFT_BENCH_LIB}-tailor
      SOURCES ${SRCS_BENCH_${_xft_b}}
      INCLUDES bench/include
    )
    add_dependencies(bench ${_xft_b})
    list(APPEND _xft_bench_run COMMAND $<TARGET_FILE:${_xft_b}>)
  endforeach()
  xft_add_harness(
    libc_bench
    LIB ${XFT_LIBC_BENCH_LIB}-tailor
    SOURCES ${SRCS_BENCH_libc_bench}
    INCLUDES bench/include
  )
  target_compile_options(libc_bench PRIVATE ${CFLAGS_HOSTED} -fno-builtin)
  add_dependencies(bench libc_bench)
  list(APPEND _xft_bench_run COMMAND $<TARGET_FILE:libc_bench>)

  add_custom_target(
    run-bench
    ${_xft_bench_run}
    DEPENDS ${BENCH_TARGETS} libc_bench
    COMMENT "running benchmarks"
    USES_TERMINAL
    VERBATIM
  )
endif()
