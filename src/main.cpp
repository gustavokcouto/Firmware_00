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
int main(void)
{
  int16_t i = -1000;
  SysTick_Config(SystemCoreClock / 1000);
  Pwm M2_A_H(MAH_Port[2], MAH_Pin[2], MAH_Tim[2], MAH_Af_Pin[2], MAH_Af[2], MAH_Ch[2]);
  GPIO M2_A_L(MAL_Port[2], MAL_Pin[2]);
  Pwm M2_B_H(MBH_Port[2], MBH_Pin[2], MBH_Tim[2], MBH_Af_Pin[2], MBH_Af[2], MBH_Ch[2]);
  GPIO M2_B_L(MBL_Port[2], MBL_Pin[2]);
  Encoder M2_Enc(M_EncA_Port[2], M_EncB_Port[2], M_EncA_Pin[2], M_EncB_Pin[2], M_Enc_Tim[2], M_EncA_Af_Pin[2], M_EncB_Af_Pin[2], M_Enc_Af[2]);
  Motor M2(&M2_A_H, &M2_A_L, &M2_B_H, &M2_B_L, &M2_Enc);
  Delay(100);
  //M2.Control_Pos(2500);
  //M2.Answer((int16_t)600);
  //M2_B_H.set_DutyCycle(600);
  //M2_A_L.Set();
  //M2_A_H.set_DutyCycle(0);
  //M2_B_L.Reset();
  M2.Answer(-400);
  while (1)
  {
	  M2.Control_Pos(2000);
	  //Delay(10);
	  //i = i+10;
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
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}
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
