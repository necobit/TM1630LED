/*
   TM1630サンプルスケッチは4桁7セグメント表示機専用です。

   Copyright (c) 2019 kurobeko

   TM1630ドライバ用のライブラリです。
   表示モード：5桁7セグメント（スケッチ上は4桁7セグメントです）
   表示輝度：2/16
   Begin()･･･通信開始前のDIO,CLK,STBの出力状態を定義
   Init()･･･ディスプレイのバッファをクリア
   Disp(uint16_t)･･･引数として表示したい数字を入れる
*/

#include <TM1630LED.h>
uint8_t DIOPin = 2;
uint8_t CLKPin = 3;
uint8_t STBPin = 4;

TM1630LED TM1630(DIOPin, CLKPin, STBPin);
void setup() {
  TM1630.Begin();
  TM1630.Init();

  //3桁目のドットを点灯
  digitalWrite(STBPin, LOW);
  shiftOut(DIOPin, CLKPin, LSBFIRST, ADRS | 5);
  shiftOut(DIOPin, CLKPin, LSBFIRST, 0b00100000);
  digitalWrite(STBPin, HIGH);
}

void loop() {
int msec = millis()/10 % 10000;
TM1630.Disp(msec);
delay(1);
}
