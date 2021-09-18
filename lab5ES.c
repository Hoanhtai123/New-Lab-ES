#include <stdio.h>
#include <time.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include<freertos/timers.h>

int time1 = 10;
int time2 = 5;
xTimerHandle  twosec_timer = NULL;
xTimerHandle  thrsec_timer = NULL;
void task (xTimerHandle  pxTimer)
{
    int timer = (int) pvTimerGetTimerID( pxTimer );
    if (timer == 1)
    {
        static int count1 = 0;
        if (count1 < time1)
        {
            printf("Ahihi at %d ms\n",(int) clock());
            xTimerReset(two_second_timer,0);
            count1++;
        }
    }
    else 
    {
        static int count2 = 0;
        if (count2 < time2)
        {
            printf("hello world at %d ms\n",(int) clock());
            xTimerReset(three_second_timer,0);
            count2++;
        }
    }
}
void app_main(void)
{
    twosec_timer = xTimerCreate("Hello",300,pdFALSE,(void*)1,task);
    thrsec_timer = xTimerCreate("World",400,pdFALSE,(void*)2,task);
    xTimerStart(twosec_timer,0);
    xTimerStart(thrsec_timer,0);
}