#!/bin/bash

tempCpu=$(sensors | awk '/edge/ {print$2}' | sed 's/+//')
#usageCpu=$(top -bn1 | grep load | awk '{printf "%.2f%%\t\t\n", $(NF-2)}')
icon="^b#282828^^c#89B482^"

read cpu a b c previdle rest < /proc/stat
prevtotal=$((a+b+c+previdle))
sleep 0.5
read cpu a b c idle rest < /proc/stat
total=$((a+b+c+idle))
usageCpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))

echo "$icon ^b#282828^^c#dfbf8e^$usageCpu󰏰 $tempCpu"
