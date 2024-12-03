::"C:\Program Files (x86)\GNU Tools ARM Embedded\9 ::2019-q4-major\bin\arm-none-eabi-objcopy" -O binary .\Release\I2C_KBS_LDROM.elf .\Release\I2C_KBS_LDROM.bin

@echo off
for /f "usebackq tokens=*" %%i in (`where /r "C:\Program Files (x86)" arm-none-eabi-objcopy.exe 2^>nul`) do set "TOOLCHAIN_PATH=%%i"

if "%TOOLCHAIN_PATH%"=="" (
    echo "GNU ARM toolchain not found."
    exit /b 1
) else (
    echo "Found toolchain at %TOOLCHAIN_PATH%"
)

"%TOOLCHAIN_PATH%" -O binary .\Release\I2C_KBS_LDROM.elf .\Release\I2C_KBS_LDROM.bin

if exist .\Release\I2C_KBS_LDROM.bin (
    powershell -Command "Write-Host 'I2C_KBS_LDROM.bin generated successfully!' -ForegroundColor Green"
) else (
    powershell -Command "Write-Host 'Failed to generate I2C_KBS_LDROM.bin.' -ForegroundColor Red"
)