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
#include <reg52.h>

#include "common.h"
#include "clock.h"
#include "serial.h"
#include "test.h"
#include "light.h"
#include "ac.h"
#include "command.h"

void main()
{
    //Initialize
    clock_init();
    ac_init();
    serial_init();
    light_init();
    
    light_ready_on();
    
    //Test
    if(if_test()) {
        test();
    }
    
    ES = 1;
    
    while(true) {
        if(ac_on()) {
            light_ac_on();
        } else {
            light_ac_off();
        }
        light_status_next();
    }
}

void on_serial() interrupt 4
{
    u8 data_recv;
    if(RI == 0) {
        return;
    }
    
    serial_recv(&data_recv);
    command_exec(data_recv);
}