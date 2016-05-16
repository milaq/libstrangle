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
You'll need the headers `GL/glx.h` and `EGL/egl.h` to build this. In Debian they can be found in the packages `mesa-common-dev` and `libegl1-mesa-dev`
## Errata
Does not work with all games, e.g. Doom 3 and Xonotic.
## FAQ
Q: Isn't there an easier way of doing this?  
A: Probably?!
