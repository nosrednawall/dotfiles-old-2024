#!/bin/bash

# Gerenciador de sessao
sudo apt install -y lightdm  lightdm-gtk-greeter

# Configurar o lightdm para abrir apenas no monitor do notebook
sudo cat > /usr/share/multiple-monitors.sh << EOF
#!/bin/bash
xrandr --output  HDMI-0 --off --output eDP-1-1 --primary --mode 1920x1080 --rotate normal --dpi 96
EOF
sudo chmod +x /usr/share/multiple-monitors.sh
sudo sed -i 's|^\#display-setup-script=|display-setup-script=/usr/share/multiple-monitors.sh|' /etc/lightdm/lightdm.conf
