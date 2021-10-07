/*
 * File        : LCD_Program.c
 */
#include"LSTD_TYPES.h"
#include"LBIT_MATH.h"
#include"MDIO_Interface.h"
#include"LCD_private.h"
#include "LBIT_MATH.h"
#include"LCD_Interface.h"
#include"LCD_Config.h"
#include "LCD_private.h"
#include<avr/delay.h>
#include "MDIO_Interface.h"
/*********************************************************/

void LCD_VoidInit(void)
{
    /*config LCD PINS */
    /*set pins0,1,2 as output for rs,rw,enable pins*/
    MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,OUTPUT_PIN);
    MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,OUTPUT_PIN);
    MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,OUTPUT_PIN);

    #if (HLCD_MODE == HLCD_8BIT)
    /*set porta as output for data or command*/
    MDIO_VoidSetPortDirection(LCD_U8_DATA_PORT,OUTPUT_PORT);
    /********************INTIALIZATION*****************/
    /*wait more than 30 ms after VDD raises to 4.5*/
    _delay_ms(40);

    /*function set*/
    LCD_VoidSendCommand(FUNCTIONSET);
    _delay_ms(1);
    LCD_VoidSendCommand(DISPLAY_ON_OFF);
    _delay_ms(1);
    LCD_VoidSendCommand(DISPLAY_CLEAR);
    #elif (HLCD_MODE == HLCD_4BIT)
    for (u8 i=0;i<4;++i)
    {
        MDIO_VoidSetPinDirection(LCD_U8_DATA_PORT,LCD_DATA_BINS_4BIT_MODE[i],OUTPUT_PIN);
    }

	_delay_ms(30);
	LCD_VoidSendCommand4Bit(0x20);
	LCD_VoidSendCommand4Bit(0x20);
	LCD_VoidSendCommand4Bit(0x80);
	_delay_ms(1);
	LCD_VoidSendCommand4Bit(0x00);
	LCD_VoidSendCommand4Bit(0b11000000);
	_delay_ms(1);
	LCD_VoidSendCommand4Bit(0x00);
	LCD_VoidSendCommand4Bit(0x10);
	_delay_ms(2);
#endif

}
void LCD_VoidSendCommand4Bit(u8 Copy_U8Command)
{
    MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,LOW);
    /*PIN RW=0*/
    MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
    /*COMMAND*/

    for (u8 i=4;i<=7;++i)
        {
    	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,LCD_DATA_BINS_4BIT_MODE[i-4],GET_BIT(Copy_U8Command,i));
        }

    /*ENABLE SEQUANCE**/
    MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
    _delay_ms(1);
    MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
    _delay_ms(2);
}
void LCD_VoidSendChar(u8 Copy_U8Data)
{
	 /*PIN RS=1*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,HIGH);
	 /*PIN RW=0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
#if (HLCD_MODE == HLCD_8BIT)
	 /*DATA*/
	 MDIO_VoidSetPortValue(LCD_U8_DATA_PORT,Copy_U8Data);
      /*Enable Sequance*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_ms(2);
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
#elif (HLCD_MODE == HLCD_4BIT)
	   for (u8 i=4;i<=7;++i)
	        {
		   MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,LCD_DATA_BINS_4BIT_MODE[i-4],GET_BIT(Copy_U8Data,i));
	        }

		 /*ENABLE SEQUANCE**/
		 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
		 _delay_ms(1);
		 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);

		 for (u8 i=0;i<=3;++i)
			        {
				   MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,LCD_DATA_BINS_4BIT_MODE[i],GET_BIT(Copy_U8Data,i));
			        }

		 /*ENABLE SEQUANCE**/
		 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
		 _delay_ms(1);
		  MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
		  _delay_ms(2);
#endif
}

void LCD_VoidSendCommand(u8 Copy_U8Command)
{	/**PIN RS =0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,LOW);
	 /*PIN RW=0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
#if (HLCD_MODE == HLCD_8BIT)
	 /*COMMAND*/
	 MDIO_VoidSetPortValue(LCD_U8_DATA_PORT,Copy_U8Command);
	 /*ENABLE SEQUANCE**/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
    _delay_ms(1);
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
#elif (HLCD_MODE == HLCD_4BIT)
	 for (u8 i=4;i<=7;++i)
	 	        {
	 		   MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,LCD_DATA_BINS_4BIT_MODE[i-4],GET_BIT(Copy_U8Command,i));
	 	        }
		 /*ENABLE SEQUANCE**/
		 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
		 _delay_ms(1);
		 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);

		 for (u8 i=0;i<=3;++i)
		{
		 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,LCD_DATA_BINS_4BIT_MODE[i],GET_BIT(Copy_U8Command,i));
		 }

		 /*ENABLE SEQUANCE**/
		 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
		 _delay_ms(1);
		  MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
		  _delay_ms(2);
#endif
}


void LCD_VoidSendString(char * Copy_U8PtrString)
{
	u8 count=0;
	//while you don't reach to the end of your string enter the loop
	while(( Copy_U8PtrString[count])!='\0')
	{
		//print the selected char
		LCD_VoidSendChar(Copy_U8PtrString[count]);
		//increment to print the next char
		count++;
	}
}
/*___________________________THE END OF PRINT STRING FUNCTION____________________________*/



void LCD_VoidSendNum(u16 CopyNum)
{
	u16 temp=CopyNum;
	u8 count=0;
	/*this loop to count the digits of input number */
	/*this loop is a commmon between the 2 codes below*/
	while (temp!=0)
	{
		temp=temp/10;
		count++;
	}

		u16 mul;
		for(u8 j=1;j<count;j++)
				 {
			         mul=1;
					 for(u8 i =0;i<count-j;i++)
					 {mul=mul*10;  //in this loop we multiply 10 in itself ex :10*10=100
					 }
					 LCD_VoidSendChar((CopyNum/mul)+'0'); //ex : 256/100 = 2 then add ascii of 0 to print it
					 CopyNum=CopyNum%mul;   //256%100=56 ==> we do this to get red of (digit 2)
				}

		 LCD_VoidSendChar(CopyNum+'0'); //we print the last digit 6 as it will not be printed in the previous loop
}

/*__________________________________________________________________________________________*/



void LCD_VoidClearScreen(void)
{
	LCD_VoidSendCommand(0x01);
	_delay_ms(5);

}


void LCD_VoidShiftLeft(void)
{
    LCD_VoidSendCommand(0x18);
}


void LCD_VoidShiftRight(void)
{
    LCD_VoidSendCommand(0x1C);
}

void LCD_VoidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8Address;
	if(Copy_u8XPos==0)
	{
		Local_u8Address=Copy_u8YPos;

	}
	else if(Copy_u8XPos==1)
		{
			Local_u8Address=Copy_u8YPos+0x40;

		}
	LCD_VoidSendCommand(Local_u8Address+128);

}

void LCD_VoidWriteSpecialCharacter(u8* Copy_u8Pattern,u8 Copy_u8PosInMemory)
{
	u8 localCGramAddress;

	localCGramAddress=Copy_u8PosInMemory*8;
	LCD_VoidSendCommand(localCGramAddress+64);
	for(u8 i=0;i<8;++i)
	{
		LCD_VoidSendChar(Copy_u8Pattern[i]);
	}


}
void LCD_VoidDisplaySpecialCharacter(u8 Copy_u8PosInMemory,u8 Copy_u8XPosition,u8 Copy_u8YPosition)
{
    LCD_VoidGoToXY(Copy_u8XPosition,Copy_u8YPosition);

    LCD_VoidSendChar(Copy_u8PosInMemory);

}







