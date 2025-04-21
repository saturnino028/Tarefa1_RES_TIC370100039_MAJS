/**
 * @brief arquivo cabeçalho das funções de configuração
 */
#ifndef CONFIG_H
#define CONFIG_H
/***********************  Includes ***********************/
#include <stdio.h>
#include "pinout.h"
#include "ssd1306.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "funcoes_gpio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

/***********************  Defines ***********************/

#define KHz         1000 //Define KHz
#define MHz         1000000 //Define MHz

/******************* Variáveis Globais *******************/

extern volatile uint16_t top_wrap; //Maior valor de wrap;
extern volatile bool erro_flag ; //Sinal vizual de erro

/******************* Protótipo Funções *******************/

void config_adc();
void config_i2c();
void config_pins_gpio();

void calibrar_joy(ssd1306_t *ssd, uint16_t posicoesjoy[6]);


#endif //CONFIG_H