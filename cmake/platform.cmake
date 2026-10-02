# target arch / os and host cache geometry

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64)$")
  set(XFT_ARCH x86_64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64)$")
  set(XFT_ARCH aarch64)
else()
  set(XFT_ARCH unknown)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(XFT_WIN64 ON)
else()
  set(XFT_WIN64 OFF)
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
