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

#ifndef COMMAND_H_INCLUDE
#define COMMAND_H_INCLUDE

#include "common.h"

#define CMD_MASK        0xF0
#define PARAM_MASK      0x0F

#define CMD(val)    (((val) & CMD_MASK) >> 4)
#define PARAM(val)  ((val) & PARAM_MASK)

/*
 * Command format:
 *  |7         4|3         0|
 *  |  Command  |   Param   |
 */
#define CMD_CLEAR       0x01

/*
 * Parameter format
 *  |           3           |2      0|
 *  | color(1 green, 0 red) | index  |
 */
#define CMD_LIGHT_SET   0x02

/*
 * Parameter format
 *  | 3 |2      0|
 *  | 0 | index  |
 */
#define CMD_LIGHT_OFF   0x03

#define CMD_GET_AC_STAT 0x04

void    command_exec(u8 cmd);

#endif  //! COMMAND_H_INCLUDE