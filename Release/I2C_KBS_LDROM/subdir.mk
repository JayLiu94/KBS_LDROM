################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../I2C_KBS_LDROM/aprom_isp.c \
../I2C_KBS_LDROM/i2c_cmd.c \
../I2C_KBS_LDROM/i2c_ctrl.c \
../I2C_KBS_LDROM/main.c \
../I2C_KBS_LDROM/prj_config.c \
../I2C_KBS_LDROM/uart_ctrl.c 

OBJS += \
./I2C_KBS_LDROM/aprom_isp.o \
./I2C_KBS_LDROM/i2c_cmd.o \
./I2C_KBS_LDROM/i2c_ctrl.o \
./I2C_KBS_LDROM/main.o \
./I2C_KBS_LDROM/prj_config.o \
./I2C_KBS_LDROM/uart_ctrl.o 

C_DEPS += \
./I2C_KBS_LDROM/aprom_isp.d \
./I2C_KBS_LDROM/i2c_cmd.d \
./I2C_KBS_LDROM/i2c_ctrl.d \
./I2C_KBS_LDROM/main.d \
./I2C_KBS_LDROM/prj_config.d \
./I2C_KBS_LDROM/uart_ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
I2C_KBS_LDROM/%.o: ../I2C_KBS_LDROM/%.c I2C_KBS_LDROM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\CMSIS\Include" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\Device\Nuvoton\NM1240\Include" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\StdDriver\inc" -I"C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\I2C_KBS_LDROM" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


