#!/bin/bash

# Função para mostrar a notificação de processamento
show_processing() {
    local task_pid=$1
    while kill -0 $task_pid 2>/dev/null; do
        notify-send "Processamento" "Processando... Por favor, aguarde." -u low -t 1000
        sleep 1
    done
}

# Verifique se o PID foi passado como argumento
if [ -z "$1" ]; then
    echo "Uso: $0 <PID>"
    exit 1
fi

TASK_PID=$1

# Mostre a notificação de processamento enquanto a tarefa está em execução
show_processing $TASK_PID

# Aguarde a conclusão da tarefa em segundo plano
wait $TASK_PID

# Mostre uma notificação de conclusão
notify-send "Processamento" "Tarefa concluída!" -u normal
