#include "Keypad.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8_t_t KEYPAD_4x3_adjustKeyNumber(uint8_t button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8_t KEYPAD_4x4_adjustKeyNumber(uint8_t button_number);
#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8_t KEYPAD_getPressedKey(void)
{
	uint8_t col,row;
	uint8_t keypad_port_value = 0;
	while(1)
	{
		for(col=0;col<KEYPAD_NUM_COLS;col++) /* loop for columns */
		{
			/* 
			 * Each time setup the direction for all keypad port as input pins,
			 * except this column will be output pin
			 */
			DIO_SetPortDirection(KEYPAD_PORT_ID,Input);
			DIO_SetPinDirection(KEYPAD_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+col,Output);
			
#if(KEYPAD_BUTTON_PRESSED == LOW)
			/* Clear the column output pin and set the rest pins value */
			keypad_port_value = ~(1<<(KEYPAD_FIRST_COLUMN_PIN_ID+col));
#else
			/* Set the column output pin and clear the rest pins value */
			keypad_port_value = (1<<(KEYPAD_FIRST_COLUMN_PIN_ID+col));
#endif
			DIO_SetPortValue(KEYPAD_PORT_ID,keypad_port_value);

			for(row=0;row<KEYPAD_NUM_ROWS;row++) /* loop for rows */
			{
				/* Check if the switch is pressed in this row */
				
				if(DIO_GetPinValue(KEYPAD_PORT_ID,row+KEYPAD_FIRST_ROW_PIN_ID) == KEYPAD_BUTTON_PRESSED)
				{
					#if (KEYPAD_NUM_COLS == 3)
						return KEYPAD_4x3_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
					#elif (KEYPAD_NUM_COLS == 4)
						return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
					#endif
				}
			}
		}
	}	
}

#if (KEYPAD_NUM_COLS == 3)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8_t KEYPAD_4x3_adjustKeyNumber(uint8_t button_number)
{
	uint8_t keypad_button = 0;
	switch(button_number)
	{
		case 10: keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: keypad_button = 0;
				 break;		
		case 12: keypad_button = '#'; // ASCII Code of #
				 break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
} 

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8_t KEYPAD_4x4_adjustKeyNumber(uint8_t button_number)
{
	uint8_t keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = '7';
				break;
		case 2: keypad_button = '8';
				break;
		case 3: keypad_button = '9';
				break;
		case 4: keypad_button = '/'; // ASCII Code of %
				break;
		case 5: keypad_button = '4';
				break;
		case 6: keypad_button = '5';
				break;
		case 7: keypad_button = '6';
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;		
		case 9: keypad_button = '1';
				break;
		case 10: keypad_button = '2';
				break;
		case 11: keypad_button = '3';
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 'o';  /* ASCII of Enter */
				break;			
		case 14: keypad_button = '0';
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
} 

#endif
