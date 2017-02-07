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

#include "egl.h"
#include "real_dlsym.h"
#include "libstrangle.h"

#include <dlfcn.h>

EGLBoolean eglSwapBuffers( EGLDisplay display, EGLSurface surface ) {
	EGLBoolean (*realFunction)( EGLDisplay display, EGLSurface surface)
	= real_dlsym( RTLD_NEXT, "eglSwapBuffers" );
	EGLBoolean ret;
	ret = realFunction( display, surface );
	limiter();
	return ret;
}
