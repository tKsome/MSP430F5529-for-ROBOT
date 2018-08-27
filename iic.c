#include "iic.h"

void IIC_delay_us(uchar x)//��ʱ
{
  if(x==0)
    x=2;
  while(x--);
}


void IIC_Init(void)
{
   SDA_OUT();
   IIC_delay_us(2);
   SCL_OUT();
   IIC_delay_us(2);
}


void IIC_Start(void)//��ʼ��IIC�ӿ�
{
  SDA_OUT();  
  IIC_SDA_HI;
  IIC_delay_us(2);
  IIC_SCL_HI;
  IIC_delay_us(2);
  IIC_SDA_LO;
  IIC_delay_us(2);
  IIC_SCL_LO; 
  IIC_delay_us(2);
}

void IIC_Stop(void)//ֹͣIIC�ӿ�
{
	SDA_OUT();
	IIC_SCL_LO;
	IIC_SDA_LO;
	IIC_delay_us(2);
	IIC_SCL_HI;
	IIC_SDA_HI;
	IIC_delay_us(2);							   	
}

void IIC_NAck(void)//��Ӧ���ź�
{
  IIC_SCL_LO;
  SDA_OUT();
  IIC_delay_us(2);
  IIC_SDA_HI;
  IIC_delay_us(2);
  IIC_SCL_HI;
  IIC_delay_us(2);
  IIC_SCL_LO;  
}

void IIC_Ack(void)//Ӧ���ź�
{
  IIC_SCL_LO;
  SDA_OUT();
  IIC_SDA_LO;
  IIC_delay_us(2);
  IIC_SCL_HI;
  IIC_delay_us(2);
  IIC_SCL_LO;
}

void IIC_SendByte(uint dat)//�����ֽ�
{
	uchar i;
	SDA_OUT();
	for(i=0;i<8;i++)
	{
		if(dat&0x80) 
                  IIC_SDA_HI;
                else IIC_SDA_LO;
		dat<<=1;
		IIC_delay_us(2);
		IIC_SCL_HI;
		IIC_delay_us(2);
		IIC_SCL_LO;
	}
       IIC_NAck();

}
uchar IIC_ReadByte(uchar ack)//�����ֽ�
{
    uchar i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
        IIC_SCL_LO; 
        IIC_delay_us(0);
        IIC_SCL_HI;
        receive<<=1;
        if(READ_SDA())receive++;   
        IIC_delay_us(0); 
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}

void I2C_WriteByte(uchar DiviceID ,uchar address,uchar thedata)
{
	IIC_Start();		//
	IIC_SendByte(DiviceID);//д<<1
	IIC_SendByte(address);	//
	IIC_SendByte(thedata);	//
	IIC_Stop();
}

uchar I2C_ReadByte(uchar  DiviceID ,uchar address)
{
    uchar ret = 100;
    IIC_Start();		
    IIC_SendByte((DiviceID));	//��д�Ĵ����ĵ�ַ�ٶ�<<1
    IIC_SendByte(address);//д�Ĵ�����ַ
    IIC_Start();
    IIC_SendByte((DiviceID)|1);//���Ĵ���<<1
    ret = IIC_ReadByte(0);
    IIC_Stop();
    return ret;
}
void I2C_ReadNByte(uchar DiviceID ,uchar address,uchar n,uchar* data)
{
    uchar i;
    IIC_Start();		
    IIC_SendByte((DiviceID));	//��д�Ĵ����ĵ�ַ�ٶ�<<1
    IIC_SendByte(address);//д�Ĵ�����ַ
    IIC_Start();
    IIC_SendByte((DiviceID)|1);//���Ĵ���<<1
    for(i=0;i<n-1;i++)
      data[i] = IIC_ReadByte(1);
    data[i] = IIC_ReadByte(0);//���һ�����ݷ���NACK
    IIC_Stop();
}