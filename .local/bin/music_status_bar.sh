#!/bin/bash

state=$(mpc status %state%)
if [ "$state" == "paused"  ]; then
	echo ""
else
	icon="󰝚"
	artist=$(mpc -f %artist% current)
	time=$(mpc -f %time% current)
	title=$(mpc -f %title% current)
	echo "^b#282828^^c#89B482^$icon ^b#282828^^c#ebdbb2^$title[$artist]"
fi
