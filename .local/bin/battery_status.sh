#!/bin/bash

# Coloque aqui o local que identifica sem seu dispositivo está carregando ou descarregando
# IMPORTANTE ! A saída deve ser em binário, caso contrário resultará em erro!
is_plugged=$(cat /sys/class/power_supply/ACAD/online)

# Coloque aqui o local que identifica o número relativo a porcentagem da bateria de seu dispositivo
battery_level=$(cat /sys/class/power_supply/BAT1/capacity)

# EXTRA! Altere os ícones para qualquer um de sua preferência, assim como os valores da %
# EXTRA! Customize a cor do ícone começando com %{F#} e fechando com %{F-}
if [[ "$is_plugged" -eq 1 ]]; then
    icon=""
else
    if [ "$battery_level" -le 30 ]; then
	icon=""
    elif [ "$battery_level" -le 40 ]; then
	icon=""
    elif [ "$battery_level" -le 60 ]; then
	icon=""
    elif [ "$battery_level" -le 90 ]; then
	icon=""
    else
	icon=""
    fi
fi

echo "$icon $battery_level󰏰 "
