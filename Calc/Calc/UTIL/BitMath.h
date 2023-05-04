#ifndef BITHMATH_H_
#define BITHMATH_H_

/*Set The choosen bit macro*/
#define SetBit(Reg,Pin)		Reg	|=	 (1<<Pin)
/*Clearing The choosen Bit Macro*/  
#define ClearBit(Reg,Pin)	Reg	&=	~(1<<Pin) 
/*Toggling The choosen Bit*/
#define ToggleBit(Reg,Pin)	Reg ^=	 (1<<Pin)
/*Read A choosen Bit*/
#define ReadBit(Reg,Pin)  ((Reg >>	 Pin)&1)



#endif /* BITHMATH_H_ */