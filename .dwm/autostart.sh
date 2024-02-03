#!/bin/bash
#pgrep -x dwmblocks > /dev/null || dwmblocks &
#pgrep -x  numlockx > /dev/null || numlockx &
pulseaudio --daemonize
xfce4-power-manager --daemon
pgrep -x xautolock > /dev/null || xautolock -time 5 -locker ~/.local/bin/slock_personalizado &
redshift -P -O 4500 &
#compton --backend glx --vsync drm --unredir-if-possible --paint-on-overlay -b
picom -b
pgrep -x dunst > /dev/null || dunst &
pgrep -x nm-tray > /dev/null || nm-tray &
copyq &
pgrep -x pasystray > /dev/null || pasystray &
pgrep -x mpd > /dev/null || mpd ~/.config/mpd/mpd.conf
bash ~/.local/bin/if_monitor.sh
nitrogen --restore &
#pgrep -x dwmbar-colored > /dev/null || /bin/bash ~/.local/bin/statusbar/dwmbar-colored &
