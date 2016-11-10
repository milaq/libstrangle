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
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned long GLXDrawable;
typedef void Display;
typedef void* EGLDisplay;
typedef void* EGLSurface;
typedef unsigned int EGLBoolean;

static struct timespec oldTimestamp,
                       newTimestamp,
                       sleepyTime,
                       remainingTime;

static const clockid_t CLOCKTYPE = CLOCK_MONOTONIC_RAW;

static long targetFrameTime = -1;

static void limiter(void) {
    if (targetFrameTime < 0) {
        long tmp;
        char *env;
        targetFrameTime = 0;

        env = getenv("FPS");
        if (env != NULL) {
            tmp = strtol(env, NULL, 10);
            if (tmp > 0) {
                    targetFrameTime = 1000000000 / tmp;
            } else {
                return;
            }
        } else {
            return;
        }
    } else if (targetFrameTime == 0) {
        return;
    }

    if (clock_gettime(CLOCKTYPE, &newTimestamp) == 0) {
        sleepyTime.tv_nsec = targetFrameTime - newTimestamp.tv_nsec + oldTimestamp.tv_nsec;
        while (sleepyTime.tv_nsec > 0 && sleepyTime.tv_nsec < targetFrameTime) {
            // sleep in smaller and smaller intervals
            sleepyTime.tv_nsec /= 2;
            nanosleep(&sleepyTime, &remainingTime);
            clock_gettime(CLOCKTYPE, &newTimestamp);
            sleepyTime.tv_nsec = targetFrameTime - newTimestamp.tv_nsec + oldTimestamp.tv_nsec;
            // For FPS == 1 this is needed as tv_nsec cannot exceed 999999999
            sleepyTime.tv_nsec += newTimestamp.tv_sec*1000000000 - oldTimestamp.tv_sec*1000000000;
        }
        clock_gettime(CLOCKTYPE, &oldTimestamp);
    }
    return;
}

void glXSwapBuffers(Display *dpy, GLXDrawable drawable) {
    void (*realFunction) (Display *dpy, GLXDrawable drawable);
    realFunction = dlsym(RTLD_NEXT, "glXSwapBuffers");
    realFunction(dpy, drawable);
    limiter();
    return;
}

EGLBoolean eglSwapBuffers(EGLDisplay display, EGLSurface surface) {
    EGLBoolean (*realFunction) (EGLDisplay display, EGLSurface surface);
    EGLBoolean ret;
    realFunction = dlsym(RTLD_NEXT, "eglSwapBuffers");
    ret = realFunction(display, surface);
    limiter();
    return ret;
}
