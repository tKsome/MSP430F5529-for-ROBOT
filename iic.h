#ifndef _IIC_H_
#define _IIC_H_

#include "msp430.h"

typedef unsigned int uint;
typedef unsigned char uchar;

//引脚
#define IIC_SDA_PIN   (BIT0)
#define IIC_SCL_PIN   (BIT1)

//位宏
#define READ_SDA()      P2IN&BIT0

#define IIC_SDA_LO         P2OUT&=~BIT1
#define IIC_SDA_HI         P2OUT|=BIT1

#define IIC_SCL_LO         P2OUT&=~BIT3
#define IIC_SCL_HI         P2OUT|=BIT3

//SDA设置为输出输入
#define SDA_OUT()  P2DIR|=BIT1	
#define SDA_IN()   P2DIR&=~BIT1

//SCL设置为输出输入
#define SCL_OUT()  P2DIR|=BIT3
#define SCL_IN()   P2DIR&=~BIT3

//本构件所实现的函数列表
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_NAck(void);
void IIC_Ack(void);
void IIC_SendByte(uint dat);
uchar IIC_ReadByte(uchar ack);
uchar I2C_ReadByte(uchar DiviceID ,uchar address);
void I2C_WriteByte(uchar  ,uchar address,uchar );
void I2C_ReadNByte(uchar  ,uchar address,uchar ,uchar* );
#endif

