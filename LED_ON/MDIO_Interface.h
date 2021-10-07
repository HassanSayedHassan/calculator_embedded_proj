#ifndef _MDIO_INTERFACE_H_
#define _MDIO_INTERFACE_H_

/* Port Defines */
#define PORTA		0
#define PORTB		1
#define PORTC		2
#define PORTD		3

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7


/* Digital I/O value */
#define HIGH		1
#define LOW		0

/* Digital I/O Direction */
#define INPUT_PORT		0x00
#define OUTPUT_PORT	0xFF

#define INPUT_PIN		0x00
#define OUTPUT_PIN	0x01

#define MDIO_EN_PULL_UP_RES     1
#define MDIO_DIS_PULL_UP_RES    0

/* Functions Prototypes */
void MDIO_VoidSetPinDirection(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Direction);
void MDIO_VoidSetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Value);

void  MDIO_VoidSetPortDirection(u8 Copy_U8Port,u8 Copy_U8Direction);
void  MDIO_VoidSetPortValue(u8 Copy_U8Port,u8 Copy_U8Value);

void  MDIO_VoidTogglePin(u8 Copy_U8Port,u8 Copy_U8Pin);
u8 MDIO_U8GetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin);

#endif
