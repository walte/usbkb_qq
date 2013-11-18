/******************************************************************
   本程序只供学习使用，未经作者许可，不得用于其它任何用途

        欢迎访问我的USB专区：http://group.ednchina.com/93/
        欢迎访问我的blog：   http://www.ednchina.com/blog/computer00
                             http://computer00.21ic.org

KEY.C  file

作者：Computer-lov
建立日期: 2007.03.20
修改日期: 2007.11.18
版本：V1.2
版权所有，盗版必究。
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
函数功能：定时器0初始化，用来做键盘扫描，定时时间大约为5ms。
入口参数：无。
返    回：无。
备    注：无。
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
函数功能：键盘初始化
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
void InitKeyboard(void)
{
 KeyIO=0xFF;	  //键盘对应的口设置为输入状态
 KeyPress=0;	      //无按键按下
 KeyNoChangedTime=0;
 KeyOld=0;
 KeyCurrent=0;
 KeyLast=0;
 KeyDown=0;
 KeyUp=0;
 InitTimer0();		  //初始化定时器
 KeyCanChange=1;	  //允许键值改变
}
/*******************************************************************/

/********************************************************************
函数功能：定时器0中断处理。
入口参数：22.1184M晶体约5ms中断一次。
返    回：无。
备    注：无。
********************************************************************/
void Timer0Isr(void) interrupt 1
{ 
 TH0=(65536-Fclk/1000/12*5+15)/256;	 //定时器0重装
 TL0=(65536-Fclk/1000/12*5+15)%256;

 if(!KeyCanChange)return;     //如果正在处理按键，则不再扫描键盘 

 //开始键盘扫描
 //保存按键状态到当前按键情况
 //KeyCurrent总共有8个bit
 //当某个开关按下时，对应的bit为1
      
 KeyCurrent=~KeyIO;    

 if(KeyCurrent!=KeyOld)  //说明按键情况发生了改变
  {
   KeyNoChangedTime=0;       //键盘按下时间为0
   KeyOld=KeyCurrent;        //保存当前按键情况
   return;
  }
 else
  {
   KeyNoChangedTime++;	     //按下时间累计
   if(KeyNoChangedTime>=1)	 //如果按下时间足够
    {
	 KeyNoChangedTime=1;
	 KeyPress=KeyOld;      //保存按键
	 KeyDown|=(~KeyLast)&(KeyPress); //求出新按下的键
	 KeyUp|=KeyLast&(~KeyPress);     //求出新释放的键
	 KeyLast=KeyPress;		         //保存当前按键情况
	}
  }
}
/*******************************************************************/
