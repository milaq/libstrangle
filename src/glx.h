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

#ifndef GLX_H_
#define GLX_H_

#include <stdbool.h>

typedef unsigned long GLXDrawable;
typedef unsigned char GLubyte;
typedef void* GLXContext;
typedef bool Bool;
typedef void Display;

void glXSwapBuffers( Display *dpy, GLXDrawable drawable );
void glXSwapIntervalEXT( Display *dpy, GLXDrawable drawable, int interval );
int glXSwapIntervalSGI( int interval );
int glXSwapIntervalMESA( unsigned int interval );
Bool glXMakeCurrent( Display * dpy, GLXDrawable drawable, GLXContext ctx );

void *glXGetProcAddress( const GLubyte * procName );
void *glXGetProcAddressARB( const GLubyte * procName );

#endif
