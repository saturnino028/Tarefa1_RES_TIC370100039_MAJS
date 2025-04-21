#include "main.h"

int main()
{
    //Definição de Variaveis
    ssd1306_t ssd; // Inicializa a estrutura do display
    bool cor = true; //Estado LEDs display
    uint16_t valores_ref_joy[6] = {2047,4095,0,2047,4095,0}; //Valores de ref. Joystick

    //Inicialização de hardware e software
    set_sys_clock_khz(1250000,false); //Cofigura o clock
    stdio_init_all();
    config_pins_gpio(); //Inicia os pinos GPIO
    init_matriz(); //Inicia a matriz de LEDs 5x5 WS2812
    config_i2c_display(&ssd); //Inicia o I2C para o diplay
    config_adc();

    printf("Sistema Iniciado.");
    som_buz(1*KHz, 200);

    desenhar_fig(open, brilho_matriz); //Matriz RGB sorrindo

    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(&ssd, "  EMBARCATECH", 5, 15); // Desenha uma string
    ssd1306_draw_string(&ssd, "RESTIC 37", 26, 29); // Desenha uma string  
    ssd1306_draw_string(&ssd, "  FASE 2", 26, 43); // Desenha uma string      
    ssd1306_send_data(&ssd); // Atualiza o display

    sleep_ms(3000);

    desenhar_fig(apagado, brilho_matriz);

    calibrar_joy(&ssd, valores_ref_joy); //Captura valores de referência do joystick

    //Ativação das interrupções   
    gpio_set_irq_enabled_with_callback(bot_A, GPIO_IRQ_EDGE_FALL, true, botoes_callback); //Interrupção botão A
    gpio_set_irq_enabled_with_callback(bot_B, GPIO_IRQ_EDGE_FALL, true, botoes_callback); //Interrupção botão B
    gpio_set_irq_enabled_with_callback(bot_joy, GPIO_IRQ_EDGE_FALL, true, botoes_callback); //Interrupção botão Joystick

    sleep_ms(2000);
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(&ssd, " Atvd Especial", 4, 15); // Desenha uma string
    ssd1306_draw_string(&ssd, "de Pascoa", 24, 29); // Desenha uma string     
    ssd1306_send_data(&ssd); // Atualiza o display

    sleep_ms(2000);    
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(&ssd, " MUITA COISA", 4, 15); // Desenha uma string
    ssd1306_draw_string(&ssd, "PODE ACONTECER", 6, 29); // Desenha uma string    
    ssd1306_draw_string(&ssd, "EM 7 DIAS", 29, 43); // Desenha uma string      
    ssd1306_send_data(&ssd); // Atualiza o display

    desenhar_fig(cruz_vermelha, brilho_matriz);
    sleep_ms(3000);
    ssd1306_draw_image(&ssd, fig_principal);
    sleep_ms(2000);

    while(1)
    {
        if(modo_gravacao_flag)
        {
            ssd1306_fill(&ssd, !cor); // Limpa o display
            ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
            ssd1306_draw_string(&ssd, " Modo Gravacao", 4, 30); // Desenha uma string
            som_buz(1*KHz, 1000);
            modo_gravacao();
        }
            
        if(!flag_botoes)
        {
            desenhar_fig(cruz_verde, brilho_matriz);
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 0);
            ssd1306_draw_image(&ssd, ramo);
            sleep_ms(2000);
    
            desenhar_fig(cruz_azul, brilho_matriz);
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 0);
            gpio_put(LED_B, 1);
            ssd1306_draw_image(&ssd, coroa);
            sleep_ms(2000);
    
            desenhar_fig(cruz_vermelha, brilho_matriz);
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 0);
            gpio_put(LED_B, 0);
            ssd1306_draw_image(&ssd, cruz_ssd);
            sleep_ms(2000);
    
            desenhar_fig(cruz_branca, brilho_matriz);
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 1);
            ssd1306_draw_image(&ssd, tumba);
            sleep_ms(2000);
        }
        if(flag_botoes)
        {
            desenhar_fig(apagado, brilho_matriz);
            ssd1306_fill(&ssd, !cor); // Limpa o display 
            ssd1306_send_data(&ssd); // Atualiza o display
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 0);
            gpio_put(LED_B, 0);
        }
    }
}
