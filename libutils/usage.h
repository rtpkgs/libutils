/*
 * @File:   libtest_usage.h
 * @Author: liu2guang
 * @Date:   2018-08-21 20:57:10
 *
 * @LICENSE: MIT
 * https://github.com/rtpkgs/libtest/blob/master/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-21     liu2guang    update RT-Thread testcase toolkis.
 */

#ifndef __LIBTEST_USAGE_H__
#define __LIBTEST_USAGE_H__

#include "rtthread.h"

int libtest_usage_init(void); 
rt_uint8_t usage_cpu_major(void); 
rt_uint8_t usage_cpu_minor(void); 

#endif
