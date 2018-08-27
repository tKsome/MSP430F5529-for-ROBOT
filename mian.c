#include <msp430.h>
#include "iic.h"


void main()
{
     WDTCTL = WDTPW + WDTHOLD;            //关看门狗
     int num=0;
     PCA9685_write(0x00, 0x00);
         //初始化控制板
     while(1)
     {
       for(num=0;num<8;num++)
       {
         AngleSet(num,0,1332);//90度值
         if(num==7)
           num=0;
       }
     }
     
}

//void main(void)//频闪
//{
//      WDTCTL = WDTPW + WDTHOLD;                  // 看门狗
//      P8DIR |= 0x01;                             // P1.0 输出
//      TBCCTL0 = CCIE;                            // CCR0 中断使能
//      TBCCR0 = 50000;                            // CCR0配置初始值
//      TBCTL = TBSSEL_2 + TACLR;                  // SMCLK, 清除为1
//      TBCTL |= MC_3;
//      _BIS_SR(LPM0_bits + GIE);                  // 进入低功耗0
//}
//
///****** Timer B0 中断服务程序*******/
//
//#pragma vector=TIMERB0_VECTOR
//__interrupt void Timer_B (void)
//{
//        P8OUT ^= 0x01;                            //反转LED1
//        TBCCR0 += 50000;                          // 增加定时偏移量
//}
