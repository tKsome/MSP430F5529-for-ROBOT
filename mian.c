#include <msp430.h>
#include "iic.h"


void main()
{
     WDTCTL = WDTPW + WDTHOLD;            //�ؿ��Ź�
     int num=0;
     PCA9685_write(0x00, 0x00);
         //��ʼ�����ư�
     while(1)
     {
       for(num=0;num<8;num++)
       {
         AngleSet(num,0,1332);//90��ֵ
         if(num==7)
           num=0;
       }
     }
     
}

//void main(void)//Ƶ��
//{
//      WDTCTL = WDTPW + WDTHOLD;                  // ���Ź�
//      P8DIR |= 0x01;                             // P1.0 ���
//      TBCCTL0 = CCIE;                            // CCR0 �ж�ʹ��
//      TBCCR0 = 50000;                            // CCR0���ó�ʼֵ
//      TBCTL = TBSSEL_2 + TACLR;                  // SMCLK, ���Ϊ1
//      TBCTL |= MC_3;
//      _BIS_SR(LPM0_bits + GIE);                  // ����͹���0
//}
//
///****** Timer B0 �жϷ������*******/
//
//#pragma vector=TIMERB0_VECTOR
//__interrupt void Timer_B (void)
//{
//        P8OUT ^= 0x01;                            //��תLED1
//        TBCCR0 += 50000;                          // ���Ӷ�ʱƫ����
//}
