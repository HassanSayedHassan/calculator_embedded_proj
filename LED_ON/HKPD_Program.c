/*
 * File        : HKPD_Program.c
 * Description : This file includes Keypad Driver implementations for Atmega32
 * Author      : Ahmed Elmogy Embedded SW Engineer 
 * Date        : 9/2/2020
 * Git account : https://github.com/AhmedElmougy
 * mail        : ahmed.m.elmogy@gmil.com 
 */

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_Interface.h"
#include "HKPD_Config.h"
#include "HKPD_Private.h"
#include "HKPD_Interface.h"




/* 
 * Prototype   : void HKPD_voidInitializeKeypad(void);
 * Description : initialize 4X4 keypad at a given port set 4 pins output and 4 pins input
 * Arguments   : void
 * Return      : void  
 */
 void HKPD_voidInitializeKeypad(void)
 {
	
	 /*for loop to scan all keypad columns and rows*/
	 for (u8 i = 0 ; i<4 ; i++)
	 {
	 	 /*set column current bit in ColumnArray[] OUTPUT*/
		 MDIO_VoidSetPinDirection(KEYPAD_PORT,HKPD_u8ColumnArray[i],OUTPUT_PIN);
	
		 /*set current bit in RowArray[] INPUT*/
		 MDIO_VoidSetPinDirection(KEYPAD_PORT,HKPD_u8RowArray[i],INPUT_PIN);
		
		 /*Enable pull up resistor for current bit in RowArray[]*/

		 MDIO_VoidSetPinValue(KEYPAD_PORT,HKPD_u8RowArray[i],MDIO_EN_PULL_UP_RES);
	 }/*end of for loop*/
	
 }/*end of HKPD_voidInitializeKeypad()*/


/*
 * Prototype   : u8 HKPD_u8GetPressedKey(void);
 * Description : Return which key in the keypad has been pressed
 * Arguments   : void
 * return      : u8 pressed key
 */
 u8 HKPD_u8GetPressedKey(void)
 {
	 
	/*for loop to set all column pins HIGH*/
	for (u8 i = 0; i<4 ;i++ )
	{
		/*set current pin in ColumnArray HIGH*/
		MDIO_VoidSetPinValue(KEYPAD_PORT,HKPD_u8ColumnArray[i],HIGH);
		
	}/*end of for loop*/
	
	/*for loop to scan all keypad columns*/
	for (u8 i = 0 ; i<4 ; i++)
	{
		/*set current column pin low to test all row pins to find out which button has been pressed*/
		MDIO_VoidSetPinValue(KEYPAD_PORT,HKPD_u8ColumnArray[i],LOW);
		
		/*for loop to scan and test all keypad row pins*/
		for (u8 j = 0 ; j<4 ; j++)
		{
			/*check current row pin value*/
			if ( LOW == MDIO_U8GetPinValue(KEYPAD_PORT,HKPD_u8RowArray[j]) )
			{
				/*return pressed button value*/
				return KeyPadArr[j][i];
			}	
		}/*end of for loop*/
		
		/*set current column pin HIGH again*/
		MDIO_VoidSetPinValue(KEYPAD_PORT,HKPD_u8ColumnArray[i],HIGH);
		
	}/*end of for loop*/	
	
	/*Report no Button pressed*/
	return '?';
		
}/*end of HKPD_u8GetPressedKey()*/

/*===================================================================
 * EOF
 *===================================================================*/
