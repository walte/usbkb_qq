/******************************************************************
   ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

        ��ӭ�����ҵ�USBר����http://group.ednchina.com/93/
        ��ӭ�����ҵ�blog��   http://www.ednchina.com/blog/computer00
                             http://computer00.21ic.org

UART.H  file

���ߣ�Computer-lov
��������: 2007.03.20
�޸�����: 2007.03.22
�汾��V1.1
��Ȩ���У�����ؾ���
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
