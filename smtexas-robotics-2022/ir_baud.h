
#ifndef IR_BAUD_H // include guard
#define IR_BAUD_H


// custom baud rate set code
typedef unsigned long uint32_t;
typedef unsigned short uint16_t;

typedef struct
{
	uint16_t SR;
	uint16_t RESERVED0;
	uint16_t DR;
	uint16_t RESERVED1;
	uint16_t BRR;
	uint16_t RESERVED2;
	uint16_t CR1;
	uint16_t RESERVED3;
	uint16_t CR2;
	uint16_t RESERVED4;
	uint16_t CR3;
	uint16_t RESERVED5;
	uint16_t GTPR;
	uint16_t RESERVED6;
} USART_TypeDef;

/* Peripheral memory map */
#define PERIPH_BASE        ((unsigned long)0x40000000)
#define APB1PERIPH_BASE    PERIPH_BASE
#define USART2_BASE        (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE        (APB1PERIPH_BASE + 0x4800)

#define USART2 ((USART_TypeDef *) USART2_BASE)
#define USART3 ((USART_TypeDef *) USART3_BASE)


void setBaud( const TUARTs nPort, int baudRate ) {
	uint32_t tmpreg = 0x00, apbclock = 0x00;
	uint32_t integerdivider = 0x00;
	uint32_t fractionaldivider = 0x00;

	/* pclk1 - 36MHz */
	apbclock = 36000000;

	/* Determine the integer part */
	integerdivider = ((0x19 * apbclock) / (0x04 * (baudRate)));
	tmpreg = (integerdivider / 0x64) << 0x04;

	/* Determine the fractional part */
	fractionaldivider = integerdivider - (0x64 * (tmpreg >> 0x04));
	tmpreg |= ((((fractionaldivider * 0x10) + 0x32) / 0x64)) & 0x0F;

	/* Write to USART BRR */
	USART_TypeDef *uart = USART2;
	if( nPort == UART2 ) {
		uart = USART3;
	}
	uart->BRR = (uint16_t)tmpreg;
}



#endif // close guard
