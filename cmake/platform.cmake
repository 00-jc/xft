# target arch / os and host cache geometry

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64)$")
  set(XFT_TARGET_ARCH x86_64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64)$")
  set(XFT_TARGET_ARCH aarch64)
else()
  set(XFT_TARGET_ARCH unknown)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(XFT_WIN32 ON)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(XFT_WIN32 OFF)
else()
  message(FATAL_ERROR "xft: only linux and windows are supported")
endif()

set(XFT_LLC 0)
if(NOT CMAKE_CROSSCOMPILING)
  find_program(XFT_GETCONF getconf)
endif()
if(CMAKE_HOST_WIN32 AND NOT CMAKE_CROSSCOMPILING)
  find_program(XFT_POWERSHELL NAMES pwsh powershell)
  if(XFT_POWERSHELL)
    execute_process(
      COMMAND
        ${XFT_POWERSHELL} -NoProfile -NonInteractive -Command
        "(Get-CimInstance Win32_Processor | Measure-Object -Property L3CacheSize -Maximum).Maximum"
      OUTPUT_VARIABLE _xft_llc_kib
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
    )
    if(_xft_llc_kib MATCHES "^[0-9]+$")
      math(EXPR XFT_LLC "${_xft_llc_kib} * 1024")
    endif()
  endif()
elseif(XFT_GETCONF)
  execute_process(
    COMMAND ${XFT_GETCONF} LEVEL3_CACHE_SIZE
    OUTPUT_VARIABLE _xft_llc
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  if(_xft_llc MATCHES "^[0-9]+$")
    set(XFT_LLC ${_xft_llc})
  endif()
endif()

# cross builds (and hosts with no l3 to report) detect nothing; the streaming
# paths still need a threshold, so fall back to the XFT_LLC_SIZE default
if(XFT_LLC EQUAL 0)
  set(XFT_LLC 16777216)
endif()
