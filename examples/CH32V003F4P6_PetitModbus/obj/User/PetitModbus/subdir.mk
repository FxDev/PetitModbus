################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/PetitModbus/PetitModbus.c \
../User/PetitModbus/PetitModbusPort.c \
../User/PetitModbus/PetitRegConstant.c 

OBJS += \
./User/PetitModbus/PetitModbus.o \
./User/PetitModbus/PetitModbusPort.o \
./User/PetitModbus/PetitRegConstant.o 

C_DEPS += \
./User/PetitModbus/PetitModbus.d \
./User/PetitModbus/PetitModbusPort.d \
./User/PetitModbus/PetitRegConstant.d 


# Each subdirectory must supply rules for building sources it contributes
User/PetitModbus/%.o: ../User/PetitModbus/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\CH32V003F4P6_PetitModbus\Debug" -I"C:\MRS_DATA\workspace\CH32V003F4P6_PetitModbus\Core" -I"C:\MRS_DATA\workspace\CH32V003F4P6_PetitModbus\User" -I"C:\MRS_DATA\workspace\CH32V003F4P6_PetitModbus\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

