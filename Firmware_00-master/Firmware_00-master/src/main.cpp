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
  Delay(10);
  Pwm M0_A_H(MAH_Port[0], MAH_Pin[0], MAH_Tim[0], MAH_Af_Pin[0], MAH_Af[0], MAH_Ch[0], MAH_nState[0]);
  GPIO M0_A_L(MAL_Port[0], MAL_Pin[0]);
  Pwm M0_B_H(MBH_Port[0], MBH_Pin[0], MBH_Tim[0], MBH_Af_Pin[0], MBH_Af[0], MBH_Ch[0], MBH_nState[0]);
  GPIO M0_B_L(MBL_Port[0], MBL_Pin[0]);
  Encoder M0_Enc(M_EncA_Port[0], M_EncB_Port[0], M_EncA_Pin[0], M_EncB_Pin[0], M_Enc_Tim[0], M_EncA_Af_Pin[0], M_EncB_Af_Pin[0], M_Enc_Af[0]);
  Motor M0(&M0_A_H, &M0_A_L, &M0_B_H, &M0_B_L, &M0_Enc);
  Delay(100);
  M0.Answer(-400);
  while (1)
  {

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
