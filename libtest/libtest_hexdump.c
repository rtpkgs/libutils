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

#include "libtest_hexdump.h" 

void libtest_hexdump(const rt_uint8_t *p, rt_size_t len)
{
    unsigned char *buf = (unsigned char*)p;
    int i, j;

    for (i=0; i<len; i+=16)
    {
        rt_kprintf("%08X: ", i);

        for (j=0; j<16; j++)
        {
            if (i+j < len)
            {
                rt_kprintf("%02X ", buf[i+j]);
            }
            else
            {
                rt_kprintf("   ");
            }
        } 
        rt_kprintf(" ");

        for (j=0; j<16; j++)
        {
            if (i+j < len)
            {
                rt_kprintf("%c", ((unsigned int)((buf[i+j]) - ' ') < 127u - ' ') ? buf[i+j] : '.');
            }
        }
        rt_kprintf("\n");
    }
}
