#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include  "driver/gpio.h"


#define switchpin 26

QueueHandle_t intreptqueue;

static void IRAM_ATTR gpio_isr_handler(void *args)
{
    int pin = (int *)args;
    xQueueSendFromISR(intreptqueue,&pin,NULL); 
}
void motiondetected(void *args)
{ 
    int PinNumber;
    int pin ,count = 0;
    while(1)
    {
        
        if(xQueueReceive(intreptqueue,&pin,portMAX_DELAY))
        {
            PinNumber = pin;
            // disable the intrrept for removing douncing
            gpio_isr_handler_remove(switchpin);
            // wait for 10ms

            //do work
            do
            {
                vTaskDelay(20/portTICK_PERIOD_MS);
            } while (gpio_get_level(switchpin)==1);
            

            printf("Pin %d is HIGH",PinNumber);

            // Enable intrrept
            gpio_isr_handler_add(switchpin,gpio_isr_handler,(void *) switchpin);

        }
        printf("motion detected - Count = %d\n",count++);
        
    }
}
void app_main(void)
{

gpio_pad_select_gpio(switchpin);
gpio_set_direction(switchpin, GPIO_MODE_INPUT);
gpio_pulldown_en(switchpin);
gpio_pullup_dis(switchpin);
gpio_set_intr_type(switchpin,GPIO_INTR_POSEDGE);

intreptqueue = xQueueCreate(10,sizeof(int));
xTaskCreate(motiondetected," motion detected",2040,NULL,1,NULL);

gpio_install_isr_service(0);
gpio_isr_handler_add(switchpin,gpio_isr_handler,(void *) switchpin);

}
