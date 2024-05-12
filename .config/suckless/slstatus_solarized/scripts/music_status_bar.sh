#!/bin/bash

state=$(mpc status %state%)
if [ "$state" == "paused"  ]; then
	echo ""
else
	icon="󰝚"
	artist=$(mpc -f %artist% current  | cut -c 1-20)
	time=$(mpc -f %time% current)
	title=$(mpc -f %title% current  | cut -c 1-20)
	echo "^b#002b36^^c#2aa198^$icon ^b#002b36^^c#93a1a1^$title[$artist]"
fi
