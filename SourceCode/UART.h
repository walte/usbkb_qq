/******************************************************************
   本程序只供学习使用，未经作者许可，不得用于其它任何用途

        欢迎访问我的USB专区：http://group.ednchina.com/93/
        欢迎访问我的blog：   http://www.ednchina.com/blog/computer00
                             http://computer00.21ic.org

UART.H  file

作者：Computer-lov
建立日期: 2007.03.20
修改日期: 2007.03.22
版本：V1.1
版权所有，盗版必究。
Copyright(C) Computer-lov 2007-2017
All rights reserved            
*******************************************************************/

#ifndef __UART_C__
#define __UART_C__

#include "my_type.H"

void InitUART(void);
void UartPutChar(uint8);
void Prints(uint8 *);
void PrintLongInt(uint32);
void PrintShortIntHex(uint16 x);
void PrintLongIntHex(uint32);
void Printc(uint8);
void PrintHex(uint8 x);

#endif
