//  --Library:
//    |Select board
//    |RF24.h
//    |IRremote.h
//  --Connect:
//    |TX0 & RX0 // RX0 & TX0
//    |Hold the Boot button, click EN to enter Download mode.
//  --Setup:
//    |Nrf|Esp (1 & Gnd // 2 & 3.3v):
//      |RF_1:
//         |3 & 16
//         |4 & 15
//         |5 & 14
//         |6 & 13
//         |7 & 12
//      |RF_2:
//         |3 & 22
//         |4 & 21
//         |5 & 18
//         |6 & 23
//         |7 & 19
// |RF pin: <line 29-32>
// |IR pin: <line 34>
// |ChangeM pin: <line 33>
//  --Use: press IO33 (GND) to change mod.

// ==== Configuration ==== //

#define RF1_3 16
#define RF1_4 15
#define RF2_3 22
#define RF2_4 21
#define Cg_pin 33
#define IR_send 5
#define Led_pin 2
#include "RF24.h"
#include <SPI.h>
#include <IRremote.h>

// ==== Wljm ==== //

SPIClass *sp = nullptr;
SPIClass *hp = nullptr;
RF24 radio(RF1_3, RF1_4, 16000000);
RF24 radio1(RF2_3, RF2_4, 16000000);
bool is_nrf_mode = true;
unsigned int flag = 0;
unsigned int flagv = 0;
int ch = 45;
int ch1 = 45;
void two() {
  if (flagv == 0) {ch1 += 4;}
  else {ch1 -= 4;}
  if (flag == 0) {ch += 2;}
  else {ch -= 2;}
  if ((ch1 > 79) && (flagv == 0)) {flagv = 1;}
  else if ((ch1 < 2) && (flagv == 1)) {flagv = 0;}
  if ((ch > 79) && (flag == 0)) {flag = 1;}
  else if ((ch < 2) && (flag == 1)) {flag = 0;}
  radio.setChannel(ch);
  radio1.setChannel(ch1);}
void one() {
  radio1.setChannel(random(80));
  radio.setChannel(random(80));}
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
    radio1.startConstCarrier(RF24_PA_MAX, ch1);
  digitalWrite(Led_pin, HIGH);
  delay(100);
  digitalWrite(Led_pin, LOW);
  delay(100);}
  else {Serial.println("N1 not run !!!");}}
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
    radio.startConstCarrier(RF24_PA_MAX, ch);
  digitalWrite(Led_pin, HIGH);}
  else {Serial.println("N2 not run !!!");}}

// ==== IR ==== //

int irdl = 5;
void send_nec_ir_code(uint32_t code) {
    IrSender.sendNEC(code, 32);
    delay(irdl);}
void send_nec_ir_code(uint32_t addr, uint32_t cmd) {
    IrSender.sendNEC(addr, cmd, true);
    delay(irdl);}
void send_rc5_ir_code(uint32_t code) {
    IrSender.sendRC5(code, 12);
    delay(irdl);}
void send_rc5_ir_code(uint32_t addr, uint32_t cmd, int bits) {
    IrSender.sendRC5(addr, cmd, bits);
    delay(irdl);}
void send_rc6_ir_code(uint32_t code, int b) {
    IrSender.sendRC6(code, b);
    delay(irdl);}
void send_jvc_ir_code(uint32_t code, int bits) {
    IrSender.sendJVC(code, 16, false);
    delay(irdl);}
void send_samsung_ir_code(uint32_t code) {
    IrSender.sendSAMSUNG(code, 32);
    delay(irdl);}
void send_samsung_ir_code(uint32_t code, uint32_t func) {
    IrSender.sendSamsung(code, func, 1);
    delay(irdl);}
void send_sony_ir_code(uint32_t code, int bits) {
    for (int i = 0; i < 3; ++i) {
    IrSender.sendSony(code, bits);
    delay(40);}
    delay(irdl);}
void send_panasonic_ir_code(uint32_t x, uint32_t y) {
    IrSender.sendPanasonic(x, y, 1);
    delay(irdl);}
void send_philips_ir_code(uint32_t addr, uint32_t cmd) {
    IrSender.sendRC6(addr, cmd, 20);
    delay(irdl);}
