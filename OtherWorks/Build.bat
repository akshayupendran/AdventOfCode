@ECHO OFF
gcc -I "C:\Program Files\OpenSSL-Win64\include" -L "C:\Program Files\OpenSSL-Win64\lib" -l openssl SHA256OverBinary_Windows.c -o SHA256OverBinary_Windows.exe