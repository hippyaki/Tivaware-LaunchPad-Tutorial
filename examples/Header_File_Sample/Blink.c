/*
 * GPIO.c
 *
 *  Created on: 02-Jun-2022
 *      Author: Aksha
 */

#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"


void GPIO_Init(){

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

}

void Blink(){

    while(1)
        {

            GPIOPinWrite(GPIO_PORTF_BASE,0x0E, 0x0E);
            SysCtlDelay(1333333);

            GPIOPinWrite(GPIO_PORTF_BASE,0x0E, 0x00);
            SysCtlDelay(1333333);


        }

}

void LEDon(char pin){

    if (pin == 'R'){

        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_1);

    }
    else if (pin == 'B'){

        GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_2);

    }
    else if (pin == 'G'){

            GPIOPinWrite(GPIO_PORTF_BASE,0x0E, GPIO_PIN_3);

        }

    SysCtlDelay(1333333);

}

void LEDoff(){

    GPIOPinWrite(GPIO_PORTF_BASE,0x0E, 0x00);
    SysCtlDelay(1333333);

}
