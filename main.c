#include"STD_TYPES.h"
#include "MDIO_Interface.h"
#include"LCD_Interface.h"
#include<avr/delay.h>
#include "HKPD_Interface.h"

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <stdbool.h>
#include "stack.h"


#define SIZE 50

Stack stack;
char* expression;
int expLength=0;
char* correctExpression;
char *postfix;
bool withReset=false;

bool IsOperand(char C)
{
    if (C >= '0' && C <= '9') return true;
    if (C >= 'a' && C <= 'z') return true;
    if (C >= 'A' && C <= 'Z') return true;
    return false;
}
bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$')
        return true;

    return false;
}
int precedence(char symbol)
{
    if(symbol == '^')/* exponent operator, highest precedence*/
    {
        return(3);
    }
    else if(symbol == '*' || symbol == '/')
    {
        return(2);
    }
    else if(symbol == '+' || symbol == '-')          /* lowest precedence */
    {
        return(1);
    }
    else
    {
        return(0);
    }
}
void InfixToPostfix(char infix_exp[], char postfix_exp[])
{
    int i, j;
    char item;
    char x;

    stack_push(stack,'(');                               /* push '(' onto stack */
    strcat(infix_exp,")");                  /* add ')' to infix expression */

    i=0;
    j=0;
    item=infix_exp[i];         /* initialize before loop*/

    while(item != '\0')        /* run loop till end of infix expression */
    {
        if(item == '(')
        {
            stack_push(stack,item);
        }
        else if( IsOperand(item) || IsOperand(item))
        {

            postfix_exp[j] = item;              /* add operand symbol to postfix expr */
            j++;
        }
        else if(IsOperator(item) == 1)        /* means symbol is operator */
        {
            postfix_exp[j] = ' ';                  /* so pop all higher precendence operator and */
            j++;

            x=stack_pop(stack);
            while(IsOperator(x) == 1 && precedence(x)>= precedence(item))
            {
                postfix_exp[j] = x;                  /* so pop all higher precendence operator and */
                j++;
                x = stack_pop(stack);                       /* add them to postfix expresion */
            }
            stack_push(stack,x);
            /* because just above while loop will terminate we have
            oppped one extra item
            for which condition fails and loop terminates, so that one*/

            stack_push(stack,item);                 /* push current oprerator symbol onto stack */

            postfix_exp[j] = ' ';                  /* so pop all higher precendence operator and */
            j++;
        }
        else if(item == ')')         /* if current symbol is ')' then */
        {
            x = stack_pop(stack);                  /* pop and keep popping until */
            while(x != '(')                /* '(' encounterd */
            {
                postfix_exp[j] = x;
                j++;
                x = stack_pop(stack);
            }
        }
        else
        { /* if current symbol is neither operand not '(' nor ')' and nor
			operator */
            printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
            getchar();
            exit(1);
        }
        i++;


        item = infix_exp[i]; /* go to next symbol of infix expression */
    } /* while loop ends here */
    if(stack_top(stack)>0)
    {
        printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
        getchar();
        exit(1);
    }
    if(stack_top(stack)>0)
    {
        printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
        getchar();
        exit(1);
    }


    postfix_exp[j] = '\0'; /* add sentinel else puts() fucntion */
    /* will print entire postfix[] array upto SIZE */

}



int s[SIZE];
int topFix=-1; /* Global declarations */
int flag=0;
int popFix()
{                      /* Function for popFix operation */
    return(s[topFix--]);
}
void pushFix(int elem)
{
    if(flag==1){
        int num;
        num=popFix();
        s[++topFix]=elem+10*num;
    }
    else if(flag==0){
        s[++topFix]=elem;
        flag=1;
    }
}
int calculatePostFix(char* CopyPostfix )
{
    char ch;
    int op1,op2;

    for(int i=0;i< strlen(CopyPostfix);++i)
    {
        ch=CopyPostfix[i];
        if(IsOperand(ch)) pushFix(ch-'0'); /* pushFix the operand */
        else if(ch==' ')
            flag=0;
        else
        {        /* Operator,popFix two  operands */
            flag=0;
            op2=popFix();
            op1=popFix();
            switch(ch)
            {
                case '+':pushFix(op1+op2);break;
                case '-':pushFix(op1-op2);break;
                case '*':pushFix(op1*op2);break;
                case '/':pushFix(op1/op2);break;
                default:
                    printf("Input invalid ... give proper input\n");
                    return 0;
            }
        }
    }
    return  s[topFix];
}

void resetSystem(void)
{
	LCD_VoidClearScreen();
	LCD_VoidGoToXY(0, 0);
    topFix=-1;
    flag =0;
    stack_make_empty(stack);
    strcpy(expression,"");
    expLength=0;
    strcpy(correctExpression,"");
    strcpy(postfix,"");
    withReset=false;
}





int main (void)
{
	stack  = stack_create(SIZE);

	u8 localPressedKey;
	LCD_VoidInit();
	HKPD_voidInitializeKeypad();
	LCD_VoidGoToXY(0, 0);


	while(1)
	 {

		 localPressedKey=HKPD_u8GetPressedKey();
		 if(localPressedKey=='c')
		 {
			 resetSystem();

		 }

		 else if(localPressedKey!='?')
		 {

			 if(localPressedKey=='=')
			 {
				 withReset=true;

				 correctExpression=(char*)malloc(sizeof(char)*expLength);
				 postfix=(char*)malloc(sizeof(char)*expLength);
				 		 int correctExpLength=0;
				 for(int i=0;i<expLength;++i)
				  {
				       if(expression[i]!='\n')
				            correctExpression[correctExpLength++]=expression[i];
				    }
				    correctExpression[correctExpLength]='\0';

				     InfixToPostfix(correctExpression,postfix);


				      LCD_VoidGoToXY(1, 0);
				      LCD_VoidSendChar('=');
				      LCD_VoidGoToXY(1, 1);
				      sprintf(postfix, "%d", calculatePostFix(postfix));
				    LCD_VoidSendString(postfix);



					while(HKPD_u8GetPressedKey()==localPressedKey)
					{

					}
					_delay_ms(20); // Delay To Over Come The Pouncing Problems

			 }
			 else
			 {

				 if(withReset) resetSystem();

				 LCD_VoidSendChar(localPressedKey);

				 expLength++;

		        expression=(char *) realloc(expression,sizeof(char)*expLength );
		        expression[expLength-1]=localPressedKey;


				while(HKPD_u8GetPressedKey()==localPressedKey)
				{

				}
				_delay_ms(20); // Delay To Over Come The Pouncing Problems


			 }





		 }



	 }
	 return 0;
}

