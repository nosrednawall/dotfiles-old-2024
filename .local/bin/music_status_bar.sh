#!/bin/bash

title=$(mpc -f %title% current)

if [ "$title" == ""  ]; then
    echo ""
else
    icon="󰝚"
    artist=$(mpc -f %artist% current)
    time=$(mpc -f %time% current)

    echo "$icon $title[$artist]"
fi
