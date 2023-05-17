#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include  "driver/gpio.h"

#include "arduino_fun.h"

#define PIR 26
#define LED 25

void app_main(void)
{

pinMode(PIR,input_pulldown);
pinMode(LED,output);
while(1)
{

int level = gpio_get_level(PIR);
if(level)
{
gpio_set_level(LED,(uint32_t) level);
delay(5000);
}
gpio_set_level(LED,(uint32_t) level);
delay(1);

}

}