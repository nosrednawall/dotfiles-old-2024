#!/bin/bash

mute=$(pactl get-sink-mute @DEFAULT_SINK@ | grep "sim" -ic)
volume=$(pactl get-sink-volume @DEFAULT_SINK@ | grep "Volume" | awk '{print$5}' | sed 's/%//')

if [ "$mute" -eq 1 ]; then
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

echo "$icon$volume%"
