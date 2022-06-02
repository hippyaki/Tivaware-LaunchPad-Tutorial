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

    while(1)
    {

        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_1);
        SysCtlDelay(1333333);

        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, !(GPIO_PIN_1));
        SysCtlDelay(1333333);


    }

}
