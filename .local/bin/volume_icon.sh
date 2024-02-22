#!/bin/bash

muteVol=$(pactl get-sink-mute @DEFAULT_SINK@ | grep "sim" -ic)
muteMic=$(pactl get-source-mute @DEFAULT_SOURCE@ | grep 'sim' -ic)
volume=$(pactl get-sink-volume @DEFAULT_SINK@ | grep "Volume" | awk '{print$5}' | sed 's/%//')
microfone=$(pactl get-source-volume @DEFAULT_SOURCE@ | grep "Volume" | awk '{print$5}' | sed 's/%//')

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

echo "$icon$volume󰏰 $iconMic$microfone󰏰 "
