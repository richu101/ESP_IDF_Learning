#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include  "driver/gpio.h"
#include "arduino_fun.h"
void app_main(void)
{

pinMode(2, input_pullup);
uint32_t status = 0;
int mode = 0;
while (true)
{
status = !status;
printf("Hello world!\n");
gpio_set_level(2,status);
delay(100);
ESP_LOGE("TAG", "Error message!");
ESP_LOGW("TAG", "Warning message!");
ESP_LOGI("TAG", "Info message!");
ESP_LOGD("TAG", "Debug message!");
ESP_LOGV("TAG", "Verbose message!");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}

}