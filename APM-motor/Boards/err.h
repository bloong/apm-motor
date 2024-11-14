
/* Define to prevent recursive inclusion */
#ifndef __ERR_H
#define __ERR_H

#include "main.h"

typedef enum {
  E0_NONE     =  0,                           // 没有错误
  E1_SHOCK    = 1 << 0,                       // 震动错误
  E2_OUTSYNC  = 1 << 1,                       // 不同步错误
  E3_OVERLOAD = 1 << 2,                       // 过载错误
  E4_TIMEOUT  = 1 << 3,                       // 运行超时错误
  E5_SHOCK    = 1 << 4,                       // 输入错误
  E6_SHOCK    = 1 << 5,                       // 输出错误
  E7_SHOCK    = 1 << 6,                       // 系统错误
  E8_SHOCK    = 1 << 7,                       // 进程错误
  E9_SHOCK    = 1 << 8                        // 安全错误
} ErrorFlags;

uint32_t set_error_flag(uint32_t current_status, ErrorFlags flag);
uint32_t clear_error_flag(uint32_t current_status, ErrorFlags flag);
uint32_t is_error_flag_set(uint32_t current_status, ErrorFlags flag);

#endif /*__ERR_H */
