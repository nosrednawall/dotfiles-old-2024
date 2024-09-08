#!/bin/bash

# IDE
sudo apt install emacs-gtk geany
git clone --depth 1 https://github.com/doomemacs/doomemacs ~/.config/emacs
~/.config/emacs/bin/doom install  # Cuidado para nao sobreescrever os arquivos do dotfiles
