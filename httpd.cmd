@echo off
if "%NACL_DIR%"=="" goto :error

setlocal
PATH=%NACL_DIR%/third_party/cygwin/bin;%PATH%
python httpd.py

goto :end

:error
echo Please set the NACL_DIR environment variable.

:end
