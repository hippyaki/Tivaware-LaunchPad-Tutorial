#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"


int main(void)
{
    char x;

        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        GPIOPinConfigure(GPIO_PC4_U1RX);
        GPIOPinConfigure(GPIO_PC5_U1TX);

        GPIOPinTypeUART(GPIO_PORTA_BASE,0x03);
        GPIOPinTypeUART(GPIO_PORTC_BASE,0x30);

        UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
        UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

        UARTStdioConfig(0, 9600, 16000000);
        UARTStdioConfig(1, 9600, 16000000);

        int i = 0;
        while(1){

            while(UARTCharsAvail(UART1_BASE)){

                x = UARTCharGet(UART1_BASE);
                UARTCharPut(UART0_BASE, x);
            }

        }

}
