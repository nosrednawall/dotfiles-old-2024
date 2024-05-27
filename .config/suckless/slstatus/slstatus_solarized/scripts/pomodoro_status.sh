#!/bin/bash

separador="^b#002b36^^c#eee8d5^|"
status=$(/home/anderson/.dotfiles/.local/bin/pomodoro status --format "^b#002b36^^c#268bd2^⏱^c#93a1a1^%r ^c#dc322f^🍅^c#93a1a1^%c" | grep -m1 "🍅")

if [ -z "$status" ];then
   printf ""
else
   printf "$status $separador "
fi
