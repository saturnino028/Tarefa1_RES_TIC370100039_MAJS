/**
 * @brief implementa as funções do joystick
 */
#include "config.h"

/************************ Declaração de Variaveis ************************/

/*********************** Implementação das funções **********************/
/**
 * @brief Configura os pinos ADC
 */
void config_adc()
{
    adc_init();
    adc_gpio_init(adc_jY);//Inicia pino ADC eixo y
    adc_gpio_init(adc_jX);//Inicia pino ADC eixo x
}

/**
 * @brief inicia os pinos de GPIO
 */
void config_pins_gpio()
{
    //Configuração do botao A
    gpio_init(bot_A);
    gpio_pull_up(bot_A);
    gpio_set_dir(bot_A, GPIO_IN);

    //Configuração do botao B
    gpio_init(bot_B);
    gpio_pull_up(bot_B);
    gpio_set_dir(bot_B, GPIO_IN);

    //Configuração do botao do Joystick
    gpio_init(bot_joy);
    gpio_pull_up(bot_joy);
    gpio_set_dir(bot_joy, GPIO_IN);

    //Configuração do Buzzer A
    gpio_init(buz_A);
    gpio_set_dir(buz_A, GPIO_OUT);

    //Configuração do Buzzer B
    gpio_init(buz_B);
    gpio_set_dir(buz_B, GPIO_OUT);

    //Configuração do LED vermelho
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    //Configuração do LED verde
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    //Configuração do LED azul
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
}

/**
 * @brief função usada para calibrar a posição do Joystick
 * @param ssd ponteiro para uso do display
 * @param posicoesjoy é um vetor com as posições de calibração do joystick, nas três primeiras posições
 * estão armazenados os valores de referencia de X - X0, Xmax, Xmin. Nas três últimas, estão os valores
 * de referencia de y - y0, ymax, ymin.
 */

 void calibrar_joy(ssd1306_t *ssd, uint16_t posicoesjoy[6])
 {
     bool cor = true; uint32_t aux1 = 0, aux2 = 0, delay_padrao = 2500;
 
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Primeiro, ", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Vamos Calibrar", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "O Joystick", 8, 48); // Desenha uma string      
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(3000);
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Siga todas", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "As instrucoes", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "A seguir", 8, 48); // Desenha uma string      
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(3000);
     som_buz(1*KHz, 200);
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Espere um pouco", 4, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Fazendo a cali", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "bracao inicial", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(3000);
 
     for(int i = 10; i<100; i++) //Coleta 100 amostras da pos X0 e Y0 (1segundo de amostra)
     {
         adc_select_input(0); //Seleciona o canal em que o eixo y esta conectado GPIO 26
         aux2 = adc_read() + aux2;
         sleep_ms(5);
 
         adc_select_input(1); //Seleciona o canal em que o eixo x esta conectado GPIO 27
         aux1 = adc_read() + aux1;
         sleep_ms(5);
     }
     posicoesjoy[0] = aux1/100; //Média da posição inicial de x
     posicoesjoy[3] = aux2/100; //Média da posição inicial de y
     aux1 = aux2 = 0;
     
     som_buz(1*KHz, 200);
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Segure o Joy", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Todo a direita", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Espere", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao);  
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Calibrando", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Segure firme", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Por favor", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao); 
     for(int i = 0; i<200;i++) //Coleta 200 amostras da pos X (1segundo de amostra)
     {
         adc_select_input(1); //Seleciona o canal em que o eixo x esta conectado GPIO 27
         aux1 = adc_read() + aux1;
         sleep_ms(5);
     }
     aux1 = aux1/200;
     if(aux1>posicoesjoy[0])
         posicoesjoy[1] = aux1;
     else if(aux1 < posicoesjoy[0])
         posicoesjoy[2] = aux1;
     aux1 = 0;
     
     som_buz(1*KHz, 200);
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Segure o Joy", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Todo a esquerda", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Espere", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao);   
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Calibrando", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Segure firme", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Por favor", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao); 
     for(int i = 0; i<200;i++) //Coleta 200 amostras da pos X (1segundo de amostra)
     {
         adc_select_input(1); //Seleciona o canal em que o eixo x esta conectado GPIO 27
         aux1 = adc_read() + aux1;
         sleep_ms(5);
     }
     aux1 = aux1/200;
     if(aux1>posicoesjoy[0])
         posicoesjoy[1] = aux1;
     else if(aux1 < posicoesjoy[0])
         posicoesjoy[2] = aux1;
     aux1 = 0;
     
     som_buz(1*KHz, 200);
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Segure o Joy", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Todo para cima", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Espere", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao);    
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Calibrando", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Segure firme", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Por favor", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao); 
     for(int i = 0; i<200;i++) //Coleta 200 amostras da pos y (1segundo de amostra)
     {
         adc_select_input(0); //Seleciona o canal em que o eixo y esta conectado GPIO 26
         aux1 = adc_read() + aux1;
         sleep_ms(5);
     }
     aux1 = aux1/200;
     if(aux1>posicoesjoy[3])
         posicoesjoy[4] = aux1;
     else if(aux1 < posicoesjoy[0])
         posicoesjoy[5] = aux1;
     aux1 = 0;
     
     som_buz(1*KHz, 200);
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Segure o Joy", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Todo pra baixo", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Espere", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao);    
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "Calibrando", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Segure firme", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Por favor", 8, 48); // Desenha uma string   
     ssd1306_send_data(ssd); // Atualiza o display
     sleep_ms(delay_padrao); 
     for(int i = 0; i<200;i++) //Coleta 200 amostras da pos y (1segundo de amostra)
     {
         adc_select_input(0); //Seleciona o canal em que o eixo y esta conectado GPIO 26
         aux1 = adc_read() + aux1;
         sleep_ms(5);
     }
     aux1 = aux1/200;
     if(aux1>posicoesjoy[3])
         posicoesjoy[4] = aux1;
     else if(aux1 < posicoesjoy[0])
         posicoesjoy[5] = aux1;
     aux1 = 0;
 
     
     gpio_put(LED_G, 1);
     
     som_buz(1*KHz, 200);
     gpio_put(LED_G, 0);
     sleep_ms(200);
     gpio_put(LED_G, 1);
     
     som_buz(1*KHz, 200);
     gpio_put(LED_G, 0);
     sleep_ms(200);
     ssd1306_fill(ssd, !cor); // Limpa o display
     ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
     ssd1306_draw_string(ssd, "O seu modulo", 8, 10); // Desenha uma string
     ssd1306_draw_string(ssd, "Esta pronto", 8, 30); // Desenha uma string
     ssd1306_draw_string(ssd, "Para ser usado.", 8, 48); // Desenha uma string      
     ssd1306_send_data(ssd); // Atualiza o display
     gpio_put(LED_G, 1);
     sleep_ms(delay_padrao);
 } 