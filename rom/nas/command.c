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

#include "command.h"
#include "light.h"
#include "ac.h"
#include "serial.h"

static ret_magic()
{
    u8 ret = MAGIC;
    
    serial_send(&ret, 1);
    
    return;
}

static void clear_all()
{
    int i;
    for(i = 0; i < 8; i++) {
        light_status_set(i, COLOR_OFF);
    }
    
    return;
}

static void light_set(u8 param)
{
    u8 index = param & 0x07;
    if(param & 0x08) {
        light_status_set(index, COLOR_GREEN);
        
    } else {
        light_status_set(index, COLOR_RED);
        
    }
    
    return;
}

static void light_off(u8 param)
{
    u8 index = param & 0x07;

    light_status_set(index, COLOR_OFF);

    return;
}

static void get_ac_stat()
{
    u8 ret;
    
    if(ac_on()) {
        ret = 0x01;

    } else {
        ret = 0x00;
    }
        
    serial_send(&ret, 1);
    
    return;
}

void command_exec(u8 cmd)
{
    switch(CMD(cmd)) {
        case CMD_MAGIC:
            ret_magic();
            break;
        
        case CMD_CLEAR:
            clear_all();
            break;
        
        case CMD_LIGHT_SET:
            light_set(PARAM(cmd));
            break;
        
        case CMD_LIGHT_OFF:
            light_off(PARAM(cmd));
            break;
        
        case CMD_GET_AC_STAT:
            get_ac_stat();
            break;
        
        default:
            return;
    }
}