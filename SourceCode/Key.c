/******************************************************************
   ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

        ��ӭ�����ҵ�USBר����http://group.ednchina.com/93/
        ��ӭ�����ҵ�blog��   http://www.ednchina.com/blog/computer00
                             http://computer00.21ic.org

KEY.C  file

���ߣ�Computer-lov
��������: 2007.03.20
�޸�����: 2007.11.18
�汾��V1.2
��Ȩ���У�����ؾ���
Copyright(C) Computer-lov 2007-2017
All rights reserved            
*******************************************************************/




#include "Key.h"
#include "my_type.h"
#include "config.h"

volatile uint8 idata KeyCurrent,KeyOld,KeyNoChangedTime;
volatile uint8 idata KeyPress;
volatile uint8 idata KeyDown,KeyUp,KeyLast;

volatile uint8 KeyCanChange;

/********************************************************************
�������ܣ���ʱ��0��ʼ��������������ɨ�裬��ʱʱ���ԼΪ5ms��
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void InitTimer0(void)
{
 TMOD&=0xF0;
 TMOD|=0x01;
 TH0=0xDC;
 ET0=1;
 TR0=1;
}
/*******************************************************************/


/********************************************************************
�������ܣ����̳�ʼ��
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void InitKeyboard(void)
{
 KeyIO=0xFF;	  //���̶�Ӧ�Ŀ�����Ϊ����״̬
 KeyPress=0;	      //�ް�������
 KeyNoChangedTime=0;
 KeyOld=0;
 KeyCurrent=0;
 KeyLast=0;
 KeyDown=0;
 KeyUp=0;
 InitTimer0();		  //��ʼ����ʱ��
 KeyCanChange=1;	  //�����ֵ�ı�
}
/*******************************************************************/

/********************************************************************
�������ܣ���ʱ��0�жϴ���
��ڲ�����22.1184M����Լ5ms�ж�һ�Ρ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void Timer0Isr(void) interrupt 1
{ 
 TH0=(65536-Fclk/1000/12*5+15)/256;	 //��ʱ��0��װ
 TL0=(65536-Fclk/1000/12*5+15)%256;

 if(!KeyCanChange)return;     //������ڴ�����������ɨ����� 

 //��ʼ����ɨ��
 //���水��״̬����ǰ�������
 //KeyCurrent�ܹ���8��bit
 //��ĳ�����ذ���ʱ����Ӧ��bitΪ1
      
 KeyCurrent=~KeyIO;    

 if(KeyCurrent!=KeyOld)  //˵��������������˸ı�
  {
   KeyNoChangedTime=0;       //���̰���ʱ��Ϊ0
   KeyOld=KeyCurrent;        //���浱ǰ�������
   return;
  }
 else
  {
   KeyNoChangedTime++;	     //����ʱ���ۼ�
   if(KeyNoChangedTime>=1)	 //�������ʱ���㹻
    {
	 KeyNoChangedTime=1;
	 KeyPress=KeyOld;      //���水��
	 KeyDown|=(~KeyLast)&(KeyPress); //����°��µļ�
	 KeyUp|=KeyLast&(~KeyPress);     //������ͷŵļ�
	 KeyLast=KeyPress;		         //���浱ǰ�������
	}
  }
}
/*******************************************************************/
