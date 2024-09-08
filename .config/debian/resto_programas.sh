#!/bin/bash

# Pass, qtpass, pinentry e askpass
sudo apt install pass qtpass pinentry-gnome3 ssh-askpass-gnome

# O resto dos programas
sudo apt install feh rofi network-manager xautolock picom dunst xdotool copyq solaar blueman flameshot btop qalculate-gtk libnotify-bin gpicview fonts-bebas-neue yt-dlp gpm aria2

# Fontes microsoft
sudo apt install cabextract curl fontconfig xfonts-utils
sudo apt install ttf-mscorefonts-installer

# Office
sudo apt install libreoffice-gtk3 libreoffice-l10n-pt-br libreoffice atril xournalpp

# Google-chrome
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt install ./google-chrome-stable_current_amd64.deb
rm -rf google-chrome-stable_current_amd64.deb
