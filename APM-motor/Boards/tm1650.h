#ifndef TM1650_H_
#define TM1650_H_

#include "main.h"
 
//显示参数
#define TM1650_BRIGHT1       0x11   /*一级亮度，打开LED显示*/
#define TM1650_BRIGHT2       0x21   /*二级亮度，打开LED显示*/
#define TM1650_BRIGHT3       0x31   /*三级亮度，打开LED显示*/
#define TM1650_BRIGHT4       0x41   /*四级亮度，打开LED显示*/
#define TM1650_BRIGHT5       0x51   /*五级亮度，打开LED显示*/
#define TM1650_BRIGHT6       0x61   /*六级亮度，打开LED显示*/
#define TM1650_BRIGHT7       0x71   /*七级亮度，打开LED显示*/
#define TM1650_BRIGHT8       0x01   /*八级亮度，打开LED显示*/
#define TM1650_DSP_OFF       0x00   /*关闭LED显示*/
 
//数码管位选
#define TM1650_DIG1     0
#define TM1650_DIG2     1
#define TM1650_DIG3     2
#define TM1650_DIG4     3
 
extern const uint8_t TUBE_TABLE_0[16];
 
void TM1650_init(void);
void TM1650_cfg_display(uint8_t param);
void TM1650_clear(void);
void TM1650_print(uint8_t dig,uint8_t seg_data);
uint32_t TM1650_Get_KEY(void);

#endif //TM1650_H_

