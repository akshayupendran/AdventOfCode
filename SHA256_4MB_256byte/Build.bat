@ECHO OFF
SETLOCAL
SET CURRENT_DIR=%~dp0
gcc -I%CURRENT_DIR%\openssl-1.1.1d-win64-mingw\include\openssl CalculateOverBinary_pthread.c -o CalculateOverBinary_pthread.exe -lcrypto
pause
ENDLOCAL