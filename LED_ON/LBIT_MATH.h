#ifndef _LBIT_MATH_H_
#define _LBIT_MATH_H_

#define  SET_BIT(res,index) 	res=res|(1<<index)
#define  TOGGLE_BIT(res,index) 	res=res^(1<<index)
#define  CLEAR_BIT(res,index) 	res=res&(~(1<<index))
#define  GET_BIT(res,index) 	((res>>index)&1)
#define  SET_BIT_VALUE(REG,BIT,Value) ( (Value == 0) ? ( REG &= ~(1<<BIT) ) : ( REG |= (1<<BIT) ) )

#endif
