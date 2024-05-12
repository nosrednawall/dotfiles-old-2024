#!/bin/bash

tempCpu=$(sensors | awk '/edge/ {print$2}' | sed 's/+//')
#usageCpu=$(top -bn1 | grep load | awk '{printf "%.2f%%\t\t\n", $(NF-2)}')
icon="^b#002b36^^c#2aa198^"

read cpu a b c previdle rest < /proc/stat
prevtotal=$((a+b+c+previdle))
sleep 0.5
read cpu a b c idle rest < /proc/stat
total=$((a+b+c+idle))
usageCpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))

if [ "$usageCpu" -le 10 ]; then
    icon="^b#002b36^^c#2aa198^"

elif [ "$usageCpu" -le 40 ]; then
    icon="^b#002b36^^c#b58900^"

elif [ "$usageCpu" -le 60 ]; then
    icon="^b#002b36^^c#cb4b16^"

elif [ "$usageCpu" -le 100 ]; then
    icon="^b#002b36^^c#dc322f^"

else
    icon="^b#002b36^^c#2aa198^"

fi
echo "$icon ^b#002b36^^c#93a1a1^$usageCpu󰏰 $tempCpu"
