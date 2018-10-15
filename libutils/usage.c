/*
 * @File:   usage.c
 * @Author: liu2guang
 * @Date:   2018-08-21 20:57:10
 *
 * @LICENSE: MIT
 * https://github.com/rtpkgs/libtest/blob/master/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-21     liu2guang    update RT-Thread usage toolkis.
 */

#include "usage.h" 
#include "optparse.h"
#include "string.h"
#include <stdlib.h>
#include "console.h" 

static rt_uint8_t  major = 0; 
static rt_uint8_t  minor = 0;
static rt_uint32_t usage_load = 0; 

//static void usage_view_entry(void *p)
//{
//    rt_kprintf(_HCU _SCP _DECSTBM(1, 28) _CUP(500, 0) _CUU(1) _FG_WHITE _BG_BLUE); 
//    rt_kprintf("INFO:%115.s", " ");
//    rt_kprintf(_SGR_NONE _RCP _SCU);
//    
//    while(1)
//    {
//        while(usage_view == RT_FALSE)
//        {
//            rt_thread_mdelay(500); 
//        }

//        rt_kprintf(_HCU _SCP _CUP(500, 0)); 
//        rt_kprintf("[%.2d.%.2d%%] [%.4ds]", major, minor, rt_tick_get()/RT_TICK_PER_SECOND);
//        rt_kprintf(_RCP _SCU);
//        
//        rt_thread_mdelay(1000);
//    }
//}

static void _delay(rt_uint32_t us)
{
    volatile rt_int32_t i;
    for (; us > 0; us--)
    {
        i = 30;
        while (i > 0)
        {
            i--;
        }
    }
}

static void usage_load_entry(void *p)
{
    while(1) 
    {
        _delay(usage_load); 
        rt_thread_mdelay(1); 
    }
}

static void usage_hook(void)
{
    rt_tick_t tick;
    rt_uint32_t count;
    volatile rt_uint32_t loop;
    static rt_uint32_t total = 0; 

    if (total == 0)
    {
        /* get total count */
        rt_enter_critical();
        tick = rt_tick_get();
        while(rt_tick_get() - tick < 10)
        {
            total ++;
            loop = 0;
            while (loop < 100) loop ++;
        }
        rt_exit_critical();
    }

    count = 0;
    tick = rt_tick_get();
    while (rt_tick_get() - tick < 10)
    {
        count ++;
        loop  = 0;
        while (loop < 100) loop ++;
    }

    if (count < total)
    {
        count = total - count;
        major = (count * 100) / total;
        minor = ((count * 100) % total) * 100 / total;
    }
    else
    {
        total = count;
        major = 0;
        minor = 0;
    }
}

rt_uint8_t usage_cpu_major(void)
{
    return major; 
}

rt_uint8_t usage_cpu_minor(void)
{
    return minor; 
}

int usage_load_cmd(int argc, char **argv)
{
    usage_load = atoi(argv[1]); 
    return RT_EOK; 
}
MSH_CMD_EXPORT_ALIAS(usage_load_cmd, load, set cpu load.)

int usage_init(void)
{
    rt_thread_t thread = RT_NULL; 

    rt_thread_idle_sethook(usage_hook);

    /* create usage load plugin */ 
    thread = rt_thread_create("cpuload", usage_load_entry, 
        RT_NULL, 512, 1, 10); 
    if(thread == RT_NULL)
    {
        rt_kprintf("create cpuload plugin failed.\n"); 
        return RT_EOK; 
    }
    rt_thread_startup(thread); 

    return RT_EOK; 
}
INIT_APP_EXPORT(usage_init); 
