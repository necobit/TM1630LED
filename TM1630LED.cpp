#include "TM1630LED.h"
#include "arduino.h"

TM1630LED::TM1630LED(uint8_t DIO, uint8_t CLK, uint8_t STB)
: DIOPin(DIO), CLKPin(CLK), STBPin(STB)
{
  pinMode(DIOPin,OUTPUT);
  pinMode(CLKPin,OUTPUT);
  pinMode(STBPin,OUTPUT);
}

void TM1630LED::Begin(void)
{
  digitalWrite(STBPin,HIGH);
  digitalWrite(DIOPin,LOW);
  digitalWrite(CLKPin,LOW);
}

void TM1630LED::Init(void)
{
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,MODE);
  digitalWrite(STBPin, HIGH);

  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,DSET2);
  digitalWrite(STBPin, HIGH);

  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,ADRS);
  for(uint8_t i=0;i<14;i++){
    shiftOut(DIOPin,CLKPin,LSBFIRST,0b00000000);
  }
  digitalWrite(STBPin, HIGH);

  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,DISP);
  digitalWrite(STBPin, HIGH);
}

void TM1630LED::Disp(uint16_t num)
{
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,MODE);
  digitalWrite(STBPin, HIGH);

  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,DSET1);
  digitalWrite(STBPin, HIGH);
   
  //一桁目
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,ADRS);
  shiftOut(DIOPin,CLKPin,LSBFIRST,d[num/1000]);
  digitalWrite(STBPin, HIGH);
  //二桁目
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,ADRS|2);
  shiftOut(DIOPin,CLKPin,LSBFIRST,d[(num%1000)/100]);
  digitalWrite(STBPin, HIGH);
  //三桁目
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,ADRS|4);
  shiftOut(DIOPin,CLKPin,LSBFIRST,d[((num%1000)%100/10)]);
  digitalWrite(STBPin, HIGH);
  //四桁目
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,ADRS|6);
  shiftOut(DIOPin,CLKPin,LSBFIRST,d[((num%1000)%100%10)]);
  digitalWrite(STBPin, HIGH);
  
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin,CLKPin,LSBFIRST,DISP);
  digitalWrite(STBPin, HIGH);
}
