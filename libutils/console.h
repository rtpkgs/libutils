/*
 * @File:   console.h
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

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "rtthread.h"

/**
 * The standard reference: 
 * 1. ANSI escape code: https://en.wikipedia.org/wiki/ANSI_escape_code 
 * 2. https://github.com/mkschreder/avr-vt100
 */ 

/** 
 * Support ANSI control terminal: 
 * 1. Tera Term v4.67
 */ 

#define _ESC            "\033" 
#define _CSI            _ESC"[" 

/**
 * Moves the cursor n (default 1) cells in the given direction. If the cursor is 
 * already at the edge of the screen, this has no effect. 
 * 
 * _CUU(n): Cursor Up
 * _CUD(n): Cursor Down
 * _CUF(n): Cursor Forward
 * _CUB(n): Cursor Back
 */ 
#define _CUU(n)         _CSI#n"A" 
#define _CUD(n)         _CSI#n"B" 
#define _CUF(n)         _CSI#n"C" 
#define _CUB(n)         _CSI#n"D" 

/* Moves cursor to beginning of the line n (default 1) lines down */ 
#define _CNL(n)         _CSI#n"E" 

/* Moves cursor to beginning of the line n (default 1) lines up. */ 
#define _CPL(n)         _CSI#n"F" 

/* Moves the cursor to column n (default 1). */ 
#define _CHA(n)         _CSI#n"G" 

/* 
 * Moves the cursor to row n, column m. 
 * The values are 1-based, and default to 1 (top left corner) if omitted. 
 * A sequence such as CSI ;5H is a synonym for CSI 1;5H as well as CSI 17;H 
 * is the same as CSI 17H and CSI 17;1H. 
 */ 
#define _CUP(n, m)      _CSI#n";"#m"H" 

/*
 * Clears part of the screen. 
 * If n is 0 (or missing), clear from cursor to end of screen. 
 * If n is 1, clear from cursor to beginning of the screen. 
 * If n is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS). 
 * If n is 3, clear entire screen and delete all lines saved in the scrollback 
 *            buffer (this feature was added for xterm and is supported by other 
 *            terminal applications). 
 */
#define _ED(n)          _CSI#n"J" 
#define _ED0            _ED(0) 
#define _ED1            _ED(1) 
#define _ED2            _ED(2) 
#define _ED3            _ED(3) 

/** 
 * Erases part of the line. 
 * If n is 0 (or missing), clear from cursor to the end of the line. 
 * If n is 1, clear from cursor to beginning of the line. 
 * If n is 2, clear entire line. Cursor position does not change
 */ 
#define _EL(n)          _CSI#n"K" 
#define _EL0            _EL(0) 
#define _EL1            _EL(1) 
#define _EL2            _EL(2) 

/** 
 * Scroll whole page up by n (default 1) lines. 
 * New lines are added at the bottom. (not ANSI.SYS)
 */ 
#define _SU(n)          _CSI#n"S" 

/** 
 * Scroll whole page down by n (default 1) lines. 
 * New lines are added at the top. (not ANSI.SYS)
 */ 
#define _SD(n)          _CSI#n"T" 

/* Same as CUP */ 
#define _HVP(n, m)      _CSI#n";"#m"f" 

/* Sets the appearance of the following characters, see SGR parameters below. */ 
#define _SGR(n)         _CSI#n"m" 
#define _SGR_NONE       _SGR(0)     // all attributes off
#define _SGR_BOLD       _SGR(1)     // Bold or increased intensity
#define _SGR_FAINT      _SGR(2)     // Faint (decreased intensity)
#define _SGR_ITALIC     _SGR(3)     // Italic, Not widely supported. Sometimes treated as inverse.
#define _SGR_UNDER      _SGR(4)     // Underline
#define _SGR_BLINK1     _SGR(5)     // Slow Blink, less than 150 per minute
#define _SGR_BLINK2     _SGR(6)     // Rapid Blink, MS-DOS ANSI.SYS; 150+ per minute; not widely supported
#define _SGR_INVERSE    _SGR(7)     // swap foreground and background colors

/* Set colors in RGB mode */ 
#define _SGR_FG(r,g,b)  _CSI"38;2;"#r";"#g";"#b"m" 
#define _SGR_BG(r,g,b)  _CSI"48;2;"#r";"#g";"#b"m" 

/* Set colors */ 
#define _FG_BLACK       _SGR(30)
#define _FG_RED         _SGR(31)
#define _FG_GREEN       _SGR(32)
#define _FG_YELLOW      _SGR(33)
#define _FG_BLUE        _SGR(34)
#define _FG_PURPLE      _SGR(35)
#define _FG_CYAN        _SGR(36)
#define _FG_WHITE       _SGR(37) 

#define _BG_BLACK       _SGR(40)
#define _BG_RED         _SGR(41) 
#define _BG_GREEN       _SGR(42) 
#define _BG_YELLOW      _SGR(43)
#define _BG_BLUE        _SGR(44) 
#define _BG_PURPLE      _SGR(45)
#define _BG_CYAN        _SGR(46)
#define _BG_WHITE       _SGR(47) 

/* Set the scroll range */ 
#define _DECSTBM(n,m)   _CSI#n";"#m"r" 

/** 
 * Reports the cursor position (CPR) to the application as (as though typed at 
 * the keyboard) ESC[n;mR, where n is the row and m is the column.) 
 */
#define _DSR            _CSI"6n" 

/* Saves the cursor position/state. */ 
#define _SCP            _CSI"s" 

/* Restores the cursor position/state. */ 
#define _RCP            _CSI"u" 

/* Hides the cursor */ 
#define _HCU            _CSI"?25l" 

/* shows the cursor */ 
#define _SCU            _CSI"?25h" 

/* Reset terminal */ 
#define _RST            _ESC"c"

/* API */ 
rt_err_t console_init(rt_uint16_t x, rt_uint16_t y, rt_uint8_t rate, rt_uint16_t plugin_num, void (*show)(void *p), void *user_data); 

#endif
