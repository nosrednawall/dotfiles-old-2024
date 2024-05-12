# dmenu - dynamic menu
dmenu is an efficient dynamic menu for X.

## Screenshots
![Dmenu screenshot](https://i.imgur.com/HCSZNun.png)

## Requirements
In order to build dmenu you need the Xlib header files.


## Installation
Edit config.mk to match your local setup (dmenu is installed into the `/usr/local` namespace by default).

Afterwards enter the following command to build and install dmenu
(if necessary as root):
```
make clean install
```
## Patches
 - dmenu-border
 - dmenu-center
 - dmenu-highlight
 - dmenu-lineheight
 - dmenu-numbers
