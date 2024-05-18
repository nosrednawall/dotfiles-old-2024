#!/bin/bash

muteVol=$(pactl get-sink-mute @DEFAULT_SINK@ | grep "sim" -ic)
muteMic=$(pactl get-source-mute @DEFAULT_SOURCE@ | grep 'sim' -ic)
volume=$(pactl get-sink-volume @DEFAULT_SINK@ | grep "Volume" | awk '{print$5}' | sed 's/%//')
microfone=$(pactl get-source-volume @DEFAULT_SOURCE@ | grep "Volume" | awk '{print$5}' | sed 's/%//')
camera=$(fuser /dev/video*)
brilho=$(brightnessctl | awk '/%/ {print$4}' | cut -c 2-4 | sed 's/%//' | sed 's/)//')
microfoneOn=$(cat /proc/asound/card0/pcm3p/sub0/status | grep "RUNNING")
separador="^b#002b36^^c#eee8d5^|"

if [ "$muteVol" -eq 1 ]; then
    iconVolume="^b#002b36^^c#4A5947^󰸈 $volume󰏰"
else
    if [ "$volume" -le 30 ]; then
	iconVolume="^b#002b36^^c#859900^󰕿 ^b#002b36^^c#93a1a1^$volume󰏰"
    elif [ "$volume" -le 60 ]; then
	iconVolume="^b#002b36^^c#859900^󰖀 ^b#002b36^^c#93a1a1^$volume󰏰"
    elif [ "$volume" -ge 61 ]; then
	iconVolume="^b#002b36^^c#859900^󰕾 ^b#002b36^^c#93a1a1^$volume󰏰"
    fi
fi

if [ "$muteMic" -eq 1 ]; then
    iconMic="^b#002b36^^c#4A5947^ $microfone󰏰"
else
    iconMic="^b#002b36^^c#d33682^ ^b#002b36^^c#93a1a1^$microfone󰏰"
fi

if [ -z "$camera" ]; then
    iconCam=""
else
    iconCam=" $separador ^b#002b36^^c#dc322f^ ^b#002b36^^c#93a1a1^ On"
fi

brilhoIcone="^b#002b36^^c#268bd2^󰃠 ^b#002b36^^c#93a1a1^$brilho󰏰"

echo "$separador $brilhoIcone $separador $iconVolume $separador $iconMic$iconCam"
