#!/bin/bash
pgrep -x  numlockx > /dev/null || numlockx &
bash ~/.local/bin/if_monitor.sh
pulseaudio --daemonize
xfce4-power-manager --daemon
pgrep -x xautolock > /dev/null || xautolock -time 10 -locker slock &
redshift -P -O 4500 &
nitrogen --restore &
#compton --backend glx --vsync drm --unredir-if-possible --paint-on-overlay -b
#picom --animations -b --conf ~/.config/picom.conf
picom --animations -b
pgrep -x dunst > /dev/null || dunst &
pgrep -x nm-tray > /dev/null || nm-tray &
copyq &
pgrep -x pasystray > /dev/null || pasystray &
pgrep -x mpd > /dev/null || mpd ~/.config/mpd/mpd.conf
