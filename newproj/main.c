#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "sysctl.h"

/*
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

void delay_50ns(float del)
{//GENERATES 50NS
    del = del * ( SysCtlClockGet() / 3.0 * 5.0 / 100000000.0 );
    uint32_t delay = (uint32_t)del;
    SysCtlDelay(delay+1);
   // return delay;
}
*/

//SysCtlDelay(x) gives 3x cycles
void code_zero(void) {
    GPIO_PORTF_DATA_R = 0x08; //green led on
    SysCtlDelay(4);//0.4us
    GPIO_PORTF_DATA_R = 0x00;
    SysCtlDelay(12);//0.85us

}
void code_one(void) {
    GPIO_PORTF_DATA_R = 0x08; //red led on
    SysCtlDelay(9); //0.8 us
    GPIO_PORTF_DATA_R = 0x00;
    SysCtlDelay(6);// 0.45us
}

/*
//2-red,4-blue
void code_zero(void) {
    GPIO_PORTF_DATA_R = 0x08; //green led on
    delay_50ns(8);//0.4us
    GPIO_PORTF_DATA_R = 0x00;
    delay_50ns(17);//0.85us

}
void code_one(void) {
    GPIO_PORTF_DATA_R = 0x08; //red led on
    delay_50ns(16); //0.8 us
    GPIO_PORTF_DATA_R = 0x00;
    delay_50ns(9);// 0.45us
}*/
void reset(void) {
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

void green_led(void)
{
    one_byte();//g
    zero_byte();//r
    zero_byte();//b
}
void red_led(void)
{
    zero_byte();//g
    one_byte();//r
    zero_byte();//b
}
void blue_led(void)
{
    zero_byte();//g
    zero_byte();//r
    one_byte();//b
}

void white_led(void)
{
    one_byte();one_byte();one_byte();
}


void black_led(void)
{
    zero_byte();zero_byte();zero_byte();
}




void configure_system_clock(void) { // Set the system clock to 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}


void TURN_ON(void)
{


        red_led();
        black_led();black_led();black_led();black_led();black_led();black_led();

        reset();
        delay_ms(2000);
}




void main(void) {
    configure_system_clock(); // configure_system_clock for 40Mhz;
    SYSCTL_RCGC2_R |= 0x00000020;      /* enable clock to GPIOF */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;     /* unlock commit register */
    GPIO_PORTF_CR_R = 0x01;             /* make PORTF0 configurable */
    GPIO_PORTF_DIR_R = 0x0E;            /* set PORTF3+PORTF2+PORTF1 pin as output (LED) pin */
    GPIO_PORTF_DEN_R = 0x1F;            /* set PORTF pins 4-3-2-1 as digital pins */
    GPIO_PORTF_PUR_R = 0x11;            /* enable pull up for pin 4 and 0 */

    //uint32_t cycles = delay_50ns(600.0);
    //uint32_t cycles2 = delay_50ns(900.0);
    //uint32_t cycles3 = delay_50ns(990.0);
while(1)
   {

        TURN_ON();

   }

}
