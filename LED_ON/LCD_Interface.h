#ifndef  LCD_INTERFACE_H
#define  LCD_INTERFACE_H


/*Create Your Custom Shape*/

/*u8 LCD_CustomShapes[]={
		14, 14, 4, 31, 4, 4, 10, 17, 		/// Man Shape
		0, 0, 14, 31, 31, 14, 0, 0 ,		/// Ball Shape
		0, 0,  0,  0,  0,  0, 0, 0 ,
		0, 0,  0,  0,  0,  0, 0, 0 ,
		0, 0,  0,  0,  0,  0, 0, 0 ,
		0, 0,  0,  0,  0,  0, 0, 0 ,
		0, 0,  0,  0,  0,  0, 0, 0
};*/


void LCD_VoidInit(void);
void LCD_VoidSendChar(u8 Copy_U8Data);
void LCD_VoidSendCommand(u8 Copy_U8Command);
void LCD_VoidSendCommand4Bit(u8 Copy_U8Command);
void LCD_VoidSendString(char * Copy_U8PtrString);
void LCD_VoidSendNum(u16 CopyNum);
void LCD_VoidClearScreen(void);
void LCD_VoidShiftLeft(void);
void LCD_VoidShiftRight(void);
void LCD_VoidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);
void LCD_VoidWriteSpecialCharacter(u8* Copy_u8Pattern,u8 Copy_u8PosInMemory);
void LCD_VoidDisplaySpecialCharacter(u8 Copy_u8PosInMemory,u8 Copy_u8XPosition,u8 Copy_u8YPosition);




#endif
