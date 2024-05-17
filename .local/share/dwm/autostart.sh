#!/bin/bash
xrdb ~/.Xresources
pgrep -x mate-power-manager > /dev/null || mate-power-manager &
pgrep -x xautolock > /dev/null || xautolock -time 15 -locker ~/.local/bin/slock_personalizado -detectsleep &
redshift -P -O 4000 &
picom -b
pgrep -x dunst > /dev/null || dunst &
pgrep -x nm-applet > /dev/null || nm-applet &
copyq &
pgrep -x pasystray > /dev/null || pasystray &
pgrep -x solaar > /dev/null || solaar -w hide &
# pgrep -x mpd > /dev/null || mpd &
# pgrep -x blueman-applet > /dev/null || blueman-applet &
bash ~/.local/bin/if_monitor.sh
#feh --recursive --bg-fill --randomize ~/.wallpapers/* &
bash ~/.fehbg
pgrep -x slstatus > /dev/null || slstatus &
