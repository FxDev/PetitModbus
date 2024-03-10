#include "PetitModbus.h"
#include "PetitModbusPort.h"

/***********************Input/Output Coils and Registers***********************/
#if ((PETITMODBUS_READ_HOLDING_REGISTERS_ENABLED > 0)|| (PETITMODBUSWRITE_SINGLE_REGISTER_ENABLED > 0) || (PETITMODBUS_WRITE_MULTIPLE_REGISTERS_ENABLED > 0))
PetitRegStructure  PetitRegisters       [NUMBER_OF_OUTPUT_PETITREGISTERS];
#endif
