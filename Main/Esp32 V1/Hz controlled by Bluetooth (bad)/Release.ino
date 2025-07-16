// Tiktok: ex.fd.cn

//=== Set library ===//
//Select board
//=== Connect ===//
//Out :
//        |1. <line 15>
//        |2. <line 16>
//Bluetooth :
//        |<line 37>
//=== Main ===//

#include <Arduino.h>
#include <driver/ledc.h>
#include <BluetoothSerial.h>

const int outputPin1 = 4;
const int outputPin2 = 5;
const int frequencyMin = 1;
const int frequencyMax = 100000;

const int ledcChannel1 = 0;
const int ledcTimerBit1 = 10;
const int ledcFrequencyBase1 = 1000;

const int ledcChannel2 = 1;
const int ledcTimerBit2 = 10;
const int ledcFrequencyBase2 = 1000;

#define BLUETOOTH_LED_PIN 2

BluetoothSerial SerialBT;

long targetFrequency = frequencyMin;
bool bluetoothConnected = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("32-Hz_driver");
  
  analogReadResolution(12);
  ledcSetup(ledcChannel1, ledcFrequencyBase1, ledcTimerBit1);
  ledcAttachPin(outputPin1, ledcChannel1);
  ledcSetup(ledcChannel2, ledcFrequencyBase2, ledcTimerBit2);
  ledcAttachPin(outputPin2, ledcChannel2);
  pinMode(BLUETOOTH_LED_PIN, OUTPUT);
  digitalWrite(BLUETOOTH_LED_PIN, LOW);
}

void loop() {
  delay(200);
  if (SerialBT.hasClient()) {
    if (!bluetoothConnected) {
      bluetoothConnected = true;
      digitalWrite(BLUETOOTH_LED_PIN, HIGH);
    }
  } else {
    if (bluetoothConnected) {
      bluetoothConnected = false;
      digitalWrite(BLUETOOTH_LED_PIN, LOW);
    }
  }

  if (bluetoothConnected && SerialBT.available() > 0) {
    targetFrequency = SerialBT.parseInt();
    if (targetFrequency < frequencyMin || targetFrequency > frequencyMax) {
      SerialBT.println("Only 1-100000 Hz");
      targetFrequency = frequencyMin;
    } else {
      SerialBT.print("Setting Hz : ");
      SerialBT.print(targetFrequency);
    }
    while (SerialBT.read() != '\n' && SerialBT.available() > 0);
  }

  long currentFrequency = targetFrequency;

  ledcWriteTone(ledcChannel1, currentFrequency);
  ledcWriteTone(ledcChannel2, currentFrequency);

  int maxDuty = pow(2, ledcTimerBit1) - 1;
  ledcWrite(ledcChannel1, maxDuty / 2);
  ledcWrite(ledcChannel2, maxDuty - (maxDuty / 2));

  delay(100);}