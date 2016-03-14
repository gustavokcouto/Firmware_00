/*
 * TimerTime.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: lenovoi7
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "TimerTime.h"

Timer_Time::Timer_Time(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	TIM_DeInit(TIM6);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_ClockDivision=1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler=40;
	TIM_TimeBaseStructure.TIM_Period=1000;
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);

	//TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_ARRPreloadConfig(TIM6, ENABLE);

	TIM_Cmd(TIM6, ENABLE);
};
uint32_t Timer_Time::time_elapsed(){
	//uint32_t time_elapsed1;
	uint32_t atual_time = TIM_GetCounter(TIM6);
	//TIM_SetCounter(TIM6, (uint32_t) 0);
	//time_elapsed1 = atual_time - this->last_time;
	//this->last_time = atual_time;
	return atual_time;
};
