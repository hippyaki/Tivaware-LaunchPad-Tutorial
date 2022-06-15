#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"

int main(){

   uint32_t RX_text[6];
   int i = 0;

   SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);

   SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

   GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

   GPIOPinConfigure(GPIO_PD0_SSI3CLK);
   GPIOPinConfigure(GPIO_PD1_SSI3FSS);
   GPIOPinConfigure(GPIO_PD2_SSI3RX);
   GPIOPinConfigure(GPIO_PD3_SSI3TX);

   SSIConfigSetExpClk(SSI3_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_SLAVE, 4000000, 8);
   SSIEnable(SSI3_BASE);

   SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

   GPIOPinConfigure(GPIO_PA0_U0RX);
   GPIOPinConfigure(GPIO_PA1_U0TX);

   GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);

   UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
   UARTStdioConfig(0, 9600, 16000000);
   UARTprintf("MASTER \n");

   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU );

   while(1){

       while(SSIDataGetNonBlocking(SSI3_BASE, &RX_text[0])){

       }

       while(SSIBusy(SSI3_BASE)){

       }

           for(i=0; i<6; i++){

               SSIDataGet(SSI3_BASE, &RX_text[i]);
               SysCtlDelay(40000000/3);
               UARTprintf("Data Received from Master = %c", RX_text[i]);

           }
   }

}
