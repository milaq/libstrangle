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

#define _GNU_SOURCE

#include "glx.h"
#include "libstrangle.h"
#include "real_dlsym.h"

#include <dlfcn.h>
#include <stdlib.h>

void glXSwapBuffers( Display *dpy, GLXDrawable drawable ) {
	void (*realFunction)( Display *dpy, GLXDrawable drawable )
	= real_dlsym( RTLD_NEXT, "glXSwapBuffers" );

	// The buffer swap is called before the wait in hope that it will reduce perceived input lag
	realFunction( dpy, drawable );
	limiter();
}

void glXSwapIntervalEXT( Display *dpy, GLXDrawable drawable, int interval ) {
	void (*realFunction)( Display *dpy, GLXDrawable drawable, int interval )
	= real_dlsym( RTLD_NEXT, "glXSwapIntervalEXT" );
	realFunction( dpy, drawable, getInterval( interval ) );
}

int glXSwapIntervalSGI( int interval ) {
	int (*realFunction)( int interval )
	= real_dlsym( RTLD_NEXT, "glXSwapIntervalSGI" );
	return realFunction( getInterval( interval ) );
}

int glXSwapIntervalMESA( unsigned int interval ) {
	int (*realFunction)( int interval )
	= real_dlsym( RTLD_NEXT, "glXSwapIntervalMESA" );
	return realFunction( getInterval( interval ) );
}

void *glXGetProcAddress( const GLubyte * procName ) {
	void *func = getStrangleFunc( (const char*)procName );
	if ( func != NULL ) {
		return func;
	}

	void *(*realFunction)( const GLubyte * procName )
	= real_dlsym( RTLD_NEXT, "glXGetProcAddress" );
	return realFunction( procName );
}

void *glXGetProcAddressARB( const GLubyte * procName ) {
	void *func = getStrangleFunc( (const char*)procName );
	if ( func != NULL ) {
		return func;
	}

	void *(*realFunction)( const GLubyte * procName )
	= real_dlsym( RTLD_NEXT, "glXGetProcAddressARB" );
	return realFunction( procName );
}

Bool glXMakeCurrent( Display * dpy, GLXDrawable drawable, GLXContext ctx ) {
	Bool (*realFunction)( Display * dpy, GLXDrawable drawable, GLXContext ctx )
	= real_dlsym( RTLD_NEXT, "glXMakeCurrent" );
	Bool ret = realFunction( dpy, drawable, ctx );
	setVsync();
	return ret;
}
