#!/bin/bash
monitor=$(xrandr | grep "HDMI-0 connected" | cut -c 1-16 )
string="HDMI-0 connected"

if [[ $monitor == $string ]]
then
	echo "monitor conectado"
	#xrandr --output HDMI-0 --primary --mode 3440x1440 --pos 1920x0 --rotate normal --output eDP-1-1 --mode 1920x1080 --pos 0x360 --rotate normal
	xrandr --output HDMI-0 --auto --rotate normal --dpi 96 --output eDP-1-1 --auto --primary  --rotate normal --left-of HDMI-0 --dpi 96
else
	echo "monitor não conectado"
#	xrandr --output HDMI-0 --off --output eDP-1-1 --primary --mode 1920x1080 --pos 0x0 --rotate normal
	xrandr --output HDMI-0 --off --output eDP-1-1 --primary --auto --rotate normal --dpi 96
fi
