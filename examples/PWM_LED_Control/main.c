#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#include "driverlib/pwm.h"

#include <string.h>


int main()
{
  unsigned int i = 1;

  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

  SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

  GPIOPinConfigure(GPIO_PF1_M1PWM5);
  GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);


  //uint32_t Period, dutyCycle;


  PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
  PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 100);


  PWMGenEnable(PWM1_BASE, PWM_GEN_2);
  PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);


  while(1){

    for(i=1; i <= 100;i++){
      PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, i);
      SysCtlDelay(1333333);
    }

    for(i=100; i >= 1;i--){
      PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, i);
      SysCtlDelay(1333333);
    }

  }

}
