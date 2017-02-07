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

#include "libstrangle.h"
#include "glx.h"
#include "egl.h"
#include "real_dlsym.h"

#include <dlfcn.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static long targetFrameTime = -1;
static int *vsync = NULL;

void init( void ) {
	long tmp;
	char *env;

	targetFrameTime = 0;

	env = getenv( "FPS" );
	if ( env != NULL ) {
		tmp = strtol( env, NULL, 10 );
		if ( tmp > 0 ) {
			targetFrameTime = 1000000000 / tmp;
		}
	}

	env = getenv( "VSYNC" );
	if ( env != NULL ) {
		char *endptr = NULL;
		tmp = strtol( env, &endptr, 10 );
		if ( env != endptr ) {
			vsync = malloc(sizeof(*vsync));
			*vsync = (int)tmp;
		}
	}
}

void limiter( void ) {
	static const clockid_t clockType = CLOCK_MONOTONIC_RAW;

	static struct timespec oldTimestamp,
	                       newTimestamp,
	                       sleepyTime,
	                       remainingTime;

	if ( targetFrameTime <= 0 ) {
		return;
	}

	if ( clock_gettime( clockType, &newTimestamp ) == 0 ) {
		sleepyTime.tv_nsec = targetFrameTime - newTimestamp.tv_nsec + oldTimestamp.tv_nsec;
		while( sleepyTime.tv_nsec > 0 && sleepyTime.tv_nsec < targetFrameTime ) {

			// sleep in smaller and smaller intervals
			sleepyTime.tv_nsec /= 2;
			nanosleep( &sleepyTime, &remainingTime );
			clock_gettime( clockType, &newTimestamp );
			sleepyTime.tv_nsec = targetFrameTime - newTimestamp.tv_nsec + oldTimestamp.tv_nsec;

			// For FPS == 1 this is needed as tv_nsec cannot exceed 999999999
			sleepyTime.tv_nsec += newTimestamp.tv_sec*1000000000 - oldTimestamp.tv_sec*1000000000;
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
}

void *dlsym( void *handle, const char *name )
{
	void* func = getStrangleFunc( name );
	if ( func != NULL ) {
		return func;
	}

	return real_dlsym( handle, name );
}

void *getStrangleFunc( const char *symbol ) {
    if ( !strcmp( symbol, "dlsym" ) ) {
        return dlsym;
	} else if ( !strcmp( symbol, "glXSwapBuffers" ) ) {
		return (void*)glXSwapBuffers;
	} else if ( !strcmp( symbol, "eglSwapBuffers" ) ) {
		return (void*)eglSwapBuffers;
	} else if ( !strcmp( symbol, "glXGetProcAddress" ) ) {
		return (void*)glXGetProcAddress;
	} else if ( !strcmp( symbol, "glXGetProcAddressARB" ) ) {
		return (void*)glXGetProcAddressARB;
	} else if ( !strcmp( symbol, "glXSwapIntervalEXT" ) ) {
		return (void*)glXSwapIntervalEXT;
	} else if ( !strcmp( symbol, "glXSwapIntervalSGI" ) ) {
		return (void*)glXSwapIntervalSGI;
	} else if ( !strcmp( symbol, "glXSwapIntervalMESA" ) ) {
		return (void*)glXSwapIntervalMESA;
	} else if ( !strcmp( symbol, "glXMakeCurrent" ) ) {
		return (void*)glXMakeCurrent;
	}

	return NULL;
}

int getInterval( int interval ) {
	if ( vsync != NULL ) {
		return *vsync;
	}
	return interval;
}

void setVsync( void ) {
	if ( vsync != NULL ) {
		glXSwapIntervalSGI( *vsync );
	}
}
