/***
 * Demo program to use FreeRTOS SMP on Both Cores
 * Blink on Core 0 to GPIO 0
 * Blink on Core 1 to GPIO 15
 * Counter showing on GPIO 2 to 5, using Core 1
 * Instructions sent to Counter from Main Task on Core 0
 * Jon Durrant
 * 15-Aug-2022
 */


#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <math.h>
#include "hardware/structs/sio.h"

#include "BlinkAgent.h"
#include "CounterAgent.h"


//Standard Task priority
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

//LED PAD to use
#define LED_PAD					0
#define LED1_PAD				2
#define LED2_PAD				3
#define LED3_PAD				4
#define LED4_PAD				5
#define LED5_PAD			   15



/***
 * Main task to blink external LED
 * @param params - unused
 */
void mainTask(void *params){
	BlinkAgent blink(LED_PAD);
	BlinkAgent blink1(LED5_PAD);
	CounterAgent counter(LED1_PAD, LED2_PAD, LED3_PAD, LED4_PAD);


	printf("Main task started\n");

	blink.start("Blink 0", TASK_PRIORITY);
	blink1.start("Blink 1", TASK_PRIORITY);
	counter.start("Counter", TASK_PRIORITY);

	//Bind to CORE 1
	UBaseType_t coreMask = 0x2;
	vTaskCoreAffinitySet( blink1.getTask(), coreMask );
	vTaskCoreAffinitySet( counter.getTask(), coreMask );

	//Bind to CORE 0
	coreMask = 0x1;
	vTaskCoreAffinitySet( blink.getTask(), coreMask );


	while (true) { // Loop forever
		printf("Main on Core %ld\n",sio_hw->cpuid);

		uint8_t r = rand()&0xF;
		counter.on(r);
		vTaskDelay(3000);
	}
}




/***
 * Launch the tasks and scheduler
 */
void vLaunch( void) {

	//Start blink task
    TaskHandle_t task;
    xTaskCreate(mainTask, "MainThread", 500, NULL, TASK_PRIORITY, &task);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

/***
 * Main
 * @return
 */
int main( void )
{
	//Setup serial over USB and give a few seconds to settle before we start
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    //Start tasks and scheduler

    const char *rtos_name;
#if ( portSUPPORT_SMP == 1 )
    rtos_name = "FreeRTOS SMP";
#else
    rtos_name = "FreeRTOS";
#endif

#if ( portSUPPORT_SMP == 1 ) && ( configNUM_CORES == 2 )
    printf("%s on both cores:\n", rtos_name);
#else
    printf("Starting %s on core 0:\n", rtos_name);
#endif

    vLaunch();


    return 0;
}
