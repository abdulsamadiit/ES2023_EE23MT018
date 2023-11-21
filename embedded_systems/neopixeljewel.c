#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"



static void configure_system_clock(void);

static void code_one(void);
static void code_zero(void);
static void reset(void);

static void one_byte(void);
static void zero_byte(void);

static void green_led(void);
static void red_led(void);
static void blue_led(void);
static void white_led(void);
static void black_led(void);


static void set_rgb(int,int,int);


static void delay_ms(uint32_t);



void delay_ms(uint32_t ui32Ms) {
    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000
    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}





void configure_system_clock(void) { // Set the system clock to 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}


//SysCtlDelay(x) gives 3x cycles delay
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


void reset(void) {
    GPIO_PORTF_DATA_R = 0x00;
    SysCtlDelay(700);//60us > 50 us
}

void one_byte(void) {// byte 0xFF
    code_zero();code_one();code_one();code_one();
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

void set_rgb(int r,int g,int b)
{
    if (g==0 & b==0 & r==255)
    {
        red_led();
    }
    else if ( g==255 & b==0 & r==0 )
    {
        green_led();
    }
    else if (g==0 & b==255 & r==0 )
    {
        blue_led();
    }
    else if (g==255 & b==255 & r==255 )
    {
        white_led();
    }
    else if (g==255 & b==0 & r==255 )
    {
        one_byte(); //g
        zero_byte();//g
        one_byte();//r

    }
    else if (g=255 & b==255 & r==0)
    {
        one_byte();//g
        one_byte();//b
        zero_byte();//r
    }
    else if (g=0 & b==255 & r==255)
    {
            zero_byte();//g
            one_byte();//b
            one_byte();//r
        }
    else
        {
           black_led();
        }

}
