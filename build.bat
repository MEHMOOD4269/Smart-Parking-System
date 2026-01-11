@echo off
setlocal enabledelayedexpansion

cd /d "M:\3rd sem\DSA\Smart Parking System\Smart-Parking-System"

echo Compiling C++ files...
C:\MinGW\bin\g++.exe main.cpp AllocationEngine.cpp ParkingArea.cpp ParkingRequest.cpp ParkingSlot.cpp RollbackManager.cpp Vehicle.cpp Zone.cpp -o main.exe 2>&1

if errorlevel 1 (
    echo Build failed!
    echo.
    echo Running again with verbose output:
    C:\MinGW\bin\g++.exe main.cpp AllocationEngine.cpp ParkingArea.cpp ParkingRequest.cpp ParkingSlot.cpp RollbackManager.cpp Vehicle.cpp Zone.cpp -o main.exe -v
    pause
    exit /b 1
) else (
    echo Build successful!
    main.exe
)
