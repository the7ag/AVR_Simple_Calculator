#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "../../UTIL/STD_Types.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../UTIL/BitMath.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                  4
#define KEYPAD_NUM_ROWS                  4

/* Keypad Port Configurations */
#define KEYPAD_PORT_ID                   PORTC

#define KEYPAD_FIRST_ROW_PIN_ID           Pin0
#define KEYPAD_FIRST_COLUMN_PIN_ID        Pin4

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOW
#define KEYPAD_BUTTON_RELEASED           HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8_t KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */