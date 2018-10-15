/*
 * @File:   console.c 
 * @Author: liu2guang
 * @Date:   2018-08-21 20:57:10
 *
 * @LICENSE: MIT
 * https://github.com/rtpkgs/libtest/blob/master/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-21     liu2guang    update RT-Thread console toolkis.
 */

#include "console.h" 
#include "usage.h" 
#include "shell.h"

struct console
{
    rt_uint16_t x; 
    rt_uint16_t y; 
    rt_uint8_t rate; 
    rt_uint16_t plugin_num; 
    
    void (*show)(void *p); 
    void *user_data; 
}; 
typedef struct console* console_t; 

static struct console _console = {0}; 

static void console_show(void *p)
{
    rt_kprintf("[%.2d.%.2d%%] [%.4ds]", usage_cpu_major(), usage_cpu_minor(), 
        rt_tick_get()/RT_TICK_PER_SECOND);
}

static void console_entry(void *p)
{
    rt_kprintf(_RST); 
    rt_thread_mdelay(10); 
    rt_show_version();
    rt_kprintf("%s", finsh_get_prompt()); 
    rt_kprintf(_HCU _SCP _CSI"1;%dr" _CUP(500, 0) _CSI"%dA" _FG_WHITE _BG_BLUE, 
        _console.y-_console.plugin_num-1, _console.plugin_num); 
    rt_kprintf("INFO:%-*.s", _console.x-5, " ");
    rt_kprintf(_SGR_NONE _RCP _SCU);
    
    while(1)
    {
        if(_console.plugin_num == 1)
        {
            rt_kprintf(_HCU _SCP _CUP(500, 0)); 
        }
        else
        {
            rt_kprintf(_HCU _SCP _CUP(500, 0) _CSI"%dA", _console.plugin_num-1); 
        }
        
        _console.show(_console.user_data); 

        rt_kprintf(_RCP _SCU);
        
        rt_thread_mdelay(RT_TICK_PER_SECOND/_console.rate);
    }
}

rt_err_t console_init(rt_uint16_t x, rt_uint16_t y, rt_uint8_t rate, rt_uint16_t plugin_num, void (*show)(void *p), void *user_data)
{
    rt_err_t ret = RT_EOK;
    
    if((x == 0) || (y == 0) || (rate == 0) || (plugin_num == 0)) 
    {
        ret = (-RT_EINVAL); 
        return ret; 
    }
    
    _console.x          = x; 
    _console.y          = y; 
    _console.rate       = rate; 
    _console.plugin_num = plugin_num; 
    
    if(show == RT_NULL)
    {
        _console.show = console_show; 
    }
    else 
    {
        _console.show = show; 
    }
    
    rt_thread_t thread = RT_NULL; 
    
    thread = rt_thread_create("console", console_entry, 
        RT_NULL, 512, FINSH_THREAD_PRIORITY-1, 10); 
    if(thread == RT_NULL)
    {
        rt_kprintf("create console plugin failed.\n"); 
        return RT_EOK; 
    }
    rt_thread_startup(thread); 
    
    return ret; 
}

static int _console_init(void)
{
    console_init(125, 30, 1, 1, RT_NULL, RT_NULL);
    return RT_EOK; 
}

INIT_APP_EXPORT(_console_init); 
