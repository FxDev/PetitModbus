################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/PetitModbus/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
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
SECONDARY_FLASH += \
CH32V003F4P6_PetitModbus.hex \

SECONDARY_LIST += \
CH32V003F4P6_PetitModbus.lst \

SECONDARY_SIZE += \
CH32V003F4P6_PetitModbus.siz \


# All Target
all: CH32V003F4P6_PetitModbus.elf secondary-outputs

# Tool invocations
CH32V003F4P6_PetitModbus.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\MRS_DATA\workspace\CH32V003F4P6_PetitModbus\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"CH32V003F4P6_PetitModbus.map" --specs=nano.specs --specs=nosys.specs -o "CH32V003F4P6_PetitModbus.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
CH32V003F4P6_PetitModbus.hex: CH32V003F4P6_PetitModbus.elf
	@	riscv-none-embed-objcopy -O ihex "CH32V003F4P6_PetitModbus.elf"  "CH32V003F4P6_PetitModbus.hex"
	@	@
CH32V003F4P6_PetitModbus.lst: CH32V003F4P6_PetitModbus.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "CH32V003F4P6_PetitModbus.elf" > "CH32V003F4P6_PetitModbus.lst"
	@	@
CH32V003F4P6_PetitModbus.siz: CH32V003F4P6_PetitModbus.elf
	@	riscv-none-embed-size --format=berkeley "CH32V003F4P6_PetitModbus.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) CH32V003F4P6_PetitModbus.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
