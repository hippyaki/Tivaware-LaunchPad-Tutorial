#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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
#include "driverlib/i2c.h"

#define SLAVE_ADDRESS1 0X3C //address of slave
#define SLAVE_ADDRESS2 0X4C //address of slave

void InitConsole(void)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        UARTClockSourceSet(UART0_BASE,UART_CLOCK_PIOSC);
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
        UARTStdioConfig(0,9600,16000000);
    }

void I2C0_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE,GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE,GPIO_PIN_3);

    //HWREG9I2C0_BASE + I2C_O_MCR) |=0X01
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(),false);
}

void I2C0_Send(uint16_t device_address, uint8_t device_data)
{
    //uint32_t stat;
    I2CMasterSlaveAddrSet(I2C0_BASE, device_address,false)

    //stat=I2CMasterLineStateGet(I2C0_BASE);
    //UARTprintf("Status before =%d",stat) ;

    //PUT DATA
    ; I2CMasterDataPut(I2C0_BASE, device_data);

    //transmit data
    UARTprintf("data sent to slave");
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
}
int main(void)
{
    uint32_t ui32DataTx;
    uint32_t status;

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);

    I2C0_Init();
    InitConsole();

    I2CMasterIntEnable(I2C0_BASE);
    IntMasterEnable();

    UARTprintf("I2C Slave Interrupt Example ->");
    UARTprintf("\n Module = I2C0");
    UARTprintf("\n Mode = Receive interrupt on the Slave module");
    UARTprintf("\n Rate = 100kbps\n\n");

    while(1)
    {
        if(UARTCharsAvail(UART0_BASE))
        {
            ui32DataTx= UARTCharGet(UART0_BASE);
            UARTprintf("Transferring from master -> slave\n");
            UARTprintf(" sending: '%c'", ui32DataTx);

            I2C0_Send(SLAVE_ADDRESS1, ui32DataTx); //0x3C
            I2C0_Send(SLAVE_ADDRESS2, ui32DataTx); //0x4C
        }
    }
}
