#!/bin/bash

# Verifica o número de pacotes com atualizações disponíveis
updates=$(aptitude search "~U" | wc -l)

# Exibe o número de pacotes com atualizações
echo "^c#6c71c4^󱧕 ^c#93a1a1^$updates"
