// #include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "ws2812.pio.h"

#define WS2812_PIN 7
#define NUM_PIXELS 25
#define PIN_LED_RED 13
#define PIN_BUTTON_A 5
#define PIN_BUTTON_B 6
#define DEBOUNCE_TIME_MS 200

static volatile int contador = 0;
static volatile uint32_t last_time_A = 0;
static volatile uint32_t last_time_B = 0;
const float r = 1.0f, g = 1.0f, b = 1.0f; // Cor branca
PIO pio = pio0;
uint sm;

// Padrões dos números (0-9) na matriz 5x5
double desenho1[25] = {0.0, 0.0, 0.2, 0.0, 0.0,
                        0.0, 0.0, 0.2, 0.2, 0.0, 
                        0.0, 0.0, 0.2, 0.0, 0.0,
                        0.0, 0.0, 0.2, 0.0, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};

double desenho2[25] = {0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.0, 0.0, 
                        0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.0, 0.0, 0.2, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};

double desenho3[25] = {0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.0, 0.0, 
                        0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.0, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};

double desenho4[25] = {0.0, 0.2, 0.0, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.2, 0.0, 
                        0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.2, 0.0};

double desenho5[25] = {0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.0, 0.0, 0.2, 0.0, 
                        0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.0, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};

double desenho6[25] = {0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.0, 0.0, 0.2, 0.0, 
                        0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.2, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};


double desenho7[25] = { 0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 0.2, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.2, 0.0,
                        0.2, 0.0, 0.0, 0.0, 0.0};

double desenho8[25] = {0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.2, 0.0, 
                        0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.2, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};

double desenho9[25] = {0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.2, 0.0, 
                        0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.0, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};

double desenho0[25] = {0.0, 0.2, 0.2, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.2, 0.0, 
                        0.0, 0.2, 0.0, 0.2, 0.0,
                        0.0, 0.2, 0.0, 0.2, 0.0,
                        0.0, 0.2, 0.2, 0.2, 0.0};

// Adicione desenhos para 2-9 seguindo o mesmo padrão...

uint32_t matrix_rgb(double brilho, double r, double g, double b) {
    uint8_t R = (uint8_t)(r * brilho * 255);
    uint8_t G = (uint8_t)(g * brilho * 255);
    uint8_t B = (uint8_t)(b * brilho * 255);
    return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio1(double *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], r, g, b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void setup_ws2812() {
    if (!set_sys_clock_khz(128000, false)) {
        printf("Erro ao configurar o clock!\n");
        while(1);
    }
    uint offset = pio_add_program(pio, &ws2812_program);
    sm = pio_claim_unused_sm(pio, true);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);
}

void display_number(int number) {
    switch(number) {
        case 0: desenho_pio1(desenho0); break;
        case 1: desenho_pio1(desenho1); break;
        case 2: desenho_pio1(desenho2); break;
        case 3: desenho_pio1(desenho3); break;
        case 4: desenho_pio1(desenho4); break;
        case 5: desenho_pio1(desenho5); break;
        case 6: desenho_pio1(desenho6); break;
        case 7: desenho_pio1(desenho7); break;
        case 8: desenho_pio1(desenho8); break;
        case 9: desenho_pio1(desenho9); break;
        default: break;
    }
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (gpio == PIN_BUTTON_A) {
        if (current_time - last_time_A > DEBOUNCE_TIME_MS && contador < 9) {
            last_time_A = current_time;
            contador++;
            display_number(contador);
        }
    } else if (gpio == PIN_BUTTON_B) {
        if (current_time - last_time_B > DEBOUNCE_TIME_MS && contador > 0) {
            last_time_B = current_time;
            contador--;
            display_number(contador);
        }
    }
}

int main() {
    stdio_init_all();
    gpio_init(PIN_LED_RED);
    gpio_set_dir(PIN_LED_RED, GPIO_OUT);

    gpio_init(PIN_BUTTON_A);
    gpio_set_dir(PIN_BUTTON_A, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_A);

    gpio_init(PIN_BUTTON_B);
    gpio_set_dir(PIN_BUTTON_B, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_B);

    gpio_set_irq_enabled_with_callback(PIN_BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(PIN_BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    setup_ws2812();
    display_number(0);

    uint32_t last_toggle = 0;
    while (true) {
        uint32_t current_time = to_ms_since_boot(get_absolute_time());
        if (current_time - last_toggle >= 100) {
            gpio_put(PIN_LED_RED, !gpio_get(PIN_LED_RED));
            last_toggle = current_time;
        }
    }

    return 0;
}