void ir_send() {
  digitalWrite(IR_send, OUTPUT);
  IrSender.begin(IR_send);
  digitalWrite(Led_pin, HIGH);
  send_sony_ir_code(0xA90, 12);
  send_nec_ir_code(0x20DF10EF);
  send_rc5_ir_code(0x80C);
  digitalWrite(Led_pin, LOW);
  send_rc5_ir_code(0xC);
  send_rc5_ir_code(0x84C);
  send_rc5_ir_code(0x4C);
  send_rc5_ir_code(0x44C);
  digitalWrite(Led_pin, HIGH);
  send_nec_ir_code(0x2FD48B7);
  send_samsung_ir_code(0xE0E040BF);
  send_samsung_ir_code(0xE0E019E6);
  send_samsung_ir_code(0x909040BF);
  digitalWrite(Led_pin, LOW);
  send_samsung_ir_code(0x07, 0x02);
  send_rc5_ir_code(0x0F, 0x2A, 12);
  digitalWrite(Led_pin, HIGH);
  send_jvc_ir_code(3, 23);
  send_samsung_ir_code(0x909C837);
  send_nec_ir_code(0x8E7152AD);
  digitalWrite(Led_pin, LOW);
  send_rc6_ir_code(0xC, 20);
  send_sony_ir_code(0xF50, 12);
  digitalWrite(Led_pin, HIGH);
  send_nec_ir_code(0x4, 0x0B);
  send_nec_ir_code(0x40000000, 0x0B000000);
  digitalWrite(Led_pin, LOW);
  send_jvc_ir_code(0xF8EB, 16);
  send_rc6_ir_code(0x1000C, 20);
  digitalWrite(Led_pin, HIGH);
  send_rc5_ir_code(0x301);
  send_rc5_ir_code(0xB01);
  send_rc5_ir_code(0x9CC);
  send_nec_ir_code(0x55AA38C7);
  digitalWrite(Led_pin, LOW);
  send_nec_ir_code(0x00BF, 0x0DF2);
  send_nec_ir_code(0x18E710EF);
  send_nec_ir_code(0x20DFBE41);
  digitalWrite(Led_pin, HIGH);
  send_panasonic_ir_code(0x800220, 0xD003);
  send_panasonic_ir_code(0x80022000, 0xD0030000);
  digitalWrite(Led_pin, LOW);
  send_jvc_ir_code(0xC0E8, 16);
  send_samsung_ir_code(0x6060F00F);
  send_nec_ir_code(0x86C6807F);
  digitalWrite(Led_pin, HIGH);
  send_samsung_ir_code(0x1010D02F);
  send_nec_ir_code(0x6F900FF);
  send_nec_ir_code(0x1FE41BE);
  send_nec_ir_code(0x7B6B4FB0);
  digitalWrite(Led_pin, LOW);
  send_nec_ir_code(0x986718E7);
  send_nec_ir_code(0x4B36E21D);
  send_nec_ir_code(0x4B36D32C);
  send_nec_ir_code(0x189710EF);
  digitalWrite(Led_pin, HIGH);
  send_nec_ir_code(0x1897639C);
  send_nec_ir_code(0xAB500FF);
  send_nec_ir_code(0x1FE48B7);
  send_nec_ir_code(0x3E060FC0);
  digitalWrite(Led_pin, LOW);
  send_rc5_ir_code(0xC3D);
  send_nec_ir_code(0xFB38C7);
  send_nec_ir_code(0x1CE348B7);
  send_nec_ir_code(0x1CE338C7);
  digitalWrite(Led_pin, HIGH);
  send_nec_ir_code(0x10EFEB14);
  send_nec_ir_code(0xAF5FC03);
  send_nec_ir_code(0xBD807F);
  send_nec_ir_code(0xC18F50AF);
  digitalWrite(Led_pin, LOW);
  send_nec_ir_code(0x8C73817E);
  send_nec_ir_code(0x38C7AC0A);
  send_nec_ir_code(0xDE010FC0);
  send_nec_ir_code(0xFD00FF);
  digitalWrite(Led_pin, HIGH);
  for (int i = 0; i < 2; ++i) {
    send_panasonic_ir_code(0x4004, 0x100BCBD);
    delay(40);}
  send_nec_ir_code(0x0030, 0x4FB0);
  delay(30);
  for (int i = 0; i < 2; ++i) {
    send_nec_ir_code(0x4CB340BF);
    send_nec_ir_code(0xC1AA09F6);
    send_nec_ir_code(0x189728D7);
    send_nec_ir_code(0x0813, 0x8778);
    send_nec_ir_code(0x4040, 0x0AF5);
    send_nec_ir_code(0x0030, 0x4EB1);
    send_nec_ir_code(0xe8174587);
    delay(100);
    digitalWrite(Led_pin, LOW);}}

// ==== Setup ====//

void setup() {
  Serial.begin(115200);
  pinMode(Cg_pin, INPUT_PULLUP);
  pinMode(Led_pin, OUTPUT);
  initSP();
  initHP();
  is_nrf_mode = true;
  Serial.println("Run in Wljm mode");}
void loop() {
  if (digitalRead(Cg_pin) == LOW) {
  if (digitalRead(Cg_pin) == LOW) {
      is_nrf_mode = !is_nrf_mode;
      if (is_nrf_mode) {
        initHP();
        initSP();
        digitalWrite(Led_pin, HIGH);}
      else {if (sp) {
          radio1.powerDown();
          delete sp;
          sp = nullptr;}
      if (hp) {
          radio.powerDown();
          delete hp;
          hp = nullptr;}}
      while (digitalRead(Cg_pin) == LOW) {
          delay(10);}}}
  if (is_nrf_mode) {one();}
  else {
     ir_send();
     Serial.println("Run in IR_send mode");}}
