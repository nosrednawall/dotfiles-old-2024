#!/bin/bash

separador="^b#002b36^^c#eee8d5^|"

status=$(ip addr show | grep 'enp4s0:' | awk '{print $3}' | sed 's/<//g' | sed 's/>//g')
status_on="BROADCAST,MULTICAST,UP,LOWER_UP"

if [ $status_on == $status ]; then
    ethernet=" $separador ^c#6c71c4^󰈀 ^c#93a1a1^"
else
    ethernet=""
fi

echo "$ethernet"
