
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "arduino_fun.h"

void delay(uint32_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void pinMode(uint32_t pin, mode val)
{
    gpio_pad_select_gpio(pin);
    if(val == output)gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    else if(val == input)gpio_set_direction(pin, GPIO_MODE_INPUT);
    else if(val == input_pullup)
    {
        gpio_set_direction(pin, GPIO_MODE_INPUT);
        gpio_pullup_en(pin);
    }
    else if(val == input_pulldown)
    {
        gpio_set_direction(pin, GPIO_MODE_INPUT);
        gpio_pulldown_en(pin);
    }
    
    

}