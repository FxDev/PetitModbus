#include "PetitModbus.h"
#include "PetitModbusPort.h"

// This port file for PIC microcontrollers!
#include "debug.h"

// Modbus RTU Variables
volatile unsigned char   PetitReceiveBuffer[PETITMODBUS_RECEIVE_BUFFER_SIZE];   // Buffer to collect data from hardware
volatile unsigned char   PetitReceiveCounter=0;                                 // Collected data number

// UART Initialize for Microconrollers, yes you can use another phsycal layer!
void PetitModBus_UART_Initialise(void)
{
// Insert UART Init Code Here
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

       /* USART1 TX-->D.5   RX-->D.6 */
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
       GPIO_Init(GPIOD, &GPIO_InitStructure);
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
       GPIO_Init(GPIOD, &GPIO_InitStructure);

       USART_InitTypeDef USART_InitStructure = { 0 };
       NVIC_InitTypeDef NVIC_InitStructure = { 0 };

       RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

       USART_InitStructure.USART_BaudRate = 9600;
       USART_InitStructure.USART_WordLength = USART_WordLength_8b;
       USART_InitStructure.USART_StopBits = USART_StopBits_1;
       USART_InitStructure.USART_Parity = USART_Parity_No;
       USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
       USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
       USART_Init(USART1, &USART_InitStructure);
       USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

       NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
       NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
       NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

       NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
       NVIC_Init(&NVIC_InitStructure);

       USART_Cmd(USART1, ENABLE);
}

// Timer Initialize for Petit Modbus, 1ms Timer will be good for us!
void PetitModBus_TIMER_Initialise(void)
{
// Insert TMR Init Code Here
    RCC->APB2PCENR |= RCC_APB2Periph_TIM1;
    TIM1->CTLR1 |= TIM_ARPE;
    TIM1->CTLR2 = TIM_MMS_1;

    // count up per 1sec
    // 48000 * 1000 = 48000000
    TIM1->ATRLR = 480;
    TIM1->PSC = 100-1;
    TIM1->RPTCR = 0;

    NVIC_EnableIRQ(TIM1_UP_IRQn);

    TIM1->INTFR = ~TIM_FLAG_Update; // 0x0001 // 10.4.5 Interrupt Status Register (TIM1_INTFR)
    TIM1->SWEVGR = TIM_UG;// 0x0001 // 10.4.6 Event Generation Register (TIM1_SWEVGR)
    TIM1->DMAINTENR |= TIM_IT_Update; // 0x0001 // 10.4.4 DMA/Interrupt Enable Register (TIM1_DMAINTENR)

    // TIM1 Enable
    TIM1->CTLR1 |= TIM_CEN;
}

// This is used for send one character
void PetitModBus_UART_Putch(unsigned char c)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    USART_SendData(USART1, (uint16_t)c);
}

// This is used for send string, better to use DMA for it ;)
unsigned char PetitModBus_UART_String(unsigned char *s, unsigned int Length)
{
    unsigned short  DummyCounter;

    for(DummyCounter=0;DummyCounter<Length;DummyCounter++)
        PetitModBus_UART_Putch(s[DummyCounter]);

    return TRUE;
}

/*************************Interrupt Fonction Slave*****************************/
// Call this function into your UART Interrupt. Collect data from it!
// Better to use DMA
void ReceiveInterrupt(unsigned char Data)
{
    PetitReceiveBuffer[PetitReceiveCounter]   =Data;
    PetitReceiveCounter++;

    if(PetitReceiveCounter>PETITMODBUS_RECEIVE_BUFFER_SIZE)
        PetitReceiveCounter=0;

    PetitModbusTimerValue=0;
}

// Call this function into 1ms Interrupt or Event!
void PetitModBus_TimerValues(void)
{
    PetitModbusTimerValue++;
}
/******************************************************************************/
