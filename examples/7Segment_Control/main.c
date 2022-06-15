#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int pins[10] = { 0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x18 }; //Common Anode
int i,j;
int ports[2] = {0x01,0x02,0x04, 0x08};


void segDisplay(int port, int num){

    GPIOPinWrite(ports[port],0x7F, pins[num]);

}

int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0x0F);

    while(1)
        {
            for (j = 0; j<=3; j++)
            {
                GPIOPinWrite(GPIO_PORTD_BASE,0x0F, ports[j]);

                for(i = 0; i<=9; i++)
                   {

                    GPIOPinWrite(GPIO_PORTB_BASE,0xFF, pins[i]);
                    //segDisplay(j, i);
                    SysCtlDelay(1333333);
                   }
                //SysCtlDelay(1333333);
            }

        }
}
