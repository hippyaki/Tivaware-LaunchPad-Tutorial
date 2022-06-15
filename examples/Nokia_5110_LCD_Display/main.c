#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"

#define rst GPIO_PIN_4
//#define cs GPIO_PIN_5
#define dc GPIO_PIN_6
#define led GPIO_PIN_7

int Alh_ltr[][5]={
    {0x7e, 0x11, 0x11, 0x11, 0x7e}
    ,{0x7f, 0x49, 0x49, 0x49, 0x36}
    ,{0x3e, 0x41, 0x41, 0x41, 0x22}
    ,{0x7f, 0x41, 0x41, 0x22, 0x1c}
    ,{0x7f, 0x49, 0x49, 0x49, 0x41}
    ,{0x7f, 0x09, 0x09, 0x09, 0x01}
    ,{0x3e, 0x41, 0x49, 0x49, 0x7a}
    ,{0x7f, 0x08, 0x08, 0x08, 0x7f}
    ,{0x00, 0x41, 0x7f, 0x41, 0x00}
    ,{0x20, 0x40, 0x41, 0x3f, 0x01}
    ,{0x7f, 0x08, 0x14, 0x22, 0x41}
    ,{0x7f, 0x40, 0x40, 0x40, 0x40}
    ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
    ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
    ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
    ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
    ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
    ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
    ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
    ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
    ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
    ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
    ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
    ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
    ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
    ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
    ,{0x00, 0x00, 0x00, 0x00, 0x00} // BLANK
};

void nokia_map(char data)
{
    int pos;
    char str[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for(i=0;i<26;i++)
    {
        if(str[i]==data)
        {
            pos=i;
        }
    }

    int Alh_ltr[][5]={
        {0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
        ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
        ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
        ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
        ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
        ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
        ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
        ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
        ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
        ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
        ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
        ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
        ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
        ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
        ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
        ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
        ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
        ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
        ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
        ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
        ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
        ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
        ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
        ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
        ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
        ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
        ,{0x00, 0x00, 0x00, 0x00, 0x00} // BLANK
        };
    nokia_data(Alh_ltr[pos]);

}
void LCD_Clear()
{
    int k;
    GPIOPinWrite(GPIO_PORTA_BASE,dc,dc);
    //GPIOPinWrite(GPIO_PORTA_BASE,cs,0x00);
    for(k=0;k<=503;k++)
    {
        SSIDataPut(SSI3_BASE,0X00);
    //SysCtlDelay(40000000/3);
    }
    GPIOPinWrite(GPIO_PORTA_BASE,dc,!(dc));
}

void nokia_rst()
{
    GPIOPinWrite(GPIO_PORTA_BASE,rst,0x00);// reset enabled
    SysCtlDelay(133333);
    GPIOPinWrite(GPIO_PORTA_BASE,rst,0x10); //reset disabled
}

void Int_it()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinTypeSSI(GPIO_PORTD_BASE ,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,rst); //A4
    // GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,cs); //A5
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,dc); //A6
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,led); //A7

    GPIOPinConfigure(GPIO_PD0_SSI3CLK);
    GPIOPinConfigure(GPIO_PD1_SSI3FSS);
    GPIOPinConfigure(GPIO_PD2_SSI3RX);
    GPIOPinConfigure(GPIO_PD3_SSI3TX);

    SSIConfigSetExpClk(SSI3_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,4000000,8);
    SSIEnable(SSI3_BASE);

    GPIOPinWrite(GPIO_PORTA_BASE,led,led); // turn backlight on

    nokia_rst(); //reset
    nokia_cmd(0X21); //Addition mode
    nokia_cmd(0XC0); //set the voltage
    nokia_cmd(0X07); //set temp coeff
    nokia_cmd(0X13); //set value of volt bios sys.
    nokia_cmd(0X20); //basic mode
    nokia_cmd(0X0C); //display result in normal mode
}

void nokia_cmd(char data)
{
    // GPIOPinWrite(GPIO_PORTA_BASE,cs,!(cs));
    GPIOPinWrite(GPIO_PORTA_BASE,dc,!(dc));
    while(SSIBusy(SSI3_BASE))
    {

    }
    SSIDataPut(SSI3_BASE,data);
    SysCtlDelay(40000000/3);
    //UARTprintf("Data Sent to slave=%c\n",data);
    // GPIOPinWrite(GPIO_PORTA_BASE,cs,cs);
    GPIOPinWrite(GPIO_PORTA_BASE,dc,dc);
}

void nokia_data(int data[5])
{
    int i;
    GPIOPinWrite(GPIO_PORTA_BASE,dc,dc);
    // GPIOPinWrite(GPIO_PORTA_BASE,cs,!(cs));
    while(SSIBusy(SSI3_BASE))
    {

    }
    for (i = 0; i<5; i++){
        SSIDataPut(SSI3_BASE,data[i]);
        SysCtlDelay(40000000/3);
    }

    //SysCtlDelay(40000000/3);
    //UARTprintf("Data Sent to slave=%c\n",data);
    // GPIOPinWrite(GPIO_PORTA_BASE,cs,cs);
    GPIOPinWrite(GPIO_PORTA_BASE,dc,!(dc));
}

int strlen_nokia(unsigned char *d)
{
    int len=0;
    int i;
    for(i=0;d[i]!='\0';i++)
    {
    len++;
    }
    return len;
}

void cursorPosition(uint8_t xpos,uint8_t ypos)
{
    nokia_cmd(0x80 + xpos);
    SysCtlDelay(10);
    nokia_cmd(0x40 + ypos);
    SysCtlDelay(10);
}

int main()
{

    char str[]="AKSHAYAN";

    Int_it();
    SysCtlDelay(1333333);
    LCD_Clear();
    SysCtlDelay(1333333);
    int j;

    /*cursorPosition(10,1);
            //d[5]=nokia_map(str[j]);

    nokia_data(Alh_ltr[0]); // print A*/
    cursorPosition(10,1);
    nokia_data(Alh_ltr[26]);

    for(j=0;j<strlen_nokia(str);j++)
    {
        int pos = j+1;
        cursorPosition(pos*7,1);
        nokia_map(str[j]);

        SysCtlDelay(1333333);
    }

    while(1)
    {

    }
}
