/*

Task: PIR Sensor Integration
Objective: To evaluate knowledge of sensor integration and event handling.
Instructions:
1. Connect the PIR sensor to the ESP32 using the jumper wires.
2. Implement a multitasking solution using FreeRTOS tasks and semaphores to detect motion events triggered by the PIR sensor.
          Create two tasks:
              Task 1: PIR Sensor Task:
                 1. Continuously monitor the PIR sensor's output using GPIO interrupts.
                 2. Upon motion detection, set a semaphore to indicate the event.
              Task 2: LED Control Task:
                 1. Wait for the semaphore indicating motion detection.
                 2. Toggle an LED connected to another GPIO pin to indicate the event.
4. Implement a delay to ignore subsequent motion events for a certain period after the initial detection.
5. Ensure proper initialization and configuration of the interrupt for the PIR sensor.
6. Implement any necessary debouncing or filtering mechanisms to handle false triggers.
7. You may change the LED so to fade from low to high and high to low for 5 times (optional)

*/



#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include  "driver/gpio.h"
#include "arduino_fun.h"
#include "driver/ledc.h"
#include "esp_err.h"


#define switchpin 26
#define LED 25
QueueHandle_t intreptqueue;

void setpwmpin(int pin)
{
    ledc_timer_config_t timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_10_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = 5000,
    .clk_cfg = LEDC_APB_CLK

   }; 

ledc_timer_config(&timer);
ledc_channel_config_t channel = {
.gpio_num = pin,
.speed_mode = LEDC_LOW_SPEED_MODE,
.channel = LEDC_CHANNEL_0,
.timer_sel = LEDC_TIMER_0, 
.duty = 0,
.hpoint = 0
};
ledc_channel_config(&channel);
} 
 void led_control(){ 

    for(int j = 1;j<=5;j++)
    {

        ESP_LOGI("LOG","LED fade count = %d \n",j);
        for(int i = 0 ; i < 1024; i+=20)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
        for(int i = 1023 ; i >= 0; i-=20)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
    }
}


static void IRAM_ATTR gpio_isr_handler(void *args) //Intrrept Function
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

            gpio_isr_handler_remove(switchpin);

            do
            {
                vTaskDelay(20/portTICK_PERIOD_MS);
            } while (gpio_get_level(switchpin)==1); // DEBOUNCING
            

            
            ESP_LOGI("log","motion detected Count = %d\n",count++);
        led_control();

        gpio_isr_handler_add(switchpin,gpio_isr_handler,(void *) switchpin);

        }
        
        
        
    }
}

void app_main(void)
{

gpio_pad_select_gpio(switchpin);
gpio_set_direction(switchpin, GPIO_MODE_INPUT);
gpio_pulldown_en(switchpin);
gpio_pullup_dis(switchpin);
gpio_set_intr_type(switchpin,GPIO_INTR_POSEDGE); // POSITIVE EDGE TRIGGERED INTRREPT ADDED

intreptqueue = xQueueCreate(10,sizeof(int));

xTaskCreate(motiondetected," motion detected",2040,NULL,1,NULL);

gpio_install_isr_service(0);
gpio_isr_handler_add(switchpin,gpio_isr_handler,(void *) switchpin);

}
