#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "driverlib/pin_map.h"
#include "driverlib/flash.h"
#include "driverlib/usb.h"
/**
 * main.c
 */
int command(int cmd)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X10);                       //     4 3 2    1 0 0
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, (data & 0Xf0)>>4);           // higher nibble   7 6 5 4 3 2 1 0
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X10);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, (data & 0X0f));
    SysCtlDelay(50000);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X00);                       // enable off
}
int data(int data)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X1C);                       //     4 3 2    1 1 0
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, (data & 0Xf0)>>4);          // higher nibble   7 6 5 4 3 2 1 0
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X1C);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, (data & 0X0f));
    SysCtlDelay(50000);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X00);   //enable off
}
int initialization()
{
    SysCtlDelay(50000);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X00);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0X03);
    SysCtlDelay(50000);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X00);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0X03);
    SysCtlDelay(50000);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X00);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0X03);
}
int main(void)
{
    int i;
    char val ="Aki";

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);   // EN RS RW
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0X1C);    //4 3 2
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0X0F);    //3 2 1 0
    int arr[]={0X0F,0X01,0X80};
    for(i=0; i<3;i++)
    {
         command(arr[i]);
    }
    for(i=0; i<5;i++)
    {
        data()
    }
}
