cmake_minimum_required(VERSION 3.21)
project(xft VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)

include(cmake/platform.cmake)	# XFT_ARCH, XFT_WIN64, XFT_LLC
include(cmake/options.cmake)	# options, validation, XFT_FLAVOR
include(cmake/sources.cmake)	# SRCS_* lists
include(cmake/flags.cmake)		# CFLAGS*, XFT_WARNS, toolchain, LTO
include(cmake/variants.cmake)	# xft libs, subprojects, install
include(cmake/harness.cmake)	# tests, fuzz, bench
include(cmake/tools.cmake)		# analyze
