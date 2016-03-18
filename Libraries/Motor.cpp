/*
 * Motor.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: lenovoi7
 */
#include "Motor.h"

Motor::Motor(Pwm *A_High,
		GPIO *A_Low,
		Pwm *B_High,
		GPIO *B_Low,
		Encoder *Enc)
{
	Motor_A_High = A_High;
	Motor_A_Low = A_Low;
	Motor_B_High = B_High;
	Motor_B_Low = B_Low;
	Motor_Enc = Enc;
}

void Motor::Control_Pos(uint32_t hold_position){
	uint32_t position;
	int16_t answer;
	position = Motor_Enc->position();
	answer = this->Pos_Calc_Answer(position, hold_position);
	this->Answer(answer);
	return;
};
void Motor::Control_Speed(int16_t hold_speed){

};

void Motor::Answer(int16_t answer)
{
	if (answer > 0)
	{
		if (answer>600)
		{
			answer=600;
		}
		Motor_A_Low->Reset();
		Motor_B_High->set_DutyCycle(0);
		Motor_A_High->set_DutyCycle(answer);
		Motor_B_Low->Set();
	}
	else
	{
		answer=-answer;
		if(answer>600)
		{
			answer=600;
		}
		Motor_B_Low->Reset();
		Motor_A_High->set_DutyCycle(0);
		Motor_B_High->set_DutyCycle(answer);
		Motor_A_Low->Set();
	}
	return;
}
int16_t Motor::Pos_Calc_Answer(uint32_t position, uint32_t hold_position)
{
	int16_t integral;
	int16_t error;
	int16_t derivative;
	int i;
//verde oliva
	error = (int16_t) (position - hold_position);
	for(i=0; i<19; i++){
		Pos_Last_Error[i]=Pos_Last_Error[i+1];
	}
	Pos_Last_Error[19] = error;
	integral=0;
	derivative=Pos_Last_Error[19]-Pos_Last_Error[18];

	for(i=0; i<20; i++){
		integral = integral+Pos_Last_Error[i];
	}
	if (integral > 600/0.18) integral = 600/0.18;
	return (int16_t) ((error)*0.81+(integral)*0.18 - derivative*2.25);
	//Kp = 0.81, Ki = 0.36, Kd = 2.25
}
