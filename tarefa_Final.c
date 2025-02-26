#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "lib/ssd1306.h"
#include "lib/font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define JOYSTICK_Y_PIN 27
#define JOYSTICK_X_PIN 26
#define Botao_A 5
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define BUZZER 10  // Novo pino do buzzer

void configurar_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice, 4095);
    pwm_set_chan_level(slice, pwm_gpio_to_channel(pin), 0);
    pwm_set_enabled(slice, true);
}

int main() {
    stdio_init_all();

    // Inicializa pinos
    gpio_init(Botao_A);
    gpio_set_dir(Botao_A, GPIO_IN);
    gpio_pull_up(Botao_A);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, 0);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0);  // Buzzer desligado inicialmente

    // Inicializa I2C e display OLED
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    // Inicializa ADC
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);


    uint16_t adc_value_x, adc_value_y;
    bool alerta_gas = false;

    while (true) {
        // Leitura do joystick
        adc_select_input(0);
        adc_value_x = adc_read();
        adc_select_input(1);
        adc_value_y = adc_read();

        // Lógica de alerta de gás
        if (adc_value_x > 4000 || adc_value_x < 100 || adc_value_y > 4000 || adc_value_y < 100) {
            alerta_gas = true;
            gpio_put(BUZZER, 1);  // Ativa o buzzer
            gpio_put(LED_VERDE, 0); // Desativa LED Verde
            gpio_put(LED_VERMELHO, 1); // Ativa LED Vermelho
        } else {
            alerta_gas = false;
            gpio_put(BUZZER, 0);  // Desativa o buzzer
            gpio_put(LED_VERMELHO, 0); // Desativa LED Vermelho
            gpio_put(LED_VERDE, 1); //Ativa LED Verde
        }

        // Atualiza o display
        ssd1306_fill(&ssd, false);

        // Mostra alerta ou mensagem padrão
        if (alerta_gas) {
            ssd1306_draw_string(&ssd, "ALERTA: GAS DETECTADO", 10, 10);
        } else {
            ssd1306_draw_string(&ssd, "RECEBENDO DADOS", 10, 10);
        }

        ssd1306_send_data(&ssd);
        sleep_ms(50);
    }
}
