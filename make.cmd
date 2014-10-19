@echo off

setlocal

set NACL_SDK_ROOT=c:\Users\Josh\Documents\development\nacl_sdk\pepper_35
set CORES=3

if "%1"=="pnacl" (
    set TOOLCHAIN=pnacl
    set NACL_ARCH=x86_32
) else if "%1"=="newlib" (
    set TOOLCHAIN=newlib
    set NACL_ARCH=x86_32
) else if "%1"=="emscripten" (
    set TOOLCHAIN=emscripten
    set NACL_ARCH=x86_32
) else (
    echo Error: Please provide a valid target [pnacl|nacl|emscripten]
    goto :end
)

if "%1"=="all" (
    set NACL_ARCH=x86_32
)


:: NACL_SDK_ROOT must be set.
if not defined NACL_SDK_ROOT (
  echo Error: NACL_SDK_ROOT is not set.
  echo Please set NACL_SDK_ROOT to the full path of the Native Client SDK.
  echo For example:
  echo set NACL_SDK_ROOT=D:\nacl_sdk
  goto end
)

if "%1"=="test" (
    %NACL_SDK_ROOT%\tools\make -j %CORES% -f Makefile_test || goto :end
    if not "%TOOLCHAIN%"=="newlib" (
        %NACL_SDK_ROOT%\toolchain\win_pnacl\bin\pnacl-translate -arch i686 %TOOLCHAIN%\release\osoasso_test.pexe -o %TOOLCHAIN%\release\osoasso_test_x86_32.nexe
    )
    %NACL_SDK_ROOT%\tools\sel_ldr.py %TOOLCHAIN%\release\osoasso_test_x86_32.nexe
    goto :end
)

if "%1"=="stress" (
    %NACL_SDK_ROOT%\tools\make -j %CORES% -f Makefile_stress_test || goto :end
    if not "%TOOLCHAIN%"=="newlib" (
        %NACL_SDK_ROOT%\toolchain\win_pnacl\bin\pnacl-translate -arch i686 %TOOLCHAIN%\release\osoasso_stress_test.pexe -o %TOOLCHAIN%\release\osoasso_stress_test_x86_32.nexe
    )
    %NACL_SDK_ROOT%\tools\sel_ldr.py %TOOLCHAIN%\release\osoasso_stress_test_x86_32.nexe
    goto :end
)

if "%2"=="deploy" (
    set NACL_ARCH=
)

if "%1"=="all" (
    echo Building all targets
    call :build_nacl || goto :end
    call :build_emscripten || goto :end
) else (
    if "%TOOLCHAIN%"=="emscripten" (
        call :build_emscripten || goto :end
    ) else (
        call :build_nacl || goto :end
    )
)

if "%2"=="deploy" (
    if "%1"=="all" (
        call :deploy_emscripten
        call :deploy_nacl
    ) else (
        if "%TOOLCHAIN%"=="emscripten" (
            call :deploy_emscripten
        ) else (
            call :deploy_nacl
        )
    )
    call :deploy_resources
    goto :end
)

goto :end

:build_emscripten
echo Build for emscripten target
%NACL_SDK_ROOT%\tools\make -j %CORES% -f Makefile_js CONFIG=release || goto :end
goto end

:deploy_emscripten
echo Deploying for emscripten target
copy /y emscripten\release\osoasso.js osoasso-gwt\war
goto :end

:build_nacl
echo Build for nacl target
%NACL_SDK_ROOT%\tools\make -j %CORES% CONFIG=Release || goto :end
goto end

:deploy_nacl
echo Deploying for nacl target
if "%TOOLCHAIN%"=="newlib" (
    copy /y %TOOLCHAIN%\release\osoasso_x86_32.nexe osoasso-gwt\war
    copy /y %TOOLCHAIN%\release\osoasso_x86_64.nexe osoasso-gwt\war
    copy /y %TOOLCHAIN%\release\osoasso_arm.nexe osoasso-gwt\war
) else (
    copy /y %TOOLCHAIN%\release\osoasso.pexe osoasso-gwt\war
)
copy /y %TOOLCHAIN%\release\osoasso.nmf osoasso-gwt\war
goto :end

:deploy_resources
echo Deploying resources
copy /y favicon.ico osoasso-gwt\war
goto :end

:end
