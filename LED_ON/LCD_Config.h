/*****************************************************/
/********************NAME    : MARIAM   ****************/
/********************DATE    : 19/9/21  ****************/
/********************SWC     : LCD      ****************/
/********************VERSION :1.0       ****************/
/********************************************************/
#ifndef LCD_CONFIGURE_H
#define LCD_CONFIGURE_H


/*
 * Choose LCD Data length Mode :
 * HLCD_8BIT or HLCD_4BIT
 */
#define HLCD_MODE		  	HLCD_4BIT

#define LCD_U8_CONTROL_PORT     PORTD
#define LCD_U8_DATA_PORT        PORTC

#define LCD_U8_RS_PIN           PIN0
#define LCD_U8_RW_PIN           PIN1
#define LCD_U8_E_PIN            PIN2

u8 LCD_DATA_BINS_4BIT_MODE[4]= {PIN4,PIN5,PIN6,PIN7};




#endif
