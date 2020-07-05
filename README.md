dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

This is my personal build of dwm, with my own keybindings (I don't use a seperate key handler like sxhkd anymore) and various patches applied.
The patches are all listed in the `patches` folder of this repository.
Most of them are directly from suckless's website, but some smaller ones I've added as well to make porting easier.
Previously [I used to fork my build from Luke's build](https://github.com/AlexBocken/dwm_old) of dwm. Many of my keybinds have their origin from that build.
This build has the [nord theme](https://www.nordtheme.com/) colors integrated (I prefer not using the xrdb patch)


Patches
-----------
- urgend border
- actual fullscreen
- barpadding
- bottomstack layout
- centered master layout
- deck layout
- fibonacci layout
- hide vacant tags layout
- info section of bar always uses normal scheme (personal)
- movestack
- status bar on all monitors (personal)
- sticky
- warp mouse to center of focussed window
- scratchpads
- zoom swap


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
