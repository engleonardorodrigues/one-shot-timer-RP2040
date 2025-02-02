/*****************************************************************************************************
 * Título        : Algortimo One Shot Timer para Raspberry Pi Pico W
 * Desenvolvedor : Leonardo Rodrigues
 * Versão        : 1.0.0
 * 
 * Descrição:
 * 
 * Este programa implementa um sistema de controle com one-shot timer, onde, ao pressionar um botão, 
 * inicia-se uma sequência de desligamento dos LEDs. Cada LED apaga após um determinado intervalo de tempo. 
 * O botão só poderá ser acionado novamente após os três LEDs estarem completamente apagados, garantindo 
 * que não haja interrupções no ciclo de temporização.
 * 
 * Materiais utilizados:
 * 
 * 1 - Raspberry Pi Pico W
 * 3 - LEDs coloridos (azul, vermelho e verde)
 * 3 - Resistores de 330 ohms
 * 1 - Simulador Wokwi
 ******************************************************************************************************/

#include <stdio.h>                                                              // Biblioteca padrão de entrada e saída
#include "pico/stdlib.h"                                                        // Biblioteca do SDK padrão do Raspberry Pi Pico
#include "hardware/timer.h"                                                     // Biblioteca para uso de temporizadores

#define LED_AZUL     11                                                         // Define o pino do LED Azul
#define LED_VERMELHO 12                                                         // Define o pino do LED Vermelho
#define LED_VERDE    13                                                         // Define o pino do LED Verde

#define BOTAO         5                                                         // Define o pino do botão

bool led_activate = false;                                                      // Variável global para ativação do LED
volatile bool status_botao = false;                                             // Variável global volátil para armazenar status do botão
int estado = 0;                                                                 // Variável para armazenar o estado da sequência

int64_t turn_off_callback(alarm_id_t id, void *user_data) {                     // Função de callback do temporizador
    switch (estado) {                                                           // Seleciona o estado atual
        case 0:                                                                 
            gpio_put(LED_AZUL, 0);                                              // Desliga o LED Azul
            estado = 1;                                                         // Avança para o próximo estado
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);              // Aguarda 3 segundos
            break;                                                              // Sai do switch

        case 1:                                                                 
            gpio_put(LED_VERMELHO, 0);                                          // Desliga o LED Vermelho
            estado = 2;                                                         // Avança para o próximo estado
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);              // Aguarda 3 segundos
            break;                                                              // Sai do switch

        case 2:                                                                 
            gpio_put(LED_VERDE, 0);                                             // Desliga o LED Verde
            estado = 0;                                                         // Retorna ao estado inicial
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);              // Aguarda 3 segundos
            status_botao = false;                                               // Reseta o status do botão
            break;                                                              // Sai do switch
        default:                                                                // Caso padrão (não utilizado)
            break;                                                              // Sai do switch
    }
    return 0;                                                                   // Retorna 0 para indicar sucesso
}

int main() {                                                                    // Função principal do programa
    stdio_init_all();                                                           // Inicializa a comunicação serial
    gpio_init(LED_AZUL);                                                        // Inicializa o pino do LED Azul
    gpio_init(LED_VERMELHO);                                                    // Inicializa o pino do LED Vermelho
    gpio_init(LED_VERDE);                                                       // Inicializa o pino do LED Verde
    gpio_init(BOTAO);                                                           // Inicializa o pino do botão

    gpio_set_dir(LED_AZUL, GPIO_OUT);                                           // Configura o LED Azul como saída
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);                                       // Configura o LED Vermelho como saída
    gpio_set_dir(LED_VERDE, GPIO_OUT);                                          // Configura o LED Verde como saída

    gpio_set_dir(BOTAO, GPIO_IN);                                               // Configura o botão como entrada
    gpio_pull_up(BOTAO);                                                        // Ativa o pull-up interno do botão

    gpio_put(LED_AZUL, 0);                                                      // Garante que o LED Azul começa apagado
    gpio_put(LED_VERMELHO, 0);                                                  // Garante que o LED Vermelho começa apagado
    gpio_put(LED_VERDE, 0);                                                     // Garante que o LED Verde começa apagado

    alarm_id_t alarm = add_alarm_in_ms(3000, turn_off_callback, NULL, false);   // Inicia o temporizador

    while (true) {                                                              // Loop principal infinito
        if ((gpio_get(BOTAO) == 0) && (status_botao == false)) {                // Verifica se o botão foi pressionado
            gpio_put(LED_AZUL, 1);                                              // Acende o LED Azul
            gpio_put(LED_VERMELHO, 1);                                          // Acende o LED Vermelho
            gpio_put(LED_VERDE, 1);                                             // Acende o LED Verde
            status_botao = true;                                                // Marca que o botão foi pressionado
        }
    }
}