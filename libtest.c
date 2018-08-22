/*
 * @File:   libtest.c
 * @Author: liu2guang
 * @Date:   2018-08-21 20:57:10
 *
 * @LICENSE: MIT
 * https://github.com/liu2guang/optparse/blob/master/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-21     liu2guang    update RT-Thread testcase toolkis.
 */

#include "libtest.h" 
#include "libtest_def.h" 

int libtest_init(void)
{
    libtest_usage_init(); 

    LOG_I("libtest init successful."); 

    return RT_EOK; 
}
INIT_COMPONENT_EXPORT(libtest_init); 
