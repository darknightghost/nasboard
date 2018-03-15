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

#ifndef COMMON_H_INCLUDE
#define COMMON_H_INCLUDE

#include <stdlib.h>

typedef unsigned char   u8;
typedef signed char     s8;
typedef unsigned short  u16;
typedef signed short    s16;
typedef unsigned long   u32;
typedef signed long     s32;

typedef u8              bool;

#define true            1
#define false           0

#ifndef NULL
    #define NULL            ((void*)0)
#endif
    
#endif  //! COMMON_H_INCLUDE