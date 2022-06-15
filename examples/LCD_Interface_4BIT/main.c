
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main()
{
    uint32_t value=1;
    char kus[10];

    uint32_t i=10;
    unsigned char data[10]="Aki";
    char strr[10];
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);

    LCD_init();
    LCD_Clear();// Clear the Screen
    SysCtlDelay(13333333);

    LCD_Command(0x0E); //Display ON, Cursor blinking
    SysCtlDelay(13333333);

    LCD_Clear(); // Clear the Screen
    SysCtlDelay(13333333);

    LCD_cursorPosition(2,6);// Cursor position
    Display_string(data); // Display Data
    SysCtlDelay(13333333);

    LCD_cursorPosition(1,2);// Cursor position
    Display_Digits(value); // Display Integer digits
    SysCtlDelay(13333333);


    // Not running after above two Displays

    LCD_cursorPosition(2,9);// Cursor position
        Display_Digits(value); // Display Integer digits
        SysCtlDelay(13333333);

//    LCD_cursorPosition(1,7);
//    Display_FloatValue(29.1997);
//    SysCtlDelay(13333333);
    /*
    value=value+1;
    *kus= i_to_a(value);
    LCD_cursorPosition(2,2);// Cursor position
    Display_string(kus); // Display Data
    SysCtlDelay(13333333);
    */

    while(1)
    {

    }

    }
