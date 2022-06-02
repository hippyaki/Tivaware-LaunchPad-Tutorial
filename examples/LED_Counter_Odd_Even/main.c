#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/**
 * main.c
 */
int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
    unsigned int num = 1;
    while(1){

        if (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
        {
            if (num%2 == 0){
               GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_1);
            }
            else{
                GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_2);
            }

        }
        else{
            if (num%2 == 0){
              GPIOPinWrite(GPIO_PORTF_BASE,0x0E, !(GPIO_PIN_1));
            }
            else{
                GPIOPinWrite(GPIO_PORTF_BASE,0x0E, !(GPIO_PIN_2));
            }
            num++;
        }
    }
}
