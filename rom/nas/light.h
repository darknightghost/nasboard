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

#ifndef LIGHT_H_INCLUDE
#define LIGHT_H_INCLUDE

#include "common.h"

#define COLOR_OFF       0x00
#define COLOR_RED       0x01
#define COLOR_GREEN     0x02
#define COLOR_YELLOW    0x03

void    light_init();
void    light_ready_on();
void    light_ac_on();
void    light_ac_off();
void    light_status_set(u8 index, u8 color);
void    light_status_next();

#endif  //! LIGHT_H_INCLUDE