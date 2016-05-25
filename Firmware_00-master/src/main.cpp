#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "GPIO.h"
#include "Pwm.h"
#include "Encoder.h"
#include "TimerTime.h"
#include "Motor.h"
#include "pins.h"

uint32_t TimingDelay;

void Delay (uint32_t nTime);

void TimingDelay_Decrement(void);
extern "C" {
void SysTick_Handler(void);
}
uint32_t position;

void calc_speed_matrix(int8_t v_r, int8_t v_t, int8_t w, int16_t *v);

Pwm M3_A_H(MAH_Port[3], MAH_Pin[3], MAH_Tim[3], MAH_Af_Pin[3], MAH_Af[3], MAH_Ch[3], MAH_nState[3]);
GPIO M3_A_L(MAL_Port[3], MAL_Pin[3]);
Pwm M3_B_H(MBH_Port[3], MBH_Pin[3], MBH_Tim[3], MBH_Af_Pin[3], MBH_Af[3], MBH_Ch[3], MBH_nState[3]);
GPIO M3_B_L(MBL_Port[3], MBL_Pin[3]);
Encoder M3_Enc(M_EncA_Port[3], M_EncB_Port[3], M_EncA_Pin[3], M_EncB_Pin[3], M_Enc_Tim[3], M_EncA_Af_Pin[3], M_EncB_Af_Pin[3], M_Enc_Af[3]);
Timer_Time Tempo; //valores ja setupados pro timer_time
Motor M3(&M3_A_H, &M3_A_L, &M3_B_H, &M3_B_L, &M3_Enc, &Tempo);

int main(void)
{
  SysTick_Config(SystemCoreClock / 1000);
  Delay(10);
/*  Pwm M3_A_H(MAH_Port[3], MAH_Pin[3], MAH_Tim[3], MAH_Af_Pin[3], MAH_Af[3], MAH_Ch[3], MAH_nState[3]);
  GPIO M3_A_L(MAL_Port[3], MAL_Pin[3]);
  Pwm M3_B_H(MBH_Port[3], MBH_Pin[3], MBH_Tim[3], MBH_Af_Pin[3], MBH_Af[3], MBH_Ch[3], MBH_nState[3]);
  GPIO M3_B_L(MBL_Port[3], MBL_Pin[3]);
  Encoder M3_Enc(M_EncA_Port[3], M_EncB_Port[3], M_EncA_Pin[3], M_EncB_Pin[3], M_Enc_Tim[3], M_EncA_Af_Pin[3], M_EncB_Af_Pin[3], M_Enc_Af[3]);
  Timer_Time Tempo; //valores ja setupados pro timer_time
  Motor M3(&M3_A_H, &M3_A_L, &M3_B_H, &M3_B_L, &M3_Enc, &Tempo);
  Delay(10);*/


  while (1)
  {
	  //M3.Control_Pos(300);
	  //M3.Control_Speed(v[3]);
	  //Delay(10);

  }
}


void Delay( uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0); //gustavo
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}
extern "C" {
void TIM6_DAC_IRQHandler(){
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)){
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		M3.Control_Speed(600);
	}
}
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}
}

void calc_speed_matrix(int8_t v_r, int8_t v_t, int8_t w, int16_t *v){
	uint8_t R = 14; //TODO valor temporario

	v[0] = -v_r*0.5 + v_t*0.86603 + w*R;
	v[1] = -v_r*0.5 - v_t*0.86603 + w*R;
	v[2] = v_r*0.70711 - v_t*0.70711 + w*R;
	v[3] = v_r*0.70711 + v_t*0.70711 + w*R;
	return;
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
