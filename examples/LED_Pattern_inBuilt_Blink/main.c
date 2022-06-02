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
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

        unsigned arr1[] = {0x00, 0x02, 0x04, 0x08, 0x0A, 0x0F, 0x06, 0x0E};
        unsigned arr2[] = {0x00, 0x02, 0x04, 0x08, 0x0A, 0x0F, 0x06, 0x0E};

        //unsigned arr2[] = {0x00, 0x02, 0x08, 0x0A, 0x04, 0x06, 0x0C, 0x0E};

        unsigned int i;
        unsigned int j = 0;

        while(1){
            for (i = 0; i<=sizeof(arr1); i++){

                GPIOPinWrite(GPIO_PORTF_BASE, 0x0E, arr2[j]);
                SysCtlDelay(1333333);
                j++;
                if (j == 8){

                    j = 0;
                    i = 0;

                }
            }
        }

    }

