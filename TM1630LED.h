#ifndef TM1630LED_H_
#define TM1630LED_H_
#include "arduino.h"

  const static uint8_t d[10]={0b01111110,0b00001100,0b10110110,0b10011110,0b11001100,0b11011011,0b11111010,0b01001110,0b11111110,0b11011110};
  const static uint8_t MODE=   0b00000000;//4桁7+1セグメント
  const static uint8_t DSET1=  0b01000100;//固定アドレス
  const static uint8_t DSET2=  0b01000000;//移動アドレス
  const static uint8_t ADRS=   0b11000000;//アドレス00H
  const static uint8_t DISP=   0b10001001;//表示設定：2/16


class TM1630LED
{
public:
  TM1630LED(uint8_t DIO, uint8_t CLK, uint8_t STB);

public:
  void Begin(void);
  void Init(void);
  void Disp(uint16_t num);

private:
  uint8_t DIOPin, CLKPin, STBPin;
};

#endif