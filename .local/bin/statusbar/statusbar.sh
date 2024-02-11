#!/usr/bin/bash

while true :; do

	ARROW_A=$'\x1b[0m\x1b[38;2;104;122;196m\x1b[0m\x1b[48;2;104;122;196m'
	ARROW_B=$'\x1b[38;2;113;151;231m\x1b[0m\x1b[48;2;113;151;231m'
	ARROW_C=$'\x1b[38;2;104;122;196m\x1b[0m\x1b[48;2;104;122;196m'

	status="${ARROW_A} ${ARROW_B}  $(uptime -p) ${ARROW_C} : $(acpi | awk '{print $4}' | sed s/,//) ${ARROW_B}  $(date '+%Y-%m-%d %H:%M') ${ARROW_C} $(free -h | awk '/^Mem:/ {print ":" $3 "/" $2}') ${ARROW_B} 摒 $(curl -s wttr.in/"Tampa,Florida?format=3") ${ARROW_C}"
	xsetroot -name "$status"
	echo "$status"

	sleep 60

done
