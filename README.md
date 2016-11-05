# libstrangle
Frame rate limiter for Linux/OpenGL.
## Usage
Cap the FPS (frames per second) of a chosen game by including libstrangle.so in LD_PRELOAD. The enviroment variable FPS needs to be set first.
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
### Steam
You can use this with Steam by right-clicking on a game in your library and selecting Properties and then SET LAUNCH OPTIONS... under the General tab. In the input box type:
`strangle <fps-limit> %command%`
## Building
If you installed a version before 2016-05-17 you should manually remove the files /usr/bin/strangle, /usr/lib/i386-linux-gnu/libstrangle.so and /usr/lib/x86_64-linux-gnu/libstrangle.so - The paths have changed.

**Debian**, **Ubuntu** and derivates may need the `libc6-dev-i386` package.

**OpenSUSE** needs these packages:
```
glibc-devel-32bit
gcc
gcc-32bit
```
## Errata
Does not work with all games, e.g. Doom 3 and Xonotic.
## FAQ
Q: Isn't there an easier way of doing this?  
A: Probably?!
