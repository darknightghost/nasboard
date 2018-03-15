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

#include "test.h"
#include <reg52.h>

#include "light.h"
#include "ac.h"
#include "clock.h"
#include "serial.h"

sbit    test_pin        = P1 ^ 4;

static tick_cb_info_t   tick_info;

bool if_test()
{
    test_pin = 1;
    if(!test_pin) {
        return true;
    } else {
        return false;
    }
}

static u8   index = 0;
static u8   color = COLOR_RED;
static void on_test_clock()
{
    int i;
    index++;
    if(index >= 8) {
        index = 0;
        if(color == COLOR_RED) {
            color = COLOR_GREEN;
        } else {
            color = COLOR_RED;
        }
    }
    
    for(i = 0; i < 8; i++) {
        if(i == index) {
            light_status_set(i, color);
        } else {
            light_status_set(i, COLOR_OFF);
        }
    }
}

void test()
{
    serial_send("\x00\x01\x02\x03\x04\x05", 6);
    serial_send("\x00\x01\x02\x03\x04\x05", 6);
    serial_send("\x00\x01\x02\x03\x04\x05", 6);
    serial_send("\x00\x01\x02\x03\x04\x05", 6);
    serial_send("\x00\x01\x02\x03\x04\x05", 6);
    serial_send("\x00\x01\x02\x03\x04\x05", 6);
    tick_info.signal_tick = 10000;
    tick_info.callback = on_test_clock;
    clock_reg_on_tick(&tick_info);
    while(true) {
        if(ac_on()) {
            light_ac_on();
        } else {
            light_ac_off();
        }
        light_status_next();
    }
}