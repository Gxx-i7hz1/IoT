//  --Library:
//    |Select board
//    |IRremote.h
//  --Connect:
//    |TX0 & RX0 // RX0 & TX0
//    |Hold the Boot button, click EN to enter Download mode.
//    |Output pin: <line 9>

#define IR_pin 5
#include <IRremote.h>
void setup() {ir();}
void loop() {}
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
void ir() {
pinMode(IR_pin, OUTPUT);
IrSender.begin(IR_pin);
while (true) {
  send_sony_ir_code(0xA90, 12);
  send_nec_ir_code(0x20DF10EF);
  send_rc5_ir_code(0x80C);
  send_rc5_ir_code(0xC);
  send_rc5_ir_code(0x84C);
  send_rc5_ir_code(0x4C);
  send_rc5_ir_code(0x44C);
  send_nec_ir_code(0x2FD48B7);
  send_samsung_ir_code(0xE0E040BF);
  send_samsung_ir_code(0xE0E019E6);
  send_samsung_ir_code(0x909040BF);
  send_samsung_ir_code(0x07, 0x02);
  send_rc5_ir_code(0x0F, 0x2A, 12);
  send_jvc_ir_code(3, 23);
  send_samsung_ir_code(0x909C837);
  send_nec_ir_code(0x8E7152AD);
  send_rc6_ir_code(0xC, 20);
  send_sony_ir_code(0xF50, 12);
  send_nec_ir_code(0x4, 0x0B);
  send_nec_ir_code(0x40000000, 0x0B000000);
  send_jvc_ir_code(0xF8EB, 16);
  send_rc6_ir_code(0x1000C, 20);
  send_rc5_ir_code(0x301);
  send_rc5_ir_code(0xB01);
  send_rc5_ir_code(0x9CC);
  send_nec_ir_code(0x55AA38C7);
  send_nec_ir_code(0x00BF, 0x0DF2);
  send_nec_ir_code(0x18E710EF);
  send_nec_ir_code(0x20DFBE41);
  send_panasonic_ir_code(0x800220, 0xD003);
  send_panasonic_ir_code(0x80022000, 0xD0030000);
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
    delay(100);}
  send_jvc_ir_code(0xC0E8, 16);
  send_samsung_ir_code(0x6060F00F);
  send_nec_ir_code(0x86C6807F);
  send_samsung_ir_code(0x1010D02F);
  send_nec_ir_code(0x6F900FF);
  send_nec_ir_code(0x1FE41BE);
  send_nec_ir_code(0x7B6B4FB0);
  send_nec_ir_code(0x986718E7);
  send_nec_ir_code(0x4B36E21D);
  send_nec_ir_code(0x4B36D32C);
  send_nec_ir_code(0x189710EF);
  send_nec_ir_code(0x1897639C);
  send_nec_ir_code(0xAB500FF);
  send_nec_ir_code(0x1FE48B7);
  send_nec_ir_code(0x3E060FC0);
  send_rc5_ir_code(0xC3D);
  send_nec_ir_code(0xFB38C7);
  send_nec_ir_code(0x1CE348B7);
  send_nec_ir_code(0x1CE338C7);
  send_nec_ir_code(0x10EFEB14);
  send_nec_ir_code(0xAF5FC03);
  send_nec_ir_code(0xBD807F);
  send_nec_ir_code(0xC18F50AF);
  send_nec_ir_code(0x8C73817E);
  send_nec_ir_code(0x38C7AC0A);
  send_nec_ir_code(0xDE010FC0);
  send_nec_ir_code(0xFD00FF);}}
