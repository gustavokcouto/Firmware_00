#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "GPIO.h"
#include "Pwm.h"
#include "Encoder.h"
#include "TimerTime.h"
#include "Motor.h"

uint32_t TimingDelay;

void Delay (uint32_t nTime);

void TimingDelay_Decrement(void);

void SysTick_Handler(void);
uint32_t position;
int main(void)
{
  Pwm M0_B_H(GPIOE, GPIO_Pin_14, TIM1, GPIO_PinSource14, GPIO_AF_TIM1, (uint8_t) 4);
  Pwm M0_A_H(GPIOA, GPIO_Pin_8, TIM1, GPIO_PinSource8, GPIO_AF_TIM1, 1);
  GPIO M0_A_L(GPIOE, GPIO_Pin_0);
  GPIO M0_B_L(GPIOE, GPIO_Pin_1);
  //M0_A_L.Set();
  //M0_B_H.set_DutyCycle(300);
  Encoder M0_Enc(GPIOA, GPIOB, GPIO_Pin_15, GPIO_Pin_3, TIM2, GPIO_PinSource15, GPIO_PinSource3, GPIO_AF_TIM2);
  Motor M0(&M0_A_H, &M0_A_L, &M0_B_H, &M0_B_L, &M0_Enc);
  M0.Answer(-600);
  while (1)
  {
	//  M0.Control_Pos(300);
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
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
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
