#ifndef DIO_REG_H_
#define DIO_REG_H_


#include "DIO.h"
/*PORT A REGISTERS*/
#define DDRA_Reg	*((volatile uint8_t*) 0x3A)
#define PORTA_Reg	*((volatile uint8_t*) 0x3B)
#define PINA_Reg	*((volatile uint8_t*) 0x39)
/*PORT B REGISTERS*/
#define DDRB_Reg	*((volatile uint8_t*) 0x37)
#define PORTB_Reg	*((volatile uint8_t*) 0x38)
#define PINB_Reg	*((volatile uint8_t*) 0x36)
/*PORT C REGSTERS*/
#define DDRC_Reg	*((volatile uint8_t*) 0x34)
#define PORTC_Reg	*((volatile uint8_t*) 0x35)
#define PINC_Reg	*((volatile uint8_t*) 0x33)
/*PORT D REGISTERS*/
#define DDRD_Reg	*((volatile uint8_t*) 0x31)
#define PORTD_Reg	*((volatile uint8_t*) 0x32)
#define PIND_Reg	*((volatile uint8_t*) 0x30)





#endif /* DIO_REG_H_ */