#pragma once
#include <stdint.h>

class TM1640 {
private:
  uint8_t Din_Pin;
  uint8_t Sclk_Pin;

  enum {
    NUM_DIGITS = 4,
  };

  enum { //     dGFEDCBA
    DIGIT_0 = 0b00111111,
    DIGIT_1 = 0b00000110,
    DIGIT_2 = 0b01011011,
    DIGIT_3 = 0b01001111,
    DIGIT_4 = 0b01100110,
    DIGIT_5 = 0b01101101,
    DIGIT_6 = 0b01111101,
    DIGIT_7 = 0b00000111,
    DIGIT_8 = 0b01111111,
    DIGIT_9 = 0b01101111,

    DIGIT_DP = 0b10000000, // use it with OR binary operation
    ALL_OFF =  0b00000000,
    NUM_DIGIT_TABLE_ELEM,
  };

  void wait() {
    // delay(1);
  }

  uint8_t toLedPattern(const uint8_t number) {
    switch (number) {
    case 0:
      return DIGIT_0;
    case 1:
      return DIGIT_1;
    case 2:
      return DIGIT_2;
    case 3:
      return DIGIT_3;
    case 4:
      return DIGIT_4;
    case 5:
      return DIGIT_5;
    case 6:
      return DIGIT_6;
    case 7:
      return DIGIT_7;
    case 8:
      return DIGIT_8;
    case 9:
      return DIGIT_9;
    default:
      return 0;
    }
  }

  void startCondition() {
    digitalWrite(Din_Pin, LOW);
    wait();
    digitalWrite(Sclk_Pin, LOW);
  }

  void endCondition() {
    digitalWrite(Sclk_Pin, HIGH);
    wait();
    digitalWrite(Din_Pin, HIGH);
    wait();
  }

  void sendBit(const uint8_t bit) {
    digitalWrite(Sclk_Pin, LOW);
    wait();
    digitalWrite(Din_Pin, bit);
    wait();
    digitalWrite(Sclk_Pin, HIGH);
    wait();
    digitalWrite(Sclk_Pin, LOW);
    wait();
    digitalWrite(Din_Pin, LOW);
    wait();
  }

  void sendByte(uint8_t data) {
    for (auto i = 0; i < 8; ++i) {
      const auto bit = data & 0x01;
      sendBit(bit);
      data >>= 1;
    }
  }

  bool changed;
  uint8_t patterns[NUM_DIGITS];

public:
  TM1640(const uint8_t Din_Pin, const uint8_t Sclk_Pin)
      : Din_Pin(Din_Pin), Sclk_Pin(Sclk_Pin) {}

  void init() {
    changed = false;
    for (auto i = 0; i < NUM_DIGITS; ++i) {
      patterns[i] = 0;
    }

    pinMode(Din_Pin, OUTPUT);
    pinMode(Sclk_Pin, OUTPUT);
    digitalWrite(Sclk_Pin, HIGH);
    digitalWrite(Din_Pin, HIGH);

    // set address mode and brightness
    startCondition();
    sendByte(0b01000000); // Address auto increment
    endCondition();

    startCondition();
    sendByte(0b10001100);
    endCondition();

    allOn();
  }

  void allOn() {
    startCondition();
    sendByte(0b11000000); // from 0
    startCondition();
    for (auto i = 0; i < 4; ++i) {
      uint8_t sendData = 0xFF;
      sendByte(sendData);
    }
    endCondition();

    startCondition();
    sendByte(0b10001100);
    endCondition();
  }

  void allOff() {
    startCondition();
    sendByte(0b11000000); // from 0

    startCondition();
    for (auto i = 0; i < 4; ++i) {
      uint8_t sendData = 0;
      sendByte(sendData);
    }
    endCondition();

    startCondition();
    sendByte(0b10001100);
    endCondition();
  }

  void setDigit(const int digit, const uint8_t value) {
      uint8_t pattern = toLedPattern(value);
      if (patterns[digit] != pattern) {
          changed = true;
          patterns[digit] = pattern;
      }
  }

  void loop() 
  {
      if (!changed) {
          return;
      }

      startCondition();
      sendByte(0b11000000); // from 0

      for (auto i = 0; i < NUM_DIGITS; ++i) {
          uint8_t data = patterns[i];
          if (i == 2) {
              data |= DIGIT_DP;
          }

          sendByte(data);
      }
      endCondition();
  }

  void test() {
    while (true) {
      for (auto n = 0; n < 10; n++) {
        init();
        startCondition();
        sendByte(0b11000000); // from 0

        for (auto i = 0; i < 4; ++i) {
          uint8_t sendData = toLedPattern(n);
          if (i == 2) {
            sendData |= DIGIT_DP;
          }
          sendByte(sendData);
        }
        endCondition();
        delay(50);
      }
    }
  }
};
