/*
Copyright (C) 2016-2017 Björn Spindel

This file is part of libstrangle.

libstrangle is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libstrangle is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libstrangle.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBSTRANGLE_H_
#define LIBSTRANGLE_H_

void init( void ) __attribute__ ((constructor));
void *getStrangleFunc( const char *symbol );

void *dlsym( void *handle, const char *name );
int getInterval( int interval );
void setVsync( void );
void limiter( void );

#endif
