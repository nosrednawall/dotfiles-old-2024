#!/bin/bash

xrdb ~/.Xresources
pgrep -x mate-power-manager > /dev/null || mate-power-manager &
pgrep -x xautolock > /dev/null || xautolock -time 15 -locker ~/.local/bin/dwm/slock_personalizado -detectsleep &
picom -b
pgrep -x redshift > /dev/null || redshift -l -25.54354018313095:-49.16561321065291 -t 5700:3600 -g 0.8 -m randr  &
pgrep -x dunst > /dev/null || dunst &
bash ~/.local/bin/check_second_monitor_is_active.sh
#bash ~/.fehbg
feh --recursive --bg-fill --randomize ~/.wallpapers/Solarized/Dark/* &
copyq &
#pgrep -x slstatus > /dev/null || slstatus &
pgrep -x emacs > /dev/null || emacs --daemon &

# olds
#pgrep -x pasystray > /dev/null || pasystray &
# pgrep -x solaar > /dev/null || solaar -w hide &
# pgrep -x nm-applet > /dev/null || nm-applet &
#pgrep -x pasystray > /dev/null || pasystray &
# pgrep -x mpd > /dev/null || mpd &
# pgrep -x blueman-applet > /dev/null || blueman-applet &
#feh --recursive --bg-fill --randomize ~/.wallpapers/* &
