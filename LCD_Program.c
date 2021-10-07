
#include"LSTD_TYPES.h"
#include"LBIT_MATH.h"

#include"MDIO_Interface.h"
/*  HAL */
#include"LCD_private.h"
#include "LBIT_MATH.h"
#include"LCD_Interface.h"
#include"LCD_Config.h"
#include "LCD_Extra.h"
#include<avr/delay.h>

/*********************************************************/
void LCD_VoidSendChar(u8 Copy_U8Data)
{
	 /*PIN RS=1*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,HIGH);
	 /*PIN RW=0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
	 /*DATA*/
	 MDIO_VoidSetPortValue(LCD_U8_DATA_PORT,Copy_U8Data);
      /*Enable Sequance*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_ms(2);
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
	 
	 
}

void LCD_VoidSendCommand(u8 Copy_U8Command)
{	/**PIN RS =0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,LOW);
	 /*PIN RW=0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
	 /*COMMAND*/
	 MDIO_VoidSetPortValue(LCD_U8_DATA_PORT,Copy_U8Command);
	 /*ENABLE SEQUANCE**/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_us(2);
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
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


void LCD_VoidPosition(u8 CopyLine,u8 CopyPosition)
{
	if(CopyLine==LINE1)
	{
        /*0b10000000 ==> 0x80 (it is the 1st position on line1 in lcd)*/
		LCD_VoidSendCommand(0x80+CopyPosition);
	    _delay_ms(1);
	}
	else if(CopyLine==LINE2)
	{

		LCD_VoidSendCommand(0xC0+CopyPosition);
		 _delay_ms(1);
	}
	else ;
}

void LCD_VoidCLR()
{
	LCD_VoidSendCommand(0x01);
	_delay_ms(5);

}

void LCD_VoidInit()
{
	/*config LCD PINS */
	/*set pins0,1,2 as output for rs,rw,enable pins*/
	MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,OUTPUT_PIN);
    MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,OUTPUT_PIN);
    MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,OUTPUT_PIN);
	
	
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

/*	LCD_VoidSendCommand(ENTRY_MODE);
	_delay_ms(1);*/
	
}
void Lcd8_VoidShiftLeft()
{
    LCD_VoidSendCommand(0x18);
}


void Lcd8_Shift_Right()
{
    LCD_VoidSendCommand(0x1C);
}

void Lcd_GoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
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
void LCD_vidWriteExtraChar (u8 Y,u8 X)
{
    u8 iteration1,iteration2;

    /*DDRAM-->CGRAM*/
    LCD_VoidSendCommand(64);
	for(iteration1=0 ; iteration1<64 ; iteration1++)
	{
		LCD_VoidSendChar(ExtraChar[iteration1]);
	}
	/*CGRAM-->DDRAM*/
	LCD_VoidSendCommand(128);
	Lcd_GoToXY(Y,X);
	/*First eight character which saved at CGRAM*/
	for (iteration2=0; iteration2<=7 ; iteration2++)
	{
		/* Write bytes of DDRAM */
		LCD_VoidSendChar(iteration2);

		_delay_ms(5);
	}
}

void LCD_VoidWriteSpecialCharacter(u8* Copy_u8Pattern,u8 pos,u8 x,u8 y)
{
	u8 localCGramAddress;

	localCGramAddress=pos*8;
	LCD_VoidSendCommand(localCGramAddress+64);
	for(u8 i=0;i<8;++i)
	{
		LCD_VoidSendChar(Copy_u8Pattern[i]);
	}

	Lcd_GoToXY(1,5);

	LCD_VoidSendChar(pos);
}

void HLCD_VoidInit4BitMod(void)
{
	/*config LCD PINS */
	/*set pins0,1,2 as output for rs,rw,enable pins*/
	MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,OUTPUT_PIN);
    MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,OUTPUT_PIN);
    MDIO_VoidSetPinDirection(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,OUTPUT_PIN);


	/*set porta as output for data or command*/
	MDIO_VoidSetPortDirection(LCD_U8_DATA_PORT,OUTPUT_PORT);


	_delay_ms(30);
	LCD_VoidSendCommand4BitModeInit(0x20);
	LCD_VoidSendCommand4BitModeInit(0x20);
	LCD_VoidSendCommand4BitModeInit(0x80);
	_delay_ms(1);
	LCD_VoidSendCommand4BitModeInit(0x00);
	LCD_VoidSendCommand4BitModeInit(0b11000000); /////////////
	_delay_ms(1);
	LCD_VoidSendCommand4BitModeInit(0x00);
	LCD_VoidSendCommand4BitModeInit(0x10);
	_delay_ms(2);

}
void LCD_VoidSendCommand4BitModeInit(u8 Copy_U8Command)
{
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,LOW);
	 /*PIN RW=0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
	 /*COMMAND*/

	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN4,GET_BIT(Copy_U8Command,4));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN5,GET_BIT(Copy_U8Command,5));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN6,GET_BIT(Copy_U8Command,6));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN7,GET_BIT(Copy_U8Command,7));
	 /*ENABLE SEQUANCE**/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_ms(1);
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
	 _delay_ms(2);
}
void LCD_VoidSendCommand4BitMode(u8 Copy_U8Command)
{
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,LOW);
	 /*PIN RW=0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
	 /*COMMAND*/

	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN4,GET_BIT(Copy_U8Command,4));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN5,GET_BIT(Copy_U8Command,5));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN6,GET_BIT(Copy_U8Command,6));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN7,GET_BIT(Copy_U8Command,7));
	 /*ENABLE SEQUANCE**/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_ms(1);
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);

	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN4,GET_BIT(Copy_U8Command,0));
	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN5,GET_BIT(Copy_U8Command,1));
	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN6,GET_BIT(Copy_U8Command,2));
	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN7,GET_BIT(Copy_U8Command,3));
	 /*ENABLE SEQUANCE**/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_ms(1);
	  MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
	  _delay_ms(2);
}
void LCD_VoidSendData4BitMode(u8 Copy_U8Data)
{
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RS_PIN,HIGH);
	 /*PIN RW=0*/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_RW_PIN,LOW);
	 /*COMMAND*/

	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN4,GET_BIT(Copy_U8Data,4));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN5,GET_BIT(Copy_U8Data,5));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN6,GET_BIT(Copy_U8Data,6));
	MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN7,GET_BIT(Copy_U8Data,7));
	 /*ENABLE SEQUANCE**/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_ms(1);
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);

	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN4,GET_BIT(Copy_U8Data,0));
	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN5,GET_BIT(Copy_U8Data,1));
	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN6,GET_BIT(Copy_U8Data,2));
	 MDIO_VoidSetPinValue(LCD_U8_DATA_PORT,PIN7,GET_BIT(Copy_U8Data,3));
	 /*ENABLE SEQUANCE**/
	 MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,HIGH);
	 _delay_ms(1);
	  MDIO_VoidSetPinValue(LCD_U8_CONTROL_PORT,LCD_U8_E_PIN,LOW);
	  _delay_ms(2);

}



