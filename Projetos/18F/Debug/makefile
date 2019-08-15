################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CR18F1.1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CR18F1.1.list \


# All Target
all: CR18F1.1.elf secondary-outputs

# Tool invocations
CR18F1.1.elf: $(OBJS) $(USER_OBJS) C:\Users\gerry.COMLINK\STM32CubeIDE\workspace_1.0.0-2\CR18F1.1\STM32F030C8TX_FLASH.ld
	arm-none-eabi-gcc -o "CR18F1.1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\gerry.COMLINK\STM32CubeIDE\workspace_1.0.0-2\CR18F1.1\STM32F030C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CR18F1.1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CR18F1.1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CR18F1.1.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
