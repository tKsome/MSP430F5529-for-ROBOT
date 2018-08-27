#include "iic.h"

#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09


void delayms(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
      for(y=148;y>0;y--);
}

void PCA9685_write(uint address, uint data)//address�����ݵ�ַ data��д������ݲ���
{
  IIC_Init();
  IIC_Start();
  IIC_SendByte(0x80);//Ӳ����ַ
  IIC_SendByte(address);
  IIC_SendByte(data);
  IIC_Stop();
}

void AngleSet(uint num, uint on, uint off)//����PCA9685�ֲᣬһ����������ĸ�8λ����
{
  PCA9685_write(LED0_ON_L+4*num,on);
  PCA9685_write(LED0_ON_H+4*num,on>>8);
  PCA9685_write(LED0_OFF_L+4*num,off);
  PCA9685_write(LED0_OFF_H+4*num,off>>8);
}

/*---------------------------------------------------------------
                                        PCA9685�޸�Ƶ�ʺ���
----------------------------------------------------------------*/
void setPWMFreq(float freq) 
{
  uint prescale,oldmode=0x00,newmode;
  float prescaleval;
  freq *= 0.92;  // Correct for overshoot in the frequency setting 
  prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;
  prescale = floor(prescaleval + 0.5);
                
  //oldmode = PCA9685_read(0x00);
  newmode = (oldmode&0x7F) | 0x10; // sleep
  PCA9685_write(0x00, newmode); // go to sleep
  PCA9685_write(0xfe, prescale); // set the prescaler
  PCA9685_write(0x00, oldmode);
  delayms(2);
  PCA9685_write(0x00, oldmode | 0xa1); //10100001
}
//PCA9685_write(0x00, 0x00);//PCA9685��ʼ��
 // AngleSet(1,0,615);//0��ֵ��
//  AngleSet(0,0,2048);//180��ֵ
//  AngleSet(2,0,1332);//90��ֵ
//}