################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/StdDriver/src/acmp.c \
../Library/StdDriver/src/adc.c \
../Library/StdDriver/src/bpwm.c \
../Library/StdDriver/src/clk.c \
../Library/StdDriver/src/ecap.c \
../Library/StdDriver/src/epwm.c \
../Library/StdDriver/src/fmc.c \
../Library/StdDriver/src/gdma.c \
../Library/StdDriver/src/gpio.c \
../Library/StdDriver/src/op.c \
../Library/StdDriver/src/retarget.c \
../Library/StdDriver/src/sys.c \
../Library/StdDriver/src/timer.c \
../Library/StdDriver/src/usci_i2c.c \
../Library/StdDriver/src/usci_spi.c \
../Library/StdDriver/src/usci_uart.c \
../Library/StdDriver/src/wdt.c 

OBJS += \
./Library/StdDriver/src/acmp.o \
./Library/StdDriver/src/adc.o \
./Library/StdDriver/src/bpwm.o \
./Library/StdDriver/src/clk.o \
./Library/StdDriver/src/ecap.o \
./Library/StdDriver/src/epwm.o \
./Library/StdDriver/src/fmc.o \
./Library/StdDriver/src/gdma.o \
./Library/StdDriver/src/gpio.o \
./Library/StdDriver/src/op.o \
./Library/StdDriver/src/retarget.o \
./Library/StdDriver/src/sys.o \
./Library/StdDriver/src/timer.o \
./Library/StdDriver/src/usci_i2c.o \
./Library/StdDriver/src/usci_spi.o \
./Library/StdDriver/src/usci_uart.o \
./Library/StdDriver/src/wdt.o 

C_DEPS += \
./Library/StdDriver/src/acmp.d \
./Library/StdDriver/src/adc.d \
./Library/StdDriver/src/bpwm.d \
./Library/StdDriver/src/clk.d \
./Library/StdDriver/src/ecap.d \
./Library/StdDriver/src/epwm.d \
./Library/StdDriver/src/fmc.d \
./Library/StdDriver/src/gdma.d \
./Library/StdDriver/src/gpio.d \
./Library/StdDriver/src/op.d \
./Library/StdDriver/src/retarget.d \
./Library/StdDriver/src/sys.d \
./Library/StdDriver/src/timer.d \
./Library/StdDriver/src/usci_i2c.d \
./Library/StdDriver/src/usci_spi.d \
./Library/StdDriver/src/usci_uart.d \
./Library/StdDriver/src/wdt.d 


# Each subdirectory must supply rules for building sources it contributes
Library/StdDriver/src/%.o: ../Library/StdDriver/src/%.c Library/StdDriver/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\CMSIS\Include" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\Device\Nuvoton\NM1240\Include" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\StdDriver\inc" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\I2C_KBS_LDROM" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


