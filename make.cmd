@echo off

setlocal

set NACL_SDK_ROOT=c:\nacl_sdk

:: NACL_SDK_ROOT must be set.
if not defined NACL_SDK_ROOT (
  echo Error: NACL_SDK_ROOT is not set.
  echo Please set NACL_SDK_ROOT to the full path of the Native Client SDK.
  echo For example:
  echo set NACL_SDK_ROOT=D:\nacl_sdk
  goto end
)

:: NACL_TARGET_PLATFORM is really the name of a folder with the base dir -
:: usually NACL_SDK_ROOT - within which the toolchain for the target platform
:: are found.
:: Replace the platform with the name of your target platform.  For example, to
:: build applications that target the pepper_15 API, set
::   NACL_TARGET_PLATFORM=pepper_15
if not defined NACL_TARGET_PLATFORM (
  set NACL_TARGET_PLATFORM=pepper_15
)

set NACL_PLATFORM_DIR=%NACL_SDK_ROOT%\%NACL_TARGET_PLATFORM%

if "%1"=="clean" (
    scons -c
    goto :end
)

if "%1"=="deploy" (
    scons osoasso_x86_32.nexe osoasso_x86_64.nexe
    %NACL_PLATFORM_DIR%\toolchain\win_x86_newlib\bin\i686-nacl-strip.exe osoasso_x86_32.nexe
    %NACL_PLATFORM_DIR%\toolchain\win_x86_newlib\bin\x86_64-nacl-strip.exe osoasso_x86_64.nexe
    copy /y osoasso_x86_??.nexe osoasso-gwt\war
    goto :end
)

if "%1"=="deploy32" (
    scons osoasso_x86_32.nexe
    %NACL_PLATFORM_DIR%\toolchain\win_x86_newlib\bin\i686-nacl-strip.exe osoasso_x86_32.nexe
    copy /y osoasso_x86_32.nexe osoasso-gwt\war
    goto :end
)

if "%1"=="deploy64" (
    scons osoasso_x86_64.nexe
    %NACL_PLATFORM_DIR%\toolchain\win_x86_newlib\bin\x86_64-nacl-strip.exe osoasso_x86_64.nexe
    copy /y osoasso_x86_64.nexe osoasso-gwt\war
    goto :end
)

scons %*

:end
