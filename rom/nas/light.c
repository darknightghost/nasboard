/*                    
	Copyright 2018,王思远 <darknightghost.cn@gmail.com>

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

#include "light.h"
#include "reg52.h"
#include <string.h>

sbit    light_ready         = P0 ^ 0;
sbit    light_ac            = P0 ^ 1;
#define light_status_select P2
sbit    light_status_green  = P3 ^ 4;
sbit    light_status_red    = P3 ^ 5;

static u8   colors[8];
#define RED_DEN 2

void light_init()
{
    light_ready = 1;
    light_ac = 1;
    light_status_select = 0xFF;
    memset(colors, 0 ,sizeof(colors));
}

void light_ready_on()
{
    light_ready = 0;
}

void light_ac_on()
{
    light_ac = 0;
}

void light_ac_off()
{
    light_ac = 1;
}

void light_status_set(u8 index, u8 color)
{
    colors[index] = color;
}

static u8 light_index = 0;
static u16 round_count = 0;

void light_status_next()
{
    light_index++;
    
    if(light_index >= 8) {
        light_index = 0;
        round_count++;
    }
    
    light_status_green = 0;
    light_status_red = 0;
    
    light_status_select = ~(u8)(1 << light_index);
    
    switch(colors[light_index]) {
        case COLOR_RED:
            light_status_red = 1;
            light_status_green = 0;
            break;
        
        case COLOR_GREEN:
            light_status_red = 0;
            light_status_green = 1;
            break;
        
        case COLOR_YELLOW:
            if(round_count >= RED_DEN) {
                round_count = 0;
                light_status_red = 1;
                light_status_green = 0;
                
            } else {
                light_status_red = 0;
                light_status_green = 1;
                
            }
            break;
    }
    
    return;
}