#!/bin/bash

# Carrega configuracoes do tema
source $HOME/.theme_selected

# Carrega as configurações do Xresources
xrdb ~/.Xresources

# Função para verificar se um processo está rodando
is_running() {
    ps aux | grep -v grep | grep -q "$1"
}

# Inicia o mate-power-manager se não estiver rodando
# is_running "mate-power-manager" || mate-power-manager &

# Inicia o xautolock com as configurações personalizadas se não estiver rodando
is_running "xautolock" || xautolock -time 15 -locker ~/.local/bin/dwm/slock_personalizado -detectsleep &

# Inicia o picom em modo background
picom -b

# Inicia o dunst se não estiver rodando
is_running "dunst" || dunst -conf "$HOME/.config/dunst/themes/${THEME_MODE}_${COLOR_MODE}" &
#is_running "dunst" || dunst &

# Executa o script para verificar se o segundo monitor está ativo
bash ~/.local/bin/check_second_monitor_is_active.sh

# Define o papel de parede usando feh
feh --recursive --bg-fill --randomize ~/.wallpapers/${THEME_MODE}/${COLOR_MODE}/* &

# Inicia o copyq se não estiver rodando
copyq &

# Inicia o dwmblocks se não estiver rodando
is_running "dwmblocks" || dwmblocks &

# Inicia o daemon do emacs se não estiver rodando
is_running "emacs --daemon" || emacs --daemon &

#is_running "redshift" || /usr/bin/redshift -l -25.54354018313095:-49.16561321065291 -t 5700:3600 -g 0.8 -m randr &

exit
