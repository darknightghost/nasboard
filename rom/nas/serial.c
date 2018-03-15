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
#include "serial.h"
#define T2MOD       *((u8*)(0xC9))

sbit serial_lock = P1 ^ 7;

void serial_init()
{
    ES = 0;  
    TI = 0;
    RI = 0;
    
    SCON = 0x50;
    RCAP2L = TC_VAL & 0xFF;
    TL2 = TC_VAL & 0xFF;
    RCAP2H =  TC_VAL >> 8;
    TH2 = TC_VAL >> 8; 
    
    #if SERIAL_SMOD == 1
        PCON |= 1 << 7; 
    #endif
     
    ET2 = 0;
    T2CON = 0x34;
    serial_lock = 0;
}

void serial_send(const u8* p_data, size_t size)
{
    const u8* p = p_data;
    size_t count;
       
    for(count = 0;
        count < size;
        count++, p++) {
        TI = 0;
        SBUF = *p;
        while(TI == 0);
            
    }
    TI = 0;
    
    return;
}

void serial_recv(u8* p_data)
{
    while(RI == 0);
    *p_data = SBUF;
    RI = 0;
    return;
}