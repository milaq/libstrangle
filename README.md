# WARNING: Unmaintained fork!

this is just a (unmaintained) fork of: https://gitlab.com/torkel104/libstrangle

# libstrangle
Frame rate limiter for Linux/OpenGL.
## Usage
Cap the FPS (frames per second) of a chosen game by including libstrangle.so in LD_PRELOAD. The environment variable FPS needs to be set first.
Example:
```
export FPS=60
LD_PRELOAD="libstrangle.so:${LD_PRELOAD}" /path/to/game
```
The included script strangle.sh, which installs into your PATH as just "strangle", can be used to simplify this.
Examples:
```
strangle 60 /path/to/game
```
Vertical sync can be controlled by setting the VSYNC environment variable. 0 to turn off, 1 and higher to turn on. Higher numbers will result in lower FPS. 2 will give FPS equal to half the refresh rate, 3 to one third etc. -1 might give adaptive vsync (unconfirmed).
Examples:
```
VSYNC=2 strangle /path/to/game
VSYNC=1 strangle 40 /path/to/game
```
### Steam
You can use this with Steam by right-clicking on a game in your library and selecting Properties and then SET LAUNCH OPTIONS... under the General tab. In the input box type:
`strangle <somenumber> %command%`
## Building
If you installed a version before 2016-05-17 you should manually remove the files /usr/bin/strangle, /usr/lib/i386-linux-gnu/libstrangle.so and /usr/lib/x86_64-linux-gnu/libstrangle.so - The paths have changed.
Typically you'll use these commands to build the program
```
make
sudo make install
```

**Debian**, **Ubuntu** and derivates may need the `libc6-dev-i386` package.

**OpenSUSE** needs these packages:
```
glibc-devel-32bit
gcc
gcc-32bit
```
## Compatibility
As of 2017-02-07 it seems to work with most games, including WINE.
## Errata
Might crash if used together with other libs that hijack dlsym, such as Steam Overlay. It seems to work with Steam Overlay when placed at the end of LD_PRELOAD for some reason.
