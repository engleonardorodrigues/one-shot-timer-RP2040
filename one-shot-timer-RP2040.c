#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_AZUL     11
#define LED_VERMELHO 12
#define LED_VERDE    13

#define BOTAO         5

bool led_activate = false;
volatile bool status_botao = false;
int estado = 0;

int64_t turn_off_callback(alarm_id_t id, void *user_data){


    switch (estado) {
        case 0:                                                                 // Estado: Vermelho aceso por 3 segundos
            gpio_put(LED_AZUL, 0);                                              // Desliga o LED ******
            estado = 1;                                                         // Avança para o próximo estado
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);              // Aguarda 3 segundos
            break;

        case 1:                                                                 // Estado: Vermelho aceso por 3 segundos
            gpio_put(LED_VERMELHO, 0);                                              // Desliga o LED ******
            estado = 2;                                                         // Avança para o próximo estado
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);              // Aguarda 3 segundos
            break;

        case 2:                                                                 // Estado: Vermelho aceso por 3 segundos
            gpio_put(LED_VERDE, 0);                                             // Desliga o LED ******
            estado = 0;                                                         // Avança para o próximo estado
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);              // Aguarda 3 segundos
            status_botao = false;
            break;
        default:
        break;

     
     return 0;
}
}

int main()
{
    stdio_init_all();
    
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);

    gpio_init(BOTAO);

    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    gpio_put(LED_AZUL,     0);
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE,    0);


    alarm_id_t alarm = add_alarm_in_ms(3000, turn_off_callback, NULL, false);

    while (true) {
        
    if((gpio_get(BOTAO) == 0) && (status_botao == false)){
        
        gpio_put(LED_AZUL,     1);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE,    1);
        status_botao = true;

     }

    }
}
