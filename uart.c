#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "displayUart/ssd1306.h"
#include "pixel/Ppixel.h"
#include "definidos/definido.h"


ssd1306_t display;
static alarm_id_t alarme_botao_a;
static alarm_id_t alarme_botao_b;

void iniciar_gpio();
int64_t apertar_botao_a(alarm_id_t id, void *user_data);
int64_t apertar_botao_b(alarm_id_t id, void *user_data);
static void debounce(uint gpio, uint32_t eventos);
void exibir_led_verde(bool status);
void exibir_led_azul(bool status);

void iniciar_gpio() {
    uint mascara_led = (0x01 << LED_R) | (0x01 << LED_V) | (0x01 << LED_B);
    gpio_init_mask(mascara_led);
    gpio_set_dir_out_masked(mascara_led);

    uint mascara_botao = (0x01 << BOTAO_A) | (0x01 << BOTAO_B);
    gpio_init_mask(mascara_botao);
    gpio_set_dir_in_masked(mascara_botao);
    gpio_pull_up(BOTAO_A);
    gpio_pull_up(BOTAO_B);

    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &debounce);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &debounce);
}

void iniciar_display() {
    i2c_init(i2c1, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);
    
    ssd1306_init(&display, LARGURA, ALTURA, false, 0x3C, i2c1);
    ssd1306_config(&display);
    ssd1306_send_data(&display);

    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);
}

int64_t apertar_botao_a(alarm_id_t id, void *user_data) {
    gpio_put(LED_V, !gpio_get(LED_V));
    exibir_led_verde(gpio_get(LED_V));
    return 0;
}

int64_t apertar_botao_b(alarm_id_t id, void *user_data) {
    gpio_put(LED_B, !gpio_get(LED_B));
    exibir_led_azul(gpio_get(LED_B));
    return 0;
}

static void debounce(uint gpio, uint32_t eventos) {
    if(gpio == BOTAO_A) {
        cancel_alarm(alarme_botao_a);
        if(eventos == GPIO_IRQ_EDGE_FALL) alarme_botao_a = add_alarm_in_ms(DEBOUNCE_MS, apertar_botao_a, NULL, false);
    } else if(gpio == BOTAO_B){
        cancel_alarm(alarme_botao_b);
        if(eventos == GPIO_IRQ_EDGE_FALL) alarme_botao_b = add_alarm_in_ms(DEBOUNCE_MS, apertar_botao_b, NULL, false);
    }
}

void exibir_led_verde(bool status) {
    printf(status ? "LED VERDE: LIGADO\n" : "LED VERDE: DESLIGADO\n");
    ssd1306_draw_string(&display, status ? "LED VERDE: LIGADO" : "LED VERDE: DESLIGADO", 8, 30);
    ssd1306_send_data(&display);
}

void exibir_led_azul(bool status) {
    printf(status ? "LED AZUL : LIGADO\n" : "LED AZUL : DESLIGADO\n");
    ssd1306_draw_string(&display, status ? "LED AZUL : LIGADO" : "LED AZUL : DESLIGADO", 8, 40);
    ssd1306_send_data(&display);
}

int main() {
    stdio_init_all();
    iniciar_gpio();
    init_neopixel();
    iniciar_display();

    printf("UART conectada com sucesso.\nCaractere Recebido:\n");

    bool ledVerde = gpio_get(LED_V);
    bool ledAzul = gpio_get(LED_B);

    ssd1306_draw_string(&display, "UART OK", 8, 10);
    ssd1306_draw_string(&display, "CHAR LIDO ", 8, 20);
    ssd1306_draw_string(&display, "LED VERDE ", 8, 30);
    ssd1306_draw_string(&display, "LED AZUL ", 8, 40);
    ssd1306_send_data(&display);

    exibir_led_verde(ledVerde);
    exibir_led_azul(ledAzul);

    while (true) {
        int c = stdio_getchar_timeout_us(10);
        if (c != PICO_ERROR_TIMEOUT) {
            printf("Caractere Recebido: %c\n", c);
            ssd1306_draw_char(&display, (char)c, 12*8, 20);
            ssd1306_send_data(&display);
            if(c >= '0' && c <= '9') {
                renderMatrix(alphabet[c - '0']);
            } else {
                renderMatrix(OFF);
            }
        }

        if(ledVerde != gpio_get(LED_V)) {
            ledVerde = gpio_get(LED_V);
            exibir_led_verde(ledVerde);
        }
        if(ledAzul != gpio_get(LED_B)) {
            ledAzul = gpio_get(LED_B);
            exibir_led_azul(ledAzul);
        }

        sleep_ms(50);
    }
}
