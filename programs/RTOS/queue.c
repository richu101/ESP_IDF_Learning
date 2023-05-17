#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


xQueueHandle queue;

void listentobus(void *params)
{
    int count=0;
while (true)
{
    count++;
    printf(" received data from bus \n");
    long ok = xQueueSend(queue,&count,1000/portTICK_PERIOD_MS);
    if(ok)
    {
        printf("data sent to queue \n");
    }
    else
    {
        printf("Failed sent to queue \n");
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);

}


}
void task1(void *params)
{
    while(1)
    {
        int rxInt = 0;
        if(xQueueReceive(queue,&rxInt,5000/portTICK_PERIOD_MS))
        {
            printf("Data received from queue %d \n",rxInt);
        }
        else
        {
            printf("Failed to receive data from queue \n");
        }
        printf("Do something\n");
        
    
    }
}

void app_main(void)
{

queue = xQueueCreate(1,sizeof(int));
xTaskCreate(&listentobus,"Listen to data bus",2048,NULL,2,NULL);
xTaskCreate(&task1,"received task",2048,NULL,2,NULL); 

}
