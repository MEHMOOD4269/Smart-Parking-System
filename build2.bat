@echo off
setlocal enabledelayedexpansion

cd /d "M:\3rd sem\DSA\Smart Parking System\Smart-Parking-System"

echo Compiling object files...

for %%f in (main.cpp AllocationEngine.cpp ParkingArea.cpp ParkingRequest.cpp ParkingSlot.cpp RollbackManager.cpp Vehicle.cpp Zone.cpp) do (
    echo Compiling %%f...
    C:\MinGW\bin\g++.exe -c %%f -o %%~nf.o
    if errorlevel 1 (
        echo ERROR: Failed to compile %%f
        pause
        exit /b 1
    )
)

echo.
echo Linking...
C:\MinGW\bin\g++.exe -o main.exe main.o AllocationEngine.o ParkingArea.o ParkingRequest.o ParkingSlot.o RollbackManager.o Vehicle.o Zone.o

if errorlevel 1 (
    echo ERROR: Linking failed
    pause
    exit /b 1
)

echo Build successful!
echo.
echo Running program...
main.exe

pause
