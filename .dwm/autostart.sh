#!/bin/bash
xrdb ~/.Xresources
pulseaudio --daemonize
xfce4-power-manager --daemon
pgrep -x xautolock > /dev/null || xautolock -time 16 -locker ~/.local/bin/slock_personalizado &
redshift -P -O 4500 &
picom -b
pgrep -x dunst > /dev/null || dunst &
pgrep -x nm-tray > /dev/null || nm-tray &
copyq &
pgrep -x pasystray > /dev/null || pasystray &
pgrep -x solaar > /dev/null || solaar -w hide &
pgrep -x blueman-applet > /dev/null || blueman-applet &
pgrep -x mpd > /dev/null || mpd ~/.config/mpd/mpd.conf
bash ~/.local/bin/if_monitor.sh
# nitrogen --restore &
# feh --recursive --bg-fill --randomize ~/.wallpapers/
# feh --recursive --bg-fill --randomize ~/.wallpapers/* &
feh --recursive --bg-fill ~/.wallpapers/Spaceman-gruvbox.png
pgrep -x slstatus > /dev/null || slstatus &
