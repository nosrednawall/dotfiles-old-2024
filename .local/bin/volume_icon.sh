#!/bin/bash

muteVol=$(pactl get-sink-mute @DEFAULT_SINK@ | grep "sim" -ic)
muteMic=$(pactl get-source-mute @DEFAULT_SOURCE@ | grep 'sim' -ic)
volume=$(pactl get-sink-volume @DEFAULT_SINK@ | grep "Volume" | awk '{print$5}' | sed 's/%//')
microfone=$(pactl get-source-volume @DEFAULT_SOURCE@ | grep "Volume" | awk '{print$5}' | sed 's/%//')
camera=$(fuser /dev/video*)

if [ "$muteVol" -eq 1 ]; then
    icon="󰸈 "
else
    if [ "$volume" -le 30 ]; then
	icon="󰕿 "
    elif [ "$volume" -le 60 ]; then
	icon="󰖀 "
    elif [ "$volume" -ge 61 ]; then
	icon="󰕾 "
    fi
fi

if [ "$muteMic" -eq 1 ]; then
    iconMic=" "
else
    iconMic=" "
fi

if [ -z "$camera" ]; then
    iconCam=""
else
    iconCam="^b#282828^^c#fb4934^ "
fi
echo "^b#282828^^c#89B482^$icon^b#282828^^c#dfbf8e^$volume󰏰 ^b#282828^^c#89B482^$iconMic^b#282828^^c#dfbf8e^$microfone󰏰 $iconCam"
