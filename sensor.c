/*
 * sensor.c
 *
 *  Created on: Nov 11, 2017
 *      Author: lenovo
 */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "hardwareinit.h"
#include "sensor.h"
#include "device.h"
#define counterTimeout 30
unsigned long tik=0;
void tikupdate()
{
	tik++;
}
uint8_t sensor1Detected(void){
	int hasil=0;
	int timeOut;
	if(HAL_GPIO_ReadPin(Sensor1_GPIO_Port,Sensor1_Pin)== GPIO_PIN_RESET){
		HAL_Delay(40);
		if(HAL_GPIO_ReadPin(Sensor1_GPIO_Port,Sensor1_Pin)==GPIO_PIN_RESET) {
			timeOut = tik;
			while(HAL_GPIO_ReadPin(Sensor1_GPIO_Port,Sensor1_Pin)==GPIO_PIN_RESET&&(tik-timeOut)<counterTimeout);
			if(tik-timeOut<counterTimeout)hasil=1; //kode normal
			else{ hasil=5; //kode error_
			}
		}
	}
	return(hasil);
}
uint8_t sensor2Detected(void){
	int hasil=0;
	int timeOut;
	if(HAL_GPIO_ReadPin(Sensor2_GPIO_Port,Sensor2_Pin)== GPIO_PIN_RESET){
		HAL_Delay(40);
		if(HAL_GPIO_ReadPin(Sensor2_GPIO_Port,Sensor2_Pin)==GPIO_PIN_RESET) {
			timeOut = tik;
			while(HAL_GPIO_ReadPin(Sensor2_GPIO_Port,Sensor2_Pin)==GPIO_PIN_RESET&&(tik-timeOut)<counterTimeout);
			if(tik-timeOut<counterTimeout)hasil=1; //kode normal
			else{ hasil=5; //kode error_
			}
		}
	}
	return(hasil);
}uint8_t sensor3Detected(void){
	int hasil=0;
	int timeOut;
	if(HAL_GPIO_ReadPin(Sensor3_GPIO_Port,Sensor3_Pin)== GPIO_PIN_RESET){
		HAL_Delay(40);
		if(HAL_GPIO_ReadPin(Sensor3_GPIO_Port,Sensor3_Pin)==GPIO_PIN_RESET) {
			timeOut = tik;
			while(HAL_GPIO_ReadPin(Sensor3_GPIO_Port,Sensor3_Pin)==GPIO_PIN_RESET&&(tik-timeOut)<counterTimeout);
			if(tik-timeOut<counterTimeout)hasil=1; //kode normal
			else{ hasil=5; //kode error_
			}
		}
	}
	return(hasil);
}

uint8_t sensorStartStopDetected(){
	unsigned char hasil=0;

	if(!HAL_GPIO_ReadPin(Start_GPIO_Port, Start_Pin)){
		HAL_Delay(20);
		if(!HAL_GPIO_ReadPin(Start_GPIO_Port,Start_Pin)){
			while(!HAL_GPIO_ReadPin(Start_GPIO_Port,Start_Pin)){
				HAL_Delay(1);
			}
			hasil=1;
		}
	}
	return(hasil);
}
uint8_t sensorResetDetected(){
	unsigned char hasil=0;

	if(!HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)){
		HAL_Delay(20);
		if(!HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)){
			while(!HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)){
				HAL_Delay(1);
			}
			hasil=1;
		}
	}
	return(hasil);
}


