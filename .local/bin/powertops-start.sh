#!/bin/bash

# Função para desativar a economia de energia para um dispositivo específico
disable_power_saving_for_device() {
  DEVICE_ID="046d:c548"  # ID do dispositivo USB Logitech a ser excluído
  for dev in $(ls /sys/bus/usb/devices/*/idVendor | grep -l ${DEVICE_ID%:*}); do
    dev_path=$(dirname $dev)
    if grep -q $DEVICE_ID $dev_path/idProduct; then
      echo "Disabling power saving for Logitech device $dev_path"
      echo on > "$dev_path/power/control"
    fi
  done
}

# Função para aplicar as configurações do powertop
apply_powertop() {
  powertop --auto-tune &
  POWERTOP_PID=$!

  # Dá ao powertop um tempo para aplicar as configurações
  sleep 5

  # Desativa a economia de energia para o dispositivo Logitech específico
  disable_power_saving_for_device

  # Aguarda o término do powertop (opcional, se você quiser que o script continue rodando)
  wait $POWERTOP_PID
}

# Verifica o estado da bateria
BATTERY_STATE=$(upower -i /org/freedesktop/UPower/devices/battery_BAT1 | grep 'state:' | awk '{print$2}' | grep 'discharging' -ic)

if [ "$BATTERY_STATE" == "on-line" ]; then
  echo "Running on AC power. Applying performance optimizations."
  # Adicione aqui qualquer configuração específica para quando o computador está conectado à energia
  apply_powertop
elif [ "$BATTERY_STATE" == "off-line" ]; then
  echo "Running on battery power. Applying power-saving optimizations."
  # Adicione aqui qualquer configuração específica para quando o computador está na bateria
  apply_powertop
else
  echo "Unable to determine power state. Defaulting to power-saving optimizations."
  apply_powertop
fi
