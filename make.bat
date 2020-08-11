@ECHO off

SET CXX=cl
SET CXX_FLAGS=/EHsc
SET INCLUDE_PATH=/I ".\include" /I ".\include\HSGIL\external"

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c head.cpp

%CXX% %CXX_FLAGS% head.obj hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:head.exe

clean.bat
