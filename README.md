# libstrangle
Framerate limiter for Linux
## Usage
Apply a framerate limit to a chosen game by including libstrangle.so in LD_PRELOAD. The enviroment variable FPS needs to be set first.  
Example:
```
export FPS=60
LD_PRELOAD="libstrangle.so:${LD_PRELOAD}" /path/to/game
```
The included script strangle.sh, which installs into your PATH as just "strangle", can be used to simplify this.  
Examples:
```
strangle 60 /path/to/game
strangle /path/to/game FPS=24
```
### Steam
You can use this with Steam by right-clicking on a game in your library and selecting Properties and then SET LAUNCH OPTIONS... under the General tab. In the input box type:
`strangle FPS=somenumber %command%`
## Building
If you installed a version before 2016-05-17 you should manually remove the files /usr/bin/strangle, /usr/lib/i386-linux-gnu/libstrangle.so and /usr/lib/x86_64-linux-gnu/libstrangle. The paths have changed.

You'll need the headers `GL/glx.h` and `EGL/egl.h` to build this.  
**Debian** needs these packages:
```
mesa-common-dev
libegl1-mesa-dev
libc6-dev-i386
```
**OpenSUSE** needs these packages:
```
Mesa-libGL-devel
Mesa-libEGL-devel
glibc-devel-32bit
gcc
gcc-32bit
```
## Errata
Does not work with all games, e.g. Doom 3 and Xonotic.
## FAQ
Q: Isn't there an easier way of doing this?  
A: Probably?!
