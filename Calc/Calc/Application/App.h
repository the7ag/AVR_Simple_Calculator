#ifndef APP_H_
#define APP_H_

#include "../MCAL/DIO/DIO.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/Keypad/Keypad.h"
/*For taking the input from the Keypad*/
uint8_t input();
/*Showing the output on the LCD*/
void output(sint16 num);
/*Solve an equation*/
sint16 solve(sint16 num1, sint16 num2, uint8_t op);
/*To call in main*/
void app();

#endif /* APP_H_ */