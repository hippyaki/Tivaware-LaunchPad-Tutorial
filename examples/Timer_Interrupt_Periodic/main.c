#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

/**
 * main.c
 */

extern void Timer0IntHandler(void);

int flag = 0;

int main(void)
{
	uint32_t uiPeriod;

	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x0E);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	//TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	uiPeriod = (SysCtlClockGet());

  	//uiPeriod = 40000000;

	TimerLoadSet(TIMER0_BASE, TIMER_A, (uiPeriod - 1)*60); // 1 min
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_A);

	TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);

}

void Timer0IntHandler(void){

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // clear the timer interrupt

    if (flag == 0){
        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, 0x00);
    }
    else if (flag == 1){
        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_1);
    }
    else if (flag == 2){
        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, 0x00);
    }
    else if (flag == 3){
        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, 0x00);
        }
    else if(flag == 4){
        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_1);
    }
    else if (flag == 5){
        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_1);
    }
    else if (flag == 6){
        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, 0x00);
        flag = 0;
        return;

    }

    flag++;


}
