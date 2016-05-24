/*
libstrangle - framerate limiter
Copyright (C) 2016 Björn Spindel

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

#include <dlfcn.h>
//#include <GL/glx.h>
//#include <EGL/egl.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned long GLXDrawable;
typedef void Display;
typedef void* EGLDisplay;
typedef void* EGLSurface;
typedef unsigned int EGLBoolean;

static long DESIRED_FPS = 0;

static struct timespec 	oldTimestamp,
			newTimestamp,
			sleepyTime,
			remainingTime;

static const clockid_t clockType = CLOCK_MONOTONIC_RAW;

static void limiter( void ) {
	long targetFrameTime;
	long tmp;
	char *env;

	env = getenv( "FPS" );
	if ( env != NULL ) {
		tmp = strtol( env, NULL, 10 );
		if ( tmp > 0 ) {
			DESIRED_FPS = tmp;
		} else {
			DESIRED_FPS = 0;
		}
	}

	if ( DESIRED_FPS < 1 ) {
		return;
	}

	targetFrameTime = 1000000000 / DESIRED_FPS;

	if ( clock_gettime( clockType, &newTimestamp ) == 0 ) {
		sleepyTime.tv_nsec = targetFrameTime - newTimestamp.tv_nsec + oldTimestamp.tv_nsec;
		while( sleepyTime.tv_nsec > 0 && sleepyTime.tv_nsec < targetFrameTime ) {
			// sleep in smaller and smaller intervals
			sleepyTime.tv_nsec /= 16;
			nanosleep( &sleepyTime, &remainingTime );
			clock_gettime( clockType, &newTimestamp );
			sleepyTime.tv_nsec = targetFrameTime - newTimestamp.tv_nsec + oldTimestamp.tv_nsec;
		}
		clock_gettime( clockType, &oldTimestamp );
	}

	/*
	// simple but too imprecise
	if ( clock_gettime( clockType, &newTimestamp ) == 0 ) {
		sleepyTime.tv_nsec = targetFrameTime - newTimestamp.tv_nsec + oldTimestamp.tv_nsec;
		if( sleepyTime.tv_nsec > 0 ) {
			nanosleep( &sleepyTime, &remainingTime );
		}
		clock_gettime( clockType, &oldTimestamp );
	}
	*/
	return;
}

void glXSwapBuffers( Display *dpy, GLXDrawable drawable ) {
	void (*realFunction)( Display *dpy, GLXDrawable drawable );
	realFunction = dlsym( RTLD_NEXT, "glXSwapBuffers" );
	realFunction( dpy, drawable );
	limiter();
	return;
}
EGLBoolean eglSwapBuffers( EGLDisplay display, EGLSurface surface ) {
	EGLBoolean (*realFunction)( EGLDisplay display, EGLSurface surface);
	EGLBoolean ret;
	realFunction = dlsym( RTLD_NEXT, "eglSwapBuffers" );
	ret = realFunction( display, surface );
	limiter();
	return ret;
}
