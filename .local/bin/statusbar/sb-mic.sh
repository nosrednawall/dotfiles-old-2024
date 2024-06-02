#!/bin/sh
# Display an icon if the microphone is muted.
microfoneOn=$(cat /proc/asound/card0/pcm3p/sub0/status | grep "RUNNING")
microfone=$(pactl get-source-volume @DEFAULT_SOURCE@ | grep "Volume" | awk '{print$5}' | sed 's/%//')
muteMic=$(pactl get-source-mute @DEFAULT_SOURCE@ | grep 'sim' -ic)

case "$BLOCK_BUTTON" in
    1) setsid --fork st -e pulsemixer ;;
    3) pactl set-sink-mute @DEFAULT_SINK@ toggle ;;
    4) pactl set-sink-volume @DEFAULT_SINK@ +5% ;;
    5) pactl set-sink-volume @DEFAULT_SINK@ -5% ;;
    8) emacsclient -c "$0" ;;
esac



if [ "$muteMic" -eq 1 ]; then
    iconMic="^c#4A5947^ $microfone󰏰"
else
    iconMic="^c#d33682^ ^c#93a1a1^$microfone󰏰"
fi

echo "$iconMic"
