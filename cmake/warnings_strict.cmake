set(_xft_warns_common
  -Wall -Wextra -Wpedantic
  -Wstrict-aliasing
  -Wshadow
  -Waddress
  -Wattributes
  -Wredundant-decls
  -Wstrict-prototypes
  -Wmissing-prototypes
  -Wold-style-definition
  -Wnull-dereference
  -Wundef
  -Wformat-security
  -Wformat=2
  -Wformat-nonliteral
  -Wwrite-strings
  -Wuninitialized
  -Wpointer-arith
  -Wunused
  -Wtautological-compare
  -Wvla
  -Wignored-qualifiers
  -Wnonnull
  -Winfinite-recursion
  -Wimplicit
  -Wimplicit-fallthrough
  -Wmissing-braces
  -Wmissing-include-dirs
  -Wparentheses
  -Wshift-negative-value
  -Wmisleading-indentation
  -Wfloat-equal
  -Wdangling-else
  -Wmissing-noreturn
  -Wchar-subscripts
  -Wsequence-point
  -Wbool-operation
  -Wunreachable-code
  -Wformat-overflow
  -Wformat-truncation
  -Wcast-function-type)

set(_xft_warns_clang
  -Wbitwise-instead-of-logical
  -Wnull-pointer-arithmetic
  -Wcast-function-type-strict
  -Wambiguous-ellipsis
  -Wambiguous-macro
  -Wassume
  -Wpessimizing-move
  -Wgnu-union-cast
  -Wlanguage-extension-token
  -Wgnu-statement-expression-from-macro-expansion
  -Wbounds-safety-counted-by-elt-type-unknown-size
  -Wcast-function-type-mismatch
  -Wc99-compat
  -Wbool-conversions
  -Wbitfield-enum-conversion
  -Warray-bounds-pointer-arithmetic
  -Wloop-analysis
  -Wcomma
  -Wover-aligned
  -Wconditional-uninitialized
  -Wimplicit-float-conversion
  -Wimplicit-int-conversion
  -Wshorten-64-to-32
  -Wstring-concatenation
  -Wunused-but-set-parameter
  -Wsizeof-array-div
  -Wtautological-constant-in-range-compare
  -Wno-extra-semi-stmt
  -Wthread-safety
  -Wdangling)

set(_xft_warns_gcc
  -Wshift-overflow
  -Wunused-but-set-parameter
  -Wstrict-overflow=5
  -Wmissing-attributes
  -Wmismatched-dealloc
  -Wtrivial-auto-var-init
  -Wuse-after-free=3
  -Wuseless-cast
  -fstrict-flex-arrays=3
  -Wsuggest-attribute=pure
  -Wsuggest-attribute=const
  -Wsuggest-attribute=noreturn
  -Wsuggest-attribute=malloc
  -Wsuggest-attribute=format
  -Wsuggest-attribute=cold
  -Walloc-size
  -Walloca
  -Warith-conversion
  -Warray-bounds=2
  -Warray-compare
  -Warray-parameter
  -Wattribute-alias=2
  -Wduplicated-branches
  -Wduplicated-cond
  -Wzero-length-bounds
  -Wunsafe-loop-optimizations
  -Wtype-limits
  -Wdangling-pointer
  -Wsizeof-pointer-memaccess
  -Wpacked
  -Wrestrict
  -Winit-self
  -Wlogical-op
  -Wstringop-overflow=4
  -Wstringop-truncation)

if(XFT_LIBC)
  list(PREPEND _xft_warns_gcc -Whardened)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(_xft_warns_raw ${_xft_warns_common} ${_xft_warns_clang})
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(_xft_warns_raw ${_xft_warns_common} ${_xft_warns_gcc})
else()
  message(WARNING "xft: unknown compiler ${CMAKE_C_COMPILER_ID}, using common warnings only")
  set(_xft_warns_raw ${_xft_warns_common})
endif()

include(CheckCCompilerFlag)
set(CMAKE_REQUIRED_FLAGS -Werror)
set(CMAKE_REQUIRED_QUIET ON)

set(XFT_WARNS "")
foreach(f IN LISTS _xft_warns_raw)
  string(MAKE_C_IDENTIFIER "XFT_WARN_OK_${f}" _var)
  check_c_compiler_flag("${f}" ${_var})
  if(${_var})
    list(APPEND XFT_WARNS ${f})
  endif()
endforeach()

unset(CMAKE_REQUIRED_FLAGS)
unset(CMAKE_REQUIRED_QUIET)

list(LENGTH _xft_warns_raw _n_raw)
list(LENGTH XFT_WARNS      _n_ok)
message(STATUS "xft: strict warnings, ${_n_ok}/${_n_raw} accepted")

list(APPEND XFT_WARNS -Werror)
