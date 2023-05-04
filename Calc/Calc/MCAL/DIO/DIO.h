#ifndef DIO_H_
#define DIO_H_

#include "../../UTIL/STD_Types.h"
#include "../../UTIL/BitMath.h"
#include "DIO_Types.h"
#include "DIO_REG.h"

/*WHOLE PORT DIRECTION HEADER*/
void DIO_SetPortDirection(DIO_PORT_ID port_name,DIO_DIRECTION direction);
/*WHOLE PORT VALUE HEADER*/
void DIO_SetPortValue(DIO_PORT_ID port_name,uint8_t value);

/*ONE PIN DIRECTION FUNCTION HEADER*/
void DIO_SetPinDirection(DIO_PORT_ID port_name,DIO_PIN_ID pin_name,DIO_DIRECTION direction);

/*ONE PIN VALUE FUNCTION HEADER*/
void DIO_SetPinValue(DIO_PORT_ID port_name,DIO_PIN_ID pin_name,DIO_VALUE value);

/*ONE PIN TOGGLE FUNCTION HEADER*/
void DIO_TogglePinValue(DIO_PORT_ID port_name,DIO_PIN_ID pin_name);

/*GETTING THE VALUE OF A PIN*/
DIO_VALUE DIO_GetPinValue(DIO_PORT_ID port_name,DIO_PIN_ID pin_name);




#endif /* DIO_H_ */