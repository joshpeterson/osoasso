@echo off

setlocal

set NACL_SDK_ROOT=c:\Users\Josh\Documents\development\nacl_sdk\pepper_33
set TOOLCHAIN=newlib

if "%1"=="pnacl" (
    set TOOLCHAIN=pnacl
)

if "%2"=="pnacl" (
    set TOOLCHAIN=pnacl
)

set CONFIG=Release
set NACL_ARCH=x86_32

:: NACL_SDK_ROOT must be set.
if not defined NACL_SDK_ROOT (
  echo Error: NACL_SDK_ROOT is not set.
  echo Please set NACL_SDK_ROOT to the full path of the Native Client SDK.
  echo For example:
  echo set NACL_SDK_ROOT=D:\nacl_sdk
  goto end
)

if "%1"=="test" (
    %NACL_SDK_ROOT%\tools\make -f Makefile_test
    if "%TOOLCHAIN%"=="pnacl" (
        %NACL_SDK_ROOT%\toolchain\win_pnacl\bin\pnacl-translate -arch x86-32 %TOOLCHAIN%\Release\osoasso_test.pexe -o %TOOLCHAIN%\Release\osoasso_test_x86_32.nexe
    )
    %NACL_SDK_ROOT%\tools\sel_ldr.py %TOOLCHAIN%\Release\osoasso_test_x86_32.nexe
    goto :end
)

if "%1"=="stress" (
    %NACL_SDK_ROOT%\tools\make -f Makefile_stress_test
    if "%TOOLCHAIN%"=="pnacl" (
        %NACL_SDK_ROOT%\toolchain\win_pnacl\bin\pnacl-translate -arch x86-32 %TOOLCHAIN%\Release\osoasso_stress_test.pexe -o %TOOLCHAIN%\Release\osoasso_stress_test_x86_32.nexe
    )
    %NACL_SDK_ROOT%\tools\sel_ldr.py %TOOLCHAIN%\Release\osoasso_stress_test_x86_32.nexe
    goto :end
)

if "%1"=="deploy" (
    set NACL_ARCH=
)

%NACL_SDK_ROOT%\tools\make

if "%1"=="deploy" (
    if "%TOOLCHAIN%"=="pnacl" (
        copy /y %TOOLCHAIN%\Release\osoasso.pexe osoasso-gwt\war
    ) else (
        copy /y %TOOLCHAIN%\Release\osoasso_x86_32.nexe osoasso-gwt\war
        copy /y %TOOLCHAIN%\Release\osoasso_x86_64.nexe osoasso-gwt\war
        copy /y %TOOLCHAIN%\Release\osoasso_arm.nexe osoasso-gwt\war
    )
    copy /y %TOOLCHAIN%\Release\osoasso.nmf osoasso-gwt\war
    copy /y favicon.ico osoasso-gwt\war
    goto :end
)

if "%1"=="deploy32" (
    copy /y %TOOLCHAIN%\Release\osoasso_x86_32.nexe osoasso-gwt\war
    copy /y %TOOLCHAIN%\Release\osoasso.nmf osoasso-gwt\war
    copy /y favicon.ico osoasso-gwt\war
    goto :end
)

if "%1"=="deploy64" (
    copy /y %TOOLCHAIN%\Release\osoasso_x86_64.nexe osoasso-gwt\war
    copy /y %TOOLCHAIN%\Release\osoasso.nmf osoasso-gwt\war
    copy /y favicon.ico osoasso-gwt\war
    goto :end
)


:end
