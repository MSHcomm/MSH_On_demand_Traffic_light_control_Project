################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/gpTimer/subdir.mk
-include MCAL/External_Interrupts/subdir.mk
-include MCAL/DIO/subdir.mk
-include ECUAL/LED/subdir.mk
-include ECUAL/Button/subdir.mk
-include Application/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
MSH_On_demand_Traffic_light_control.lss \

FLASH_IMAGE += \
MSH_On_demand_Traffic_light_control.hex \

EEPROM_IMAGE += \
MSH_On_demand_Traffic_light_control.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: MSH_On_demand_Traffic_light_control.elf secondary-outputs

# Tool invocations
MSH_On_demand_Traffic_light_control.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,MSH_On_demand_Traffic_light_control.map -mmcu=atmega32 -o "MSH_On_demand_Traffic_light_control.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

MSH_On_demand_Traffic_light_control.lss: MSH_On_demand_Traffic_light_control.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S MSH_On_demand_Traffic_light_control.elf  >"MSH_On_demand_Traffic_light_control.lss"
	@echo 'Finished building: $@'
	@echo ' '

MSH_On_demand_Traffic_light_control.hex: MSH_On_demand_Traffic_light_control.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex MSH_On_demand_Traffic_light_control.elf  "MSH_On_demand_Traffic_light_control.hex"
	@echo 'Finished building: $@'
	@echo ' '

MSH_On_demand_Traffic_light_control.eep: MSH_On_demand_Traffic_light_control.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex MSH_On_demand_Traffic_light_control.elf  "MSH_On_demand_Traffic_light_control.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: MSH_On_demand_Traffic_light_control.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 MSH_On_demand_Traffic_light_control.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) MSH_On_demand_Traffic_light_control.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
