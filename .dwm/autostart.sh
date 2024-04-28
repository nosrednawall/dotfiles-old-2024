#!/bin/bash
xrdb ~/.Xresources
pgrep -x mate-power-manager > /dev/null || mate-power-manager &
pgrep -x xautolock > /dev/null || xautolock -time 10 -locker ~/.local/bin/slock_personalizado &
redshift -P -O 4000 &
picom -b
pgrep -x dunst > /dev/null || dunst &
pgrep -x nm-applet > /dev/null || nm-applet &
copyq &
pgrep -x pasystray > /dev/null || pasystray &
pgrep -x solaar > /dev/null || solaar -w hide &
# pgrep -x blueman-applet > /dev/null || blueman-applet &
bash ~/.local/bin/if_monitor.sh
feh --recursive --bg-fill --randomize ~/.wallpapers/* &
pgrep -x slstatus > /dev/null || slstatus &
