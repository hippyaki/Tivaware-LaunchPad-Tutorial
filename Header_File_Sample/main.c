#include<stdio.h>
#include<stdint.h>
#include"Blink.h"


int main(void)
{
	GPIO_Init();

	while(1){

	    LEDon('B'); //1 -RED, 2 - BLUE, 3 - GREEN
	    LEDoff();


	    //Blink();

	}

	return 0;
}
