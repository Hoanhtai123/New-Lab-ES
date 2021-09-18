#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define LED_GPIO 15
#define BTN_GPIO 18

void AFunc() {
    int iVariableExample = 0;
    for (;;) {
        printf("Ho Anh Tai - 1810490 \n");
        vTaskDelay(100);
    }
    vTaskDelete(NULL);
}

void button_task(void* pvParameter)
{
    /* Configure the IOMUX register for pad LED_GPIO, BTN_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(LED_GPIO);
    gpio_pad_select_gpio(BTN_GPIO);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_GPIO, GPIO_PULLUP_ONLY);

    while (1) {
        if (gpio_get_level(BTN_GPIO) == 0) {
            gpio_set_level(LED_GPIO, 1);
        }
        else
            gpio_set_level(LED_GPIO, 0);
    }
}

void app_main()
{
    xTaskCreate(&button_task, "button_task", 1024, NULL, 0, NULL);
    xTaskCreate(&AFunc, "HAT", 1024, NULL, 0, NULL);
}
