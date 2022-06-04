/**
* main.c
*/
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
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"


// Motor - VBus & pinOut(M.D.), Motor Driver - VBus -> VCC

int main(void)
{
     unsigned int i=1;
     SysCtlClockSet(SYSCTL_SYSDIV_1| SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_USE_OSC);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // enable PWM module 1
     SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

     GPIOPinConfigure(GPIO_PD0_M1PWM0);
     GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_0);

     PWMGenConfigure(PWM1_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN);
     PWMGenPeriodSet(PWM1_BASE,PWM_GEN_0,100);
     PWMGenEnable(PWM1_BASE,PWM_GEN_0);
     PWMOutputState(PWM1_BASE,PWM_OUT_0_BIT,true);

while(1)
{
    while(i<=100)
    {
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,i);
            SysCtlDelay(133333);
            i++;
    }

    SysCtlDelay(133333);

    while(i>1)
    {
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,i);
            SysCtlDelay(133333);
            i--;
    }
    SysCtlDelay(133333);
}
return 0;
}
