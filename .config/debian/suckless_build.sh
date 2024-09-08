#!/bin/bash

# Dependencias para compilar
sudo apt install -y make gcc build-essential libx11-dev libxft-dev libxinerama-dev  libharfbuzz-dev  libimlib2-dev libxrandr-dev

# dwm
cd ~/.dotfiles/.config/suckless/dwm
make
sudo make clean install

# cria lancador do dwm
sudo mkdir -p /usr/share/xsessions/
sudo cp dwm.desktop /usr/share/xsessions/

# st
cd ~/.dotfiles/.config/suckless/st
make
sudo make clean install

# dwmblocks
cd ~/.dotfiles/.config/suckless/dwmblocks
make
sudo make clean install

# slock
cd ~/.dotfiles/.config/suckless/slock
make
sudo make clean install

# dmenu
cd ~/.dotfiles/.config/suckless/dmenu
make
sudo make clean install
