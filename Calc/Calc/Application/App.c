#include "App.h"

void app()
{
	/*LCD init*/
	LCD_Init(PORTA,PORTA,Pin0,Pin1,Pin2,Pin3,Pin4,Pin5);
	/*Print 0 on it as in old LCD*/
	output(0);
	/*Variables for the Calc*/
	sint16 num1 = 0, num2 = 0;
	/*Flags*/
	uint8_t op = 0, num_flag = 0, op_flag = 0;
	while (1)
	{
		/*we take the input from the keypad*/
		uint8_t ch = input();
		/*Check if it's a number*/
		if (ch >= '0' && ch <= '9')
		{
			/*if number flag ==0 then it's the first digit of first number*/
			if (num_flag == 0)
			{
				/*we set it to 1 as we are entering the first number*/
				num_flag = 1;
				/*convert it into an int*/
				num1 = ch - '0';
				//print out the number
				output(num1);
			}
			/*if the flag is 1 we are entering the first number still*/
			else if (num_flag == 1)
			{
				/*we keep taking the entered numbers and saving it into num1*/
				num1 = num1 * 10 + (ch - '0');
				//and we display the new number with every digit entered
				output(num1);
			}
			//if the flag == 2 we are now entering the 2nd number
			else if (num_flag == 2)
			{
				/*we convert that number into int*/
				num2 = num2 * 10 + (ch - '0');
				//we make the op flag = 0 as we are still entering the 2nd number
				op_flag = 0;
				//we print out the number
				output(num2);
			}
		}
		/*if we don't enter a number*/
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			//if we have an op
			if(!op_flag)
			{
				/*and we are entering the 2nd number*/
				if(num_flag == 2)
				{
					//we solve the current op and save it to num1
					num1 = solve(num1, num2, op);
					// make the 2nd number=0
					num2 = 0;
					//print out the result
					output(num1);
				}
				//if we are still entering the first number and pressed an op we switch to the 2nd number
				num_flag = 2;
			}
			//if we don't have an op we save the last op entered
			op = ch;
			//and set the flag to one as we are writing an op
			op_flag = 1;
		}
		//if we entered =
		else if (ch == '=')
		{
			//solve the 2 number problem
			num1 = solve(num1, num2, op);
			//set the 2nd number to be0
			num2 = 0;
			//clear the current op
			op = 0;
			//clear the flag
			op_flag = 0;
			//set the flag to 0 to reset the calculator if we entered a number
			num_flag = 0;
			//Print the result
			output(num1);
		}
		//if we entered clear
		else if (ch == 'o')
		{
			//clear everything
			num1 = 0;
			num2 = 0;
			op = 0;
			op_flag = 0;
			num_flag = 0;
			//print 0
			output(0);
		}
		else if (ch == 'q') break; //exit from the app /*impossible*/
	}
}

uint8_t input()
{
	//we make a local variable
	uint8_t ch = 0;
	//read it from the keypad
	ch = KEYPAD_getPressedKey();
	//delay for debouncing to only read one number
	_delay_ms(300);
	//return the charcter
	return ch;
}

void output(sint16 num)
{
	//Clear the old number
	LCD_Clear();
	//print only the new number
	LCD_IntegerToString(num);
}

sint16 solve(sint16 num1, sint16 num2, uint8_t op)
{
	//solve the equation of two number
	switch (op)
	{
		case '+':   return num1 + num2;
		case '-':   return num1 - num2;
		case '*':   return num1 * num2;
		//to avoid div by zero
		case '/':   if (num2 == 0) return 0;
					else return num1 / num2;
		//if we don't have an op we return num1 as our solution
		default:    return num1;
	}
}