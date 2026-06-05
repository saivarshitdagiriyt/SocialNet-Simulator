@echo off
REM Compile script for Social Network Simulator (Windows)

echo Compiling Social Network Simulator...
g++ -std=c++17 -Wall -Wextra -o socialnet.exe main.cpp

if %errorlevel% equ 0 (
    echo Compilation successful!
    echo Run the program with: socialnet.exe
) else (
    echo Compilation failed!
    exit /b 1
)
