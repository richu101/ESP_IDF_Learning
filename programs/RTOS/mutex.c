#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


xSemaphoreHandle mutexbus; 

void writetobus(char *params)
{

    printf(" %s written to the bus\n",params);

}
void temperature(void *params)
{
    while(1)
    {
        printf("Temperature task is running\n");

        if(xSemaphoreTake(mutexbus, 1000/portTICK_PERIOD_MS))
        {
        writetobus("Temperature 22 0C");
        xSemaphoreGive(mutexbus);
        }
        else printf("Temperature reading timeout\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    }
}
void humidity(void *params)
{
    while(1)
    {
        printf("Humidity task is running\n");
        if(xSemaphoreTake(mutexbus, 1000/portTICK_PERIOD_MS))
        {
        writetobus("Humidity 50 persent");
        xSemaphoreGive(mutexbus);
        }
        else printf("Humidity reading Timeout\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
void app_main(void)
{

mutexbus = xSemaphoreCreateMutex();
xTaskCreate(&temperature,"Temperature Reading",2048,NULL,2,NULL);
xTaskCreate(&humidity,"Humidity reading",2048,NULL,2,NULL); 

}
