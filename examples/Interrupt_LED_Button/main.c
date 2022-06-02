#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

void ISR_Switch1(void){

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0E);
    SysCtlDelay(1333333);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    SysCtlDelay(1333333);

    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
}

void ISR_Switch2(void){

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0E);
    SysCtlDelay(1333333);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
    SysCtlDelay(1333333);

    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0); //Switch 2 - pin 0(locked), Switch 1 - pin 4(unlocked)
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01; //(pin 0)

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

    IntEnable(INT_GPIOF);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOIntRegister(GPIO_PORTF_BASE, ISR_Switch1);
    GPIOIntRegister(GPIO_PORTF_BASE, ISR_Switch2);


}
