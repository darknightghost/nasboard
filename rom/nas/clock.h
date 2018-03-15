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

#ifndef CLOCK_H_INCLUDE
#define CLOCK_H_INCLUDE

#include "common.h"

#define CRYSTAL_FREQ        24000000
#define TICK_MICROSECS      100

typedef struct  _tick_cb_info {
    struct _tick_cb_info*       p_prev;
    struct _tick_cb_info*       p_next;
    u32                         signal_tick;
    u32                         current_tick;
    void                        (*callback)();
} tick_cb_info_t, *ptick_cb_info_t;

void        clock_init();
u32         clock_get_microsec();
void        clock_continue();
void        clock_pause();
void        clock_reg_on_tick(ptick_cb_info_t p_cb_info);
void        clock_delay(u32 ms);

#endif  //! CLOCK_H_INCLUDE