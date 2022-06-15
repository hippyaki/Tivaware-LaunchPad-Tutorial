#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/flash.h"
#include "driverlib/flash.c"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"


int main(void)
{
    char x;

        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);


        GPIOPinTypeUART(GPIO_PORTA_BASE,0x03);

        UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

        UARTStdioConfig(0, 9600, 16000000);

        //int i = 0;
        while(1){

            if(UARTCharsAvail(UART0_BASE) ){

               x = UARTCharGet(UART0_BASE);

               if(x != 13 ){

                   UARTCharPut(UART0_BASE, x);
               }
               else{
                   UARTCharPut(UART0_BASE, '\r');
                   UARTCharPut(UART0_BASE, '\n');
               }

              }

        }

}
