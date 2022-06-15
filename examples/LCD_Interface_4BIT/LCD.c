/*
 * LCD.c
 *
 *  Created on: Apr 18, 2022
 *      Author: Kushal Nesarkar
 */

/*                      LCD Commands:
 * |    Hex    |   Command to LCD Instruction Register  |
 * ------------------------------------------------------
 *      0X0F        LCD ON , Cursor ON
 *      0x01        Clear Screen
 *      0x02        Return Home
 *      0x04        Shift Cursor to Left
 *      0x05        Shift Display right
 *      0x06        Shift Cursor to Right
 *      0x07        Shift Display left
 *      0x0E        Display On Cursor Blinking
 *      0X80        Force Cursor to Beginning of First line
 *      0XC0        Force Cursor to Beginning of Second line
 *      0X38        2 lines and 5×7 matrix
 *      0X83        Cursor line 1 position 3
 *      0x3C        Activate second line
 *      0X08        Display OFF, cursor OFF
 *      0X0C        Display ON, cursor OFF
 *      0XC1        Jump to second line, position 1
 *      0XC2        Jump to second line, position 2
 *
 */

/*
 * Pin Functions;
 *
 * RS=0  INSTRUCTION
 *    1  DATA REGISTER SELECTION
 *
 * RW=0  REGISTER WRITE
 *    1  REGISTER READ
 *
 * E=1  ENABLE
 *   0  Disable
 */


#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"
#include <math.h>
#include "float.h"

#define RS GPIO_PIN_0
#define RW GPIO_PIN_1
#define EN GPIO_PIN_2

#define D4 GPIO_PIN_4
#define D5 GPIO_PIN_5
#define D6 GPIO_PIN_6
#define D7 GPIO_PIN_7

unsigned char res1[10];
unsigned char* sflt[10];

void LCD_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,D4|D5|D6|D7);//D4,D5,D6,D7

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,RS|RW|EN);//RS,RW,En

    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(13333333);

    // Init 4 bit
//----1
    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X30);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);
//------2
    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X30);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);
//-------3
    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X30);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);
//-------4
    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X20);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);

    LCD_Command(0x0F);
    }

void LCD_Command(uint8_t c)
{
    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(c & 0xf0));
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);

    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);


    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(c & 0x0f)<<4);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);
}

void Display_character(unsigned char d)
{
      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d & 0xf0));
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);


      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d & 0x0f)<<4);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);
}

void Display_string(unsigned char *d)
{
      int len=0;
      int i=0;

      for(i=0;d[i]!='\0';i++)
      {
          len++;
      }

      for(i=0;i<len;i++)
      {
      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d[i] & 0xf0));
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);


      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d[i] & 0x0f)<<4);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);

      }
}

void Display_Digits(uint32_t value)
{
//    char *str = i_to_a(value);
    Display_string(i_to_a(value));
//    return str;
}


void LCD_Clear()
{
    LCD_Command(0x01);
    SysCtlDelay(10);
}

void LCD_cursorPosition(uint8_t line,uint8_t pos)
{
    if(line==1)
    {
    LCD_Command(0x80 + pos);
    SysCtlDelay(10);
    }
    else
    {
        LCD_Command(0xC0 + pos);
        SysCtlDelay(10);
    }
}

int no_of_digits(int num)
{
    int digit_count = 0;

    while(num > 0)
    {
        digit_count++;
        num /= 10;
    }

    return digit_count;
}
char *i_to_a(int num)
{
    char *str;
    int digit_count = 0;

    if(num < 0)
    {
        num = -1*num;
        digit_count++;
    }

    digit_count += no_of_digits(num);
    str = malloc(sizeof(char)*(digit_count+1));

    str[digit_count] = '\0';

    while(num > 0)
    {
        str[digit_count-1] = num%10 + '0';
        num = num/10;
        digit_count--;
    }

    if(digit_count == 1)
        str[0] = '-';

    return str;
}

//---------


void Display_FloatValue(float xflt)
{
    int i=0;
    ftoa(xflt, res1, 4);
    for(i=0;i<10;i++)
    {
      sflt[i]=res1[i];
    }
   Display_string(&sflt);
}
