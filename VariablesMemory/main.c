
#include "stdlib.h"				//contains malloc function
//#include "stm32f10x.h"
int y, z1, z2;						//
int initVal = 0xAA;				//
int main(void)
{ 
	int* pdata;
	pdata = malloc(3 * sizeof(int));	//
	*pdata = 0x1111;									//
	*(pdata + 1) = 0x2222;							//
	*(pdata + 2) = 0x33333333;					//
	volatile int x=5;									//
	volatile int *px = &x;						//
	px++;															//
	*px = 0x5555;
	y=2;															//
	int* py = &y;											//
	char text[] = "abcde";						//
	char text1[] = "fghi";						//
	
	while(1)
	{
		z1 = x+y;												//
		z2 = *px + *py;									//
	}
}

