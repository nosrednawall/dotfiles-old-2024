#!/bin/bash
separador="^b#002b36^^c#eee8d5^|"
state=$(mpc status %state%)

# pausado
if [ "$state" == "paused"  ]; then
	echo ""

# mpd desligado
elif [ "$state" == "" ]; then
	echo ""

# mpd funcionando
else
	icon="󰝚"
	#artista=$(mpc -f %artist% current  | cut -c 1-30)
	artista=$(mpc -f %artist% current)
	artist="[$artista]"
	time=$(mpc -f %time% current)
	#title=$(mpc -f %title% current  | cut -c 1-30)
	title=$(mpc -f %title% current)
	printf "^b#002b36^^c#2aa198^$icon ^b#002b36^^c#93a1a1^$title $artist $separador"
fi
