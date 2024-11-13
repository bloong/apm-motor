
#include "tm1650.h"
#include "tm1650_config.h"
 
 
/* 往一个指定的数码管位写入指定的显示数据 */
/* 共阴数码管段码表 */

const uint8_t TUBE_TABLE_0[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};    //共阴，0~9~A~F
 	
static uint32_t key_number[7][4] = {11,12,13,14,21,22,23,24,31,32,33,34,41,42,43,44,51,52,53,54,61,62,63,64,71,72,73,74};
static uint8_t key_numberH[7][4] = {0x44,0x45,0x46,0x47,\
																		0x4C,0x4D,0x4E,0x4F,\
																		0x54,0x55,0x56,0x57,\
																		0x5C,0x5D,0x5E,0x5F,\
																		0x64,0x65,0x66,0x67,\
																		0x6C,0x6D,0x6E,0x6F,\
																		0x74,0x75,0x76,0x77,};

																		
//产生IIC总线起始信号
static void TM1650_IIC_start(void)
{
	TM1650_IIC_SCL_HIGH;      //SCL=1
	TM1650_IIC_SDA_HIGH;      //SDA=1
	TM1650_IIC_DELAY_4US;
	TM1650_IIC_SDA_LOW;       //SDA=0
	TM1650_IIC_DELAY_4US;
	TM1650_IIC_SCL_LOW;       //SCL=0
}
 
//产生IIC总线结束信号
static void TM1650_IIC_stop(void)
{
	TM1650_IIC_SCL_LOW;       //SCL=0
	TM1650_IIC_SDA_LOW;       //SDA=0
	TM1650_IIC_DELAY_4US;
	TM1650_IIC_SCL_HIGH;      //SCL=1
	TM1650_IIC_DELAY_4US;
	TM1650_IIC_SDA_HIGH;      //SDA=1
}
 
//通过IIC总线发送一个字节
static void TM1650_IIC_write_byte(uint8_t dat)
{
	uint8_t i;
	
	TM1650_IIC_SCL_LOW;
	for(i=0;i<8;i++)
	{
		TM1650_IIC_SDA_WR(dat&0x80);
		dat<<=1;	
		
		TM1650_IIC_DELAY_2US;
		TM1650_IIC_SCL_HIGH;
		TM1650_IIC_DELAY_2US;
		TM1650_IIC_SCL_LOW;
		TM1650_IIC_DELAY_2US;
	}
}
 

unsigned char  TM1650_Read_Byte(void)
{
	unsigned char i,rekey=0;

	for(i=0;i<8;i++ )
	{
		TM1650_IIC_SCL_LOW;
		TM1650_IIC_DELAY_4US;
		TM1650_IIC_SCL_HIGH;
		rekey<<=1;
		if(TM1650_IIC_SDA_RD()) rekey++;   
		TM1650_IIC_DELAY_4US;
	}			

	
	return rekey;
}


//通过IIC总线接收从机响应的ACK信号
static uint8_t TM1650_IIC_wait_ack(void)
{
	uint8_t ack_signal = 0;
	
	TM1650_IIC_SDA_HIGH;    //SDA=1
	TM1650_IIC_DELAY_2US;
	TM1650_IIC_SCL_HIGH;
	TM1650_IIC_DELAY_2US;
	if(TM1650_IIC_SDA_RD()) ack_signal = 1;   
	TM1650_IIC_SCL_LOW;
	TM1650_IIC_DELAY_2US;
	return ack_signal;
}
 
 
//TM1650初始化
void TM1650_init(void)
{
	  GPIO_Config_T gpioConfig;
 
    /* TM1650_IIC_SCL GPIO configuration */
    gpioConfig.pin = TM1650_IIC_SCL_PIN;
    gpioConfig.mode = GPIO_MODE_OUT_OD;
	  gpioConfig.intEn = GPIO_EINT_DISABLE;
    gpioConfig.speed = GPIO_SPEED_10MHz;
	
	
    GPIO_Config(TM1650_IIC_SCL_PORT, &gpioConfig);
 
    /* TM1650_IIC_SCL GPIO configuration */
    gpioConfig.pin = TM1650_IIC_SDA_PIN;
    GPIO_Config(TM1650_IIC_SDA_PORT, &gpioConfig);
	
    TM1650_IIC_SDA_HIGH;   //释放SDA线
    TM1650_IIC_SCL_HIGH;   //释放SCL线
 
		TM1650_cfg_display(TM1650_BRIGHT8);
		TM1650_clear();
    
}
 
 
//作用：设置显示参数
//备注：这个操作不影响显存中的数据
//用例：
//	设置亮度并打开显示:TM1650_cfg_display(TM1650_BRIGHTx)
//	关闭显示:TM1650_cfg_display(TM1650_DSP_OFF)
void TM1650_cfg_display(uint8_t param)
{
	TM1650_IIC_start();
	TM1650_IIC_write_byte(0x48);  //固定命令
	TM1650_IIC_wait_ack();
	TM1650_IIC_write_byte(param); //参数值
	TM1650_IIC_wait_ack();
	TM1650_IIC_stop();
}
 
 
//将显存数据全部刷为0，清空显示
void TM1650_clear(void)
{
	uint8_t dig;
	for(dig = TM1650_DIG1 ; dig<= TM1650_DIG3 ;dig++)
	{
		TM1650_print(dig,TUBE_TABLE_0[0]);   //将显存数据刷为0
	}
}
 
 
//用例：
//	在DIG1位上显示数字3: TM1650_print(TM1650_DIG1,TUBE_TABLE_0[3]);
void TM1650_print(uint8_t dig,uint8_t seg_data)
{
	TM1650_IIC_start();
	TM1650_IIC_write_byte(dig*2+0x68); 
	TM1650_IIC_wait_ack();  //显存起始地址为0x68
	TM1650_IIC_write_byte(seg_data); 
	TM1650_IIC_wait_ack();    //发送段码
	TM1650_IIC_stop();
}

uint8_t TM1650_Read_KEY(void)
{	
	uint8_t temp;
  TM1650_IIC_start();
	TM1650_IIC_write_byte(0x49);
	TM1650_IIC_wait_ack();
	temp=TM1650_Read_Byte();
	TM1650_IIC_wait_ack();
	TM1650_IIC_stop();
	return temp;
}


uint32_t TM1650_Get_KEY(void)
{	
	uint8_t key=0;
	key= TM1650_Read_KEY();
	uint32_t key_name=0,i,j;
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
		{
			if(key == key_numberH[i][j])
			{
				key_name = key_number[i][j];
				return key_name;
			}
		}
	
  return key_name;

}