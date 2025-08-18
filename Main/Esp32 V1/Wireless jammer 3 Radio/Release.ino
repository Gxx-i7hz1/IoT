//  --Library:
//    |Select board
//    |RF24.h
//  --Setup (Nrf|Esp) (1 & Gnd // 2 & 3.3v):
//    |pin 5;6;7 connect to (Esp):
//       |18;23;19
//       |14;13;12 (Note at line 26)

//Pin Radio
#define RF1_3 16
#define RF1_4 15
#define RF2_3 22
#define RF2_4 21
#define RF3_3 26
#define RF3_4 25
//Nrf channel:
#define Mode1 126
#define Mode2 126
#define Mode3 126

// Note: if you want to use 14;13;12 then declare the code below:
/*
#define MY_VSPI_SCK   14
#define MY_VSPI_MISO  12
#define MY_VSPI_MOSI  13
*/

#include "RF24.h"
#include <SPI.h>
SPIClass vspi(VSPI);
RF24 radio1(RF1_3, RF1_4, 16000000);
RF24 radio2(RF2_3, RF2_4, 16000000);
RF24 radio3(RF3_3, RF3_4 ,16000000);
void SAtk() {
  if (radio1.begin(&vspi)) {
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(RF24_PA_MAX, true);
    radio1.setDataRate(RF24_2MBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.startConstCarrier(RF24_PA_MAX, 45);}
    else {Serial.println("N1 couldn't start !!!");}
  if (radio2.begin(&vspi)) {
    radio2.setAutoAck(false);
    radio2.stopListening();
    radio2.setRetries(0, 0);
    radio2.setPALevel(RF24_PA_MAX, true);
    radio2.setDataRate(RF24_2MBPS);
    radio2.setCRCLength(RF24_CRC_DISABLED);
    radio2.startConstCarrier(RF24_PA_MAX, 45);}
    else {Serial.println("N2 couldn't start !!!");}
  if (radio3.begin(&vspi)) {
    radio3.setAutoAck(false);
    radio3.stopListening();
    radio3.setRetries(0, 0);
    radio3.setPALevel(RF24_PA_MAX, true);
    radio3.setDataRate(RF24_2MBPS);
    radio3.setCRCLength(RF24_CRC_DISABLED);
    radio3.startConstCarrier(RF24_PA_MAX, 45);}
    else {Serial.println("N3 couldn't start !!!");}}
void setup() {
  Serial.begin(115200);
  Serial.println("By Cio1N, Tiktok: urcio1");
  SAtk();}
void loop() {
  radio1.setChannel(random(Mode1));
  radio2.setChannel(random(Mode2));
  radio3.setChannel(random(Mode3));}