//  --Library:
//    |Select board
//    |BluetoothSerial
//    |Adafruit GFX

const int outputPin1 = 4;
#define I2C_SDA 16
#define I2C_SCL 17

#include <Arduino.h>
#include <driver/ledc.h>
#include <BluetoothSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int frequencyMin = 1;
const int frequencyMax = 1000000;
const int ledcChannel1 = 0;
const int ledcTimerBit1 = 10;
const int ledcFrequencyBase1 = 1000;
#define BLUETOOTH_LED_PIN 2
BluetoothSerial SerialBT;
long targetFrequency = frequencyMin;
bool bluetoothConnected = false;

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  SerialBT.begin("32-Hz_driver");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);}
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,10);
  display.println("Ready!");
  display.display();
  ledcSetup(ledcChannel1, ledcFrequencyBase1, ledcTimerBit1);
  ledcAttachPin(outputPin1, ledcChannel1);
  pinMode(BLUETOOTH_LED_PIN, OUTPUT);
  digitalWrite(BLUETOOTH_LED_PIN, LOW);}

void loop() {
  delay(200);
  if (SerialBT.hasClient()) {
    if (!bluetoothConnected) {
      bluetoothConnected = true;
      digitalWrite(BLUETOOTH_LED_PIN, HIGH);}}
    else {
    if (bluetoothConnected) {
      bluetoothConnected = false;
      digitalWrite(BLUETOOTH_LED_PIN, LOW);}}
  if (bluetoothConnected && SerialBT.available() > 0) {
    targetFrequency = SerialBT.parseInt();
    if (targetFrequency < frequencyMin || targetFrequency > frequencyMax) {
      SerialBT.println("Only 1-1000000 Hz");
      targetFrequency = frequencyMin;}
    else {
      SerialBT.print("Setting Hz : ");
      SerialBT.print(targetFrequency);
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("HZ:");
      display.setCursor(0, 20);
      display.setTextSize(3);
      display.print(targetFrequency);
      display.display();}
    while (SerialBT.read() != '\n' && SerialBT.available() > 0);}
  long currentFrequency = targetFrequency;
  ledcWriteTone(ledcChannel1, currentFrequency);
  int maxDuty = pow(2, ledcTimerBit1) - 1;
  ledcWrite(ledcChannel1, maxDuty / 2);
  delay(100);}
