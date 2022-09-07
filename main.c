/******************************************************************************
 * Project: On-demand Traffic light control for Udacity(FWD)
 * File Name: main.c
 * Description: types for AVR
 * Created on: Aug 18, 2022
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/
#include "Application/app.h"

int main() {

	APP_Init();

	//APP_Test();

	while(1){
		APP_start();
	}

	return 0;
}


/* User story 1:
 * while the cars green light is ON and pedestrian red light is ON,
 * I will make a short press on the crosswalk button
 * Result:
 * I will wait for the yellow lights to blink for five seconds,
 * then the cars red light is ON and pededstrian green light is ON for five seconds, so that I can cross the street */


/* User story 2:
 * while the cars yellow light is blinking and pedestrian red light is ON,
 * I will make a short press on the crosswalk button,
 * Result:
 * I will wait for all yellow lights to blink for five seconds,
 * then the cars red light is ON and pededstrian green light is ON for five seconds, so that I can cross the street */


/* User story 3:
 * while the cars red light is ON and pedestrian green light is ON,
 * I will make a short press on the crosswalk button,
 * Result:
 * I expect nothing to be done */


/* User story 4:
 * As a pedestrian when I made a long press on the crosswalk button,
 * Result:
 * I expect nothing to be done */


/* User story 5:
 * As a pedestrian when I made a double press on the crosswalk button,
 * Result:
 * I expect that the first press will do the action and nothing to be done after the second press */


