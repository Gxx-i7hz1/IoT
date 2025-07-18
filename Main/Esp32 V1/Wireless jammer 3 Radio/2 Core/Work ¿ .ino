//  --Library:
//    |Select board
//    |RF24.h
//  --Setup (Nrf|Esp) (1 & Gnd // 2 & 3.3v):
//    |5;6;7 connect to:
//       |18;23;19 |vspi|1;3|
//       |14;13;12 |hspi|2|

//Pin Radio
#define RF1_3 16
#define RF1_4 15
#define RF2_3 22
#define RF2_4 21
#define RF3_3 26
#define RF3_4 25
//Mode: |15:Wifi|81:Bluetooth|126:Drone|
#define RF1 81
#define RF2 81
#define RF3 81

#define Led_pin 2
#include "RF24.h"
#include <SPI.h>
SPIClass *vspi = nullptr;
SPIClass *hspi = nullptr;
RF24 radio1(RF1_3, RF1_4, 16000000);
RF24 radio2(RF2_3, RF2_4, 16000000);
RF24 radio3(RF3_3, RF3_4 ,16000000);
void core1(void *pvParameters) {
  for (;;) {
    radio1.setChannel(random(RF1));
    radio3.setChannel(random(RF3));
    vTaskDelay(1);}}
void core2(void *pvParameters) {
  for (;;) {
    radio2.setChannel(random(RF2));
    vTaskDelay(1);}}
void radioSetup() {
  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);
  vspi->begin();
  hspi->begin();
  if (radio1.begin(vspi)) {
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setDataRate(RF24_2MBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.startConstCarrier(RF24_PA_MAX, 0);
    digitalWrite(Led_pin, HIGH);
    delay(100);
    digitalWrite(Led_pin, LOW);
    delay(100);}
  if (radio2.begin(hspi)) {
    radio2.setAutoAck(false);
    radio2.stopListening();
    radio2.setRetries(0, 0);
    radio2.setDataRate(RF24_2MBPS);
    radio2.setCRCLength(RF24_CRC_DISABLED);
    radio2.startConstCarrier(RF24_PA_MAX, 0);
    digitalWrite(Led_pin, HIGH);
    delay(100);
    digitalWrite(Led_pin, LOW);
    delay(100);}
  if (radio3.begin(vspi)) {
    radio3.setAutoAck(false);
    radio3.stopListening();
    radio3.setRetries(0, 0);
    radio3.setDataRate(RF24_2MBPS);
    radio3.setCRCLength(RF24_CRC_DISABLED);
    radio3.startConstCarrier(RF24_PA_MAX, 0);
    digitalWrite(Led_pin, HIGH);}}
void setup() {
  pinMode(Led_pin, OUTPUT);
  radioSetup();
  xTaskCreatePinnedToCore(core1,"T1",2048,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(core2,"T2",2048,NULL,1,NULL,1);}
void loop() {}
