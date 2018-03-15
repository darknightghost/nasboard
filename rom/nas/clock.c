/*                    
	Copyright 2017,王思远 <darknightghost.cn@gmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "clock.h"
#include <reg52.h>
#include "common.h"

static data volatile u32    current_microsec;
static ptick_cb_info_t      cb_list;

void clock_init()
{
    u8 time_count = (u8)((CRYSTAL_FREQ / 12 / 10 / TICK_MICROSECS / 10) & 0xFF);
    current_microsec = 0;
    cb_list = NULL;
    
    //Initialize timer, 100μs a tick
    TR0 = 0;
    EA = 1;
    ET0 = 1;
    TH0 = time_count;
    TL0 = time_count;
    TMOD = (TMOD & 0xF0) | 0x02;
    
    //Start timer
    TR0 = 1;
    
    return;
}

u32 clock_get_microsec()
{
    return current_microsec;
}

void clock_continue()
{
    TR0 = 1;
}

void clock_pause()
{
    TR0 = 0;
}

void clock_reg_on_tick(ptick_cb_info_t p_cb_info)
{
    //Add to list
    p_cb_info->current_tick = 0;
    if(cb_list == NULL) {
        p_cb_info->p_prev = p_cb_info;
        p_cb_info->p_next = p_cb_info;
        cb_list = p_cb_info;
    } else {
        p_cb_info->p_next = cb_list;
        p_cb_info->p_prev = cb_list->p_prev;
        p_cb_info->p_prev->p_next = p_cb_info;
        p_cb_info->p_next->p_prev = p_cb_info;
    }
    
    return;
}

void clock_delay(u32 ms)
{
    u32 begin_time = current_microsec;
    u32 micro_sec = ms * 1000;
    
    while(current_microsec - begin_time < micro_sec);
   
    return;
}

static void on_timer_0() interrupt 1
{
    current_microsec += 100;
    
    if(cb_list != NULL) {
        ptick_cb_info_t p_cb_info = cb_list;
        do{
            (p_cb_info->current_tick)++;
            if(p_cb_info->current_tick >= p_cb_info->signal_tick) {
                p_cb_info->current_tick = 0;
                p_cb_info->callback();
                
            }
            
            p_cb_info = p_cb_info->p_next;
        } while(p_cb_info != cb_list);
    }
    
    TF0 = 0;
    return;
}