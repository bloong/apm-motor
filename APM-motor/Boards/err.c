
/* Includes */
#include "err.h"

uint32_t set_error_flag(uint32_t current_status, ErrorFlags flag)
{
    return current_status | flag;
}

uint32_t clear_error_flag(uint32_t current_status, ErrorFlags flag)
{
    return current_status & (~flag);
}

uint32_t is_error_flag_set(uint32_t current_status, ErrorFlags flag)
{
    return (current_status & flag) != 0;
}