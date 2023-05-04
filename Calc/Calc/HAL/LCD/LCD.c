#include "LCD.h"

static uint8_t initdone=0; /*To make sure that we init the lcd*/
static DIO_PORT_ID LCD_Data,LCD_Control; /*Copy of the current LCD */
static DIO_PIN_ID RS, E, D4, D5, D6, D7; /*Copy of LCD PINS LOCATION*/
void LCD_Init(DIO_PORT_ID LCD_Data_Port,DIO_PORT_ID LCD_Control_Port ,DIO_PIN_ID rs,DIO_PIN_ID e,DIO_PIN_ID d4,DIO_PIN_ID d5,DIO_PIN_ID d6,DIO_PIN_ID d7)
{
	/*Taking a copy of the current LCD location*/
	LCD_Data=LCD_Data_Port;
	LCD_Control=LCD_Control_Port;
	RS=rs;
	E=e;
	D4=d4;
	D5=d5;
	D6=d6;
	D7=d7;
	/*setting it's dirction as output*/
	DIO_SetPinDirection(LCD_Control_Port,RS,Output);
	DIO_SetPinDirection(LCD_Control_Port,E,Output);
	DIO_SetPinDirection(LCD_Data_Port,D4,Output);
	DIO_SetPinDirection(LCD_Data_Port,D5,Output);
	DIO_SetPinDirection(LCD_Data_Port,D6,Output);
	DIO_SetPinDirection(LCD_Data_Port,D7,Output);
	_delay_ms(30);
	/*send 4 bit mode init*/
	LCD_SendInstruction(0x20);
	LCD_SendInstruction(0x20);
	LCD_SendInstruction(0x80); //Send 2 Line Mode with 5*7 Pixel
	_delay_ms(1);

	LCD_SendInstruction(0x00); //Return home
	LCD_SendInstruction(0xC0); //Send Display on Cursor on Blink off
	_delay_ms(1);
	LCD_SendInstruction(0x00); // Return home
	LCD_SendInstruction(0x10); // LCD clear
	_delay_ms(2);
	initdone=1;
}
void LCD_SendData(uint8_t Data)
{
	//RW LOW
	//Rs High to send data
	DIO_SetPinValue(LCD_Control,RS,HIGH);
	//High Nibble bit 4 5 6 7
	DIO_SetPinValue(LCD_Data,D4,ReadBit(Data,4));
	DIO_SetPinValue(LCD_Data,D5,ReadBit(Data,5));
	DIO_SetPinValue(LCD_Data,D6,ReadBit(Data,6));
	DIO_SetPinValue(LCD_Data,D7,ReadBit(Data,7));
	/*Send Falling Edge on enable*/
	DIO_SetPinValue(LCD_Control,E,HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control,E,LOW);
	//Lower Nibble bit 0 1 2 3
	DIO_SetPinValue(LCD_Data,D4,ReadBit(Data,0));
	DIO_SetPinValue(LCD_Data,D5,ReadBit(Data,1));
	DIO_SetPinValue(LCD_Data,D6,ReadBit(Data,2));
	DIO_SetPinValue(LCD_Data,D7,ReadBit(Data,3));
	/*Falling edge on the enable*/
	DIO_SetPinValue(LCD_Control,E,HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control,E,LOW);
	_delay_ms(2);
}

void LCD_SendInstruction(uint8_t CMD)
{
	//RW LOW
	//Rs LOW to send data
	DIO_SetPinValue(LCD_Control,RS,LOW);
	//High Nibble bit 4 5 6 7
	DIO_SetPinValue(LCD_Data,D4,ReadBit(CMD,4));
	DIO_SetPinValue(LCD_Data,D5,ReadBit(CMD,5));
	DIO_SetPinValue(LCD_Data,D6,ReadBit(CMD,6));
	DIO_SetPinValue(LCD_Data,D7,ReadBit(CMD,7));
	DIO_SetPinValue(LCD_Control,E,HIGH);
	_delay_ms(1);
	/*falling edge*/
	DIO_SetPinValue(LCD_Control,E,LOW);
	/*if lcd is done init we use 8 bits instructions*/
	if(initdone){
		//Lower Nibble bits 0 1 2 3
		DIO_SetPinValue(LCD_Data,D4,ReadBit(CMD,0));
		DIO_SetPinValue(LCD_Data,D5,ReadBit(CMD,1));
		DIO_SetPinValue(LCD_Data,D6,ReadBit(CMD,2));
		DIO_SetPinValue(LCD_Data,D7,ReadBit(CMD,3));
		/*Falling edge*/
		DIO_SetPinValue(LCD_Control,E,HIGH);
		_delay_ms(1);
		DIO_SetPinValue(LCD_Control,E,LOW);
	}
	_delay_ms(2);
}
/*To print an entire string*/
void LCD_Print(uint8_t* Data)
{
	/*Data is a pointer to first element of the string*/
	while(*Data!='\0')
	{
		LCD_SendData(*Data); //send where it's pointing
		Data++;				//increment the pointer
		
	}
}

void LCD_SetCursor(uint8_t row,uint8_t column)
{
	//Make the address to send it to the lcd
	uint8_t Address=0;
	if (row<2	&&	column<16) 
	{
		//row 0 is 0x00 row 1 is 0x40 column is ranges from 0x00 to 0x0F
		//so we take the row * 0x40 + column to get the right address
		Address=(row*0x40)+column;
		//we set the bit no7 to make sure it's an address
		Address=SetBit(Address,7);
		//we send that address as a command
		LCD_SendInstruction(Address);
	}
}
void LCD_Clear()
{
	LCD_SendInstruction(0x01); //we send the clear command
}
void LCD_IntegerToString(uint16 data)
{
	// buffer to save the number after converting
	uint8_t BUFF[16];
	//transform the number into string
	itoa(data,BUFF,10); //Base 10
	//print that string
	LCD_Print(BUFF);
}