################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/Device/Nuvoton/NM1240/Source/system_NM1240.c 

OBJS += \
./Library/Device/Nuvoton/NM1240/Source/system_NM1240.o 

C_DEPS += \
./Library/Device/Nuvoton/NM1240/Source/system_NM1240.d 


# Each subdirectory must supply rules for building sources it contributes
Library/Device/Nuvoton/NM1240/Source/%.o: ../Library/Device/Nuvoton/NM1240/Source/%.c Library/Device/Nuvoton/NM1240/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\CMSIS\Include" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\Device\Nuvoton\NM1240\Include" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\StdDriver\inc" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\I2C_KBS_LDROM" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


