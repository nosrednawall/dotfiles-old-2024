#!/bin/bash

state=$(mpc status %state%)
if [ "$state" == "paused"  ]; then
	echo ""
else
	icon="󰝚"
	artist=$(mpc -f %artist% current)
	time=$(mpc -f %time% current)
	title=$(mpc -f %title% current)
	echo "$icon $title [$artist]"
fi
