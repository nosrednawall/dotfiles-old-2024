#!/bin/bash
monitor=$(xrandr | grep "HDMI-0 connected" -ci | cut -c 1-16 )

if [ $monitor -eq 1  ]
then
	xrandr --output HDMI-0 --auto --rotate normal --dpi 96 --output eDP-1-1 --auto --primary  --rotate normal --left-of HDMI-0 --dpi 96
else
	xrandr --output  HDMI-0 --off --output eDP-1-1 --primary --auto --rotate normal --dpi 96
fi
