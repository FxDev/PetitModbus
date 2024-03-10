#include "debug.h"
#include "PetitModbus/PetitModbus.h"

#define MODBUS_ID   0x1

/* interrupts */
void TIM1_UP_IRQHandler(void)   __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void)    __attribute__((interrupt("WCH-Interrupt-fast")));

volatile uint32_t tim_tick = 0;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();

    InitPetitModbus(MODBUS_ID);

    while(1)
    {
        ProcessPetitModbus();
    }

    return 0;
}

void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {

        ReceiveInterrupt(USART_ReceiveData(USART1));
    }
}

void TIM1_UP_IRQHandler() {
    if(TIM1->INTFR & TIM_FLAG_Update) {

        PetitModBus_TimerValues();

        tim_tick++;

        if (tim_tick % 1000 == 0) {
            PetitRegisters[0].ActValue++;
            PetitRegisters[1].ActValue++;
            PetitRegisters[2].ActValue++;
        }

        TIM1->INTFR = ~TIM_FLAG_Update;
    }
}
