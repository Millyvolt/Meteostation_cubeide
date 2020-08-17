################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include Drivers/Src/subdir.mk
-include CMSIS/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
meteost_cubeide_tx.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
meteost_cubeide_tx.list \

OBJCOPY_BIN += \
meteost_cubeide_tx.bin \


# All Target
all: meteost_cubeide_tx.elf secondary-outputs

# Tool invocations
meteost_cubeide_tx.elf: $(OBJS) $(USER_OBJS) C:\git_repos\meteostation\meteostation_tx\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "meteost_cubeide_tx.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\git_repos\meteostation\meteostation_tx\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="meteost_cubeide_tx.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

meteost_cubeide_tx.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "meteost_cubeide_tx.list"
	@echo 'Finished building: $@'
	@echo ' '

meteost_cubeide_tx.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "meteost_cubeide_tx.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
