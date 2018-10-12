/*
 * @File:   libtest_hexdump.c
 * @Author: liu2guang
 * @Date:   2018-10-12 14:56:10
 *
 * @LICENSE: MIT
 * https://github.com/liu2guang/optparse/blob/master/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-12     liu2guang    update RT-Thread testcase toolkis.
 */

#ifndef __LIBTEST_HEXDUMP_H__
#define __LIBTEST_HEXDUMP_H__

#include "rtthread.h"

void libtest_hexdump(const rt_uint8_t *p, rt_size_t len); 

#endif
