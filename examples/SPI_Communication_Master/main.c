#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"
#include "driverlib/ssi.h"

int main()
{
uint32_t text[7];
uint32_t send;
text[0]='A';
text[1]='B';
text[2]='C';
text[3]='D';
text[4]='E';
text[5]='F';
text[6]='G';

//clock configuration
SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);

//SPI CONFIGURATION
SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
GPIOPinConfigure(GPIO_PD0_SSI3CLK);
GPIOPinConfigure(GPIO_PD1_SSI3FSS);
GPIOPinConfigure(GPIO_PD2_SSI3RX);
GPIOPinConfigure(GPIO_PD3_SSI3TX);
SSIConfigSetExpClk(SSI3_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_0,SSI_MODE_SLAVE,4000000,8);
SSIEnable(SSI3_BASE);

//UART CONFIGURATION
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
GPIOPinConfigure(GPIO_PA0_U0RX);
GPIOPinConfigure(GPIO_PA1_U0TX);
GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
UARTStdioConfig(0, 9600, 16000000);
UARTprintf("SLAVE\n");

////////switch 1 configurtion
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);


while(1)
{
while(SSIBusy(SSI3_BASE))
{

}
if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
{
int i=0;
for(i=0;i<7;i++)
{
send=text[i];
SSIDataPut(SSI3_BASE,send);
SysCtlDelay(13333333);
UARTprintf("DATA SENT TO SLAVE =%c\n",send);
}
}
}





}
