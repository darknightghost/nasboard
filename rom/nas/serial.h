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

#ifndef SERIAL_H_INCLUDE
#define SERIAL_H_INCLUDE

#include "common.h"
#include "clock.h"
#include <stdlib.h>

#define SERIAL_BAUD     9600
#define SERIAL_SMOD     0

#if SERIAL_SMOD == 0
    #define TC_VAL  (65536 - CRYSTAL_FREQ / 16 / SERIAL_BAUD / 2)
#else
    #define TC_VAL  (65536 - CRYSTAL_FREQ / 32 / SERIAL_BAUD)  
#endif

void    serial_init();
void    serial_send(const u8* p_data, size_t size);
void    serial_recv(u8* p_data);

#endif //! SERIAL_H_INCLUDE


