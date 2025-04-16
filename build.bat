@echo off
echo Compiling program...
g++ -std=c++17 -I./include src/*.cpp -o booking_system.exe
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Running program...
    booking_system.exe
) else (
    echo Compilation failed!
    pause
)