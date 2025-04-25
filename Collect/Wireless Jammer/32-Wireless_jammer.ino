//  --Library:
//    |Select board
//    |RF24.h
//  --Connect:
//    |TX0 & RX0 // RX0 & TX0
//    |Hold the Boot button, click EN to enter Download mode.
//  --Setup (Nrf|Esp) (1 & Gnd // 2 & 3.3v):
//    |RF_1:
//       |3 & 16
//       |4 & 15
//       |5 & 14
//       |6 & 13
//       |7 & 12
//    |RF_2:
//       |3 & 22
//       |4 & 21
//       |5 & 18
//       |6 & 23
//       |7 & 19

#include "RF24.h"
#include <SPI.h>
SPIClass *sp = nullptr;
SPIClass *hp = nullptr;
RF24 radio(16, 15, 16000000);
RF24 radio1(22, 21, 16000000);
unsigned int flag = 0;
unsigned int flagv = 0;
int ch = 45;
int ch1 = 45;
void two() {
  if (flagv == 0) {
    ch1 += 4;
  } else {
    ch1 -= 4;
  }
  if (flag == 0) {
    ch += 2;
  } else {
    ch -= 2;
  }
  if ((ch1 > 79) && (flagv == 0)) {
    flagv = 1;
  } else if ((ch1 < 2) && (flagv == 1)) {
    flagv = 0;
  }
  if ((ch > 79) && (flag == 0)) {
    flag = 1;
  } else if ((ch < 2) && (flag == 1)) {
    flag = 0;
  }
  radio.setChannel(ch);
  radio1.setChannel(ch1);
}
void one() {
  radio1.setChannel(random(80));
  radio.setChannel(random(80));
}
void setup() {
  Serial.begin(115200);
  initHP();
  initSP();
}
void initSP() {
  sp = new SPIClass(VSPI);
  sp->begin();
  if (radio1.begin(sp)) {
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(RF24_PA_MAX, true);
    radio1.setDataRate(RF24_2MBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.printPrettyDetails();
    radio1.startConstCarrier(RF24_PA_MAX, ch1);
  } else {
    Serial.println("N1 couldn't start !!!");
  }
}
void initHP() {
  hp = new SPIClass(HSPI);
  hp->begin();
  if (radio.begin(hp)) {
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.printPrettyDetails();
    radio.startConstCarrier(RF24_PA_MAX, ch);
  } else {
    Serial.println("N2 couldn't start !!!");
  }
}
void loop() {one();}