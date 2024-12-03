################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Library/StdDriver/src/subdir.mk
-include Library/Device/Nuvoton/NM1240/Source/GCC/subdir.mk
-include Library/Device/Nuvoton/NM1240/Source/subdir.mk
-include I2C_KBS_LDROM/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := I2C_KBS_LDROM
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
I2C_KBS_LDROM.hex \

SECONDARY_SIZE += \
I2C_KBS_LDROM.siz \


# All Target
all: I2C_KBS_LDROM.elf secondary-outputs

# Tool invocations
I2C_KBS_LDROM.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "C:\Users\CCLIU2\Desktop\WORK\KBS\I2C_KBS_LDROM_0925\I2C_KBS_LDROM\Library\Device\Nuvoton\NM1240\Source\GCC\gcc_arm.ld" -nostdlib -Xlinker --gc-sections -Wl,-Map,"I2C_KBS_LDROM.map" --specs=nano.specs -specs=nosys.specs -o "I2C_KBS_LDROM.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

I2C_KBS_LDROM.hex: I2C_KBS_LDROM.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "I2C_KBS_LDROM.elf"  "I2C_KBS_LDROM.hex"
	@echo 'Finished building: $@'
	@echo ' '

I2C_KBS_LDROM.siz: I2C_KBS_LDROM.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "I2C_KBS_LDROM.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) I2C_KBS_LDROM.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
