#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include  "driver/gpio.h"


#define switch 26

QueueHandle_t intreptqueue;

static void IRAM_ATTR gpio_isr_handler(void *args)
{
    int pin = (int *)args;
    xQueueSendFromISR(intreptqueue,&pin,NULL); 
}
void motiondetected(void *args)
{ 
    int PinNumber;
    while(1)
    {
        int pin ,count = 0;
        if(xQueueReceive(intreptqueue,&pin,portMAX_DELAY))
        {
            PinNumber = pin;
        }
        printf("motion detected - Count = %d\n",count++);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void app_main(void)
{

gpio_set_direction(switch, GPIO_MODE_INPUT);
gpio_set_intr_type(switch,GPIO_INTR_POSEDGE);
gpio_install_isr_service(0);
gpio_isr_handler_add(switch,gpio_isr_handler,(void *) switch);
intreptqueue = xQueueCreate(10,sizeof(int));


}