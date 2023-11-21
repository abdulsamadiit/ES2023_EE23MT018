#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "sysctl.h"
#include "neopixel.h"


void TURN_ON(void);

void delay_ms(uint32_t ui32Ms) {
    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000
    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}
void delay_us(uint32_t ui32Us) {
    SysCtlDelay(ui32Us * (SysCtlClockGet() / 3 / 1000000));
}
void delay_ns(uint32_t ui32Ns) {
    SysCtlDelay(ui32Ns * (SysCtlClockGet() / 3 / 100000000 ));
}
void delay_5ns(uint32_t del)
{
    del = del * ( SysCtlClockGet() / 3 * 5 / 100000000);
    SysCtlDelay(del);
}





//2-red,4-blue
void code_zero(void) {
    GPIO_PORTF_DATA_R = 0x08; //red led on
    delay_5ns(80);//0.4us
    GPIO_PORTF_DATA_R = 0x00;
    delay_5ns(170);//0.85us

}
void code_one(void) {
    GPIO_PORTF_DATA_R = 0x08; //red led on
    delay_5ns(160); //0.8 us
    GPIO_PORTF_DATA_R = 0x00;
    delay_5ns(90);// 0.45us
}
void reset() {
    GPIO_PORTF_DATA_R = 0x00;
    delay_us(60);//60us > 50 us
}

void one_byte(void) {// byte 0xFF
    code_one();code_one();code_one();code_one();
    code_one();code_one();code_one();code_one();
}

void zero_byte(void) { // byte 0x00
    code_zero();code_zero();code_zero();code_zero();
    code_zero();code_zero();code_zero();code_zero();
}

void green_led()
{
    one_byte();//g
    zero_byte();//r
    zero_byte();//b
}
void red_led()
{
    zero_byte();//g
    one_byte();//r
    zero_byte();//b
}
void blue_led()
{
    zero_byte();//g
    zero_byte();//r
    one_byte();//b
}

void white_led()
{
    one_byte();one_byte();one_byte();
}


void configure_system_clock(void) { // Set the system clock to 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}


void TURN_ON()
{

        configure_system_clock(); // configure_system_clock for 40Mhz;
        white_led();white_led();white_led();
        white_led();white_led();white_led();
        white_led();
        reset();
        delay_ms(2000);
}
