#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/DIO/DIO.h"
#define F_CPU 8000000UL
#include <util/delay.h>

/*LCD init for 4 bit mode*/
void LCD_Init(DIO_PORT_ID LCD_Data_Port,DIO_PORT_ID LCD_Control_Port ,DIO_PIN_ID RS,DIO_PIN_ID E,DIO_PIN_ID D4,DIO_PIN_ID D5,DIO_PIN_ID D6,DIO_PIN_ID D7);
/*Send an instruction to the screen*/
void LCD_SendInstruction(uint8_t CMD);
/*Send a data to the screen*/
void LCD_SendData(uint8_t Data);
/*print a string to the screen*/
void LCD_Print(uint8_t* Data);
/*Move the cursor to a spacific place*/
void LCD_SetCursor(uint8_t row,uint8_t column);
/*Clear the screen*/
void LCD_Clear();
/*Convert an integer to string*/
void LCD_IntegerToString(uint16 data);

#endif /* LCD_H_ */