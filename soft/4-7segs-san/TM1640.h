/**
 * @file TM1640.h
 * @brief TM1640 LED Driver Library(header only)
 * 

MIT License

Copyright (c) 2023 Kinoshita Laboratory

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#pragma once
#include <stdint.h>
#include <Arduino.h>

namespace kinoshita_lab
{

class TM1640
{
private:
    uint8_t Din_Pin;
    uint8_t Sclk_Pin;

    enum
    {
        NUM_DIGITS = 4,
    };

    enum
    { //               dGFEDCBA
        DIGIT_0    = 0b00111111,
        DIGIT_1    = 0b00000110,
        DIGIT_2    = 0b01011011,
        DIGIT_3    = 0b01001111,
        DIGIT_4    = 0b01100110,
        DIGIT_5    = 0b01101101,
        DIGIT_6    = 0b01111101,
        DIGIT_7    = 0b00000111,
        DIGIT_8    = 0b01111111,
        DIGIT_9    = 0b01101111,
        DIGIT_DP   = 0b10000000, // use it with OR binary operation
        ALL_OFF    = 0b00000000,
        MINUS_SIGN = 0b01000000, // set -1 to display minus sign

        //         dGFEDCBA
        CHAR_A = 0b01110111,
        CHAR_B = 0b01111100, // 'b'
        CHAR_C = 0b00111001,
        CHAR_D = 0b01011110, // 'd'
        CHAR_E = 0b01111001,
        CHAR_F = 0b01110001,
        CHAR_G = 0b00111101,
        CHAR_H = 0b01110110,
        CHAR_I = 0b00000110,
        CHAR_J = 0b00011110,
        CHAR_K = 0b01110110, // 'K' and 'H' are same
        CHAR_L = 0b00111000,
        CHAR_M = 0b00010101,
        CHAR_N = 0b00110111,
        CHAR_O = 0b00111111,
        CHAR_P = 0b01110011,
        CHAR_Q = 0b01100111, // 'q'
        CHAR_R = 0b01010000, // 'r'
        CHAR_S = 0b01101101,
        CHAR_T = 0b01000100, // 't'
        CHAR_U = 0b00011100, // 'u'
        CHAR_V = 0b00011100, // 'v' and 'u' are same
        CHAR_W = 0b00011100, // 'w' and 'u' are same
        CHAR_X = 0b01110110, // 'x' and 'h' are same
        CHAR_Y = 0b01101110,
        CHAR_Z = 0b01011011,
    };

    // note: implement this if required.
    // arduino uno/nano OK
    // seeeduino xiao OK
    void wait()
    {
        //delay(1);
    }

    uint8_t toLedPattern(const int8_t number)
    {
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
        case SPECIAL_NUMBER_MINUS_SIGN:
            return MINUS_SIGN;
        case SPECIAL_NUMBER_ALL_OFF:
            return ALL_OFF;
        case 'A': // fall through
        case 'a':
            return CHAR_A;
        case 'B': // fall through
        case 'b':
            return CHAR_B;
        case 'C': // fall through
        case 'c':
            return CHAR_C;
        case 'D': // fall through
        case 'd':
            return CHAR_D;
        case 'E': // fall through
        case 'e':
            return CHAR_E;
        case 'F': // fall through
        case 'f':
            return CHAR_F;
        case 'G': // fall through
        case 'g':
            return CHAR_G;

        case 'H': // fall through
        case 'h':
            return CHAR_H;
        case 'I': // fall through
        case 'i':
            return CHAR_I;
        case 'J': // fall through
        case 'j':
            return CHAR_J;
        case 'K': // fall through
        case 'k':
            return CHAR_K;
        case 'L': // fall through
        case 'l':
            return CHAR_L;
        case 'M': // fall through
        case 'm':
            return CHAR_M;
        case 'N': // fall through
        case 'n':
            return CHAR_N;
        case 'O': // fall through
        case 'o':
            return CHAR_O;
        case 'P': // fall through
        case 'p':
            return CHAR_P;
        case 'Q': // fall through
        case 'q':
            return CHAR_Q;
        case 'R': // fall through
        case 'r':
            return CHAR_R;
        case 'S': // fall through
        case 's':
            return CHAR_S;
        case 'T': // fall through
        case 't':
            return CHAR_T;
        case 'U': // fall through
        case 'u':
            return CHAR_U;
        case 'V': // fall through
        case 'v':
            return CHAR_V;
        case 'W': // fall through
        case 'w':
            return CHAR_W;
        case 'X': // fall through
        case 'x':
            return CHAR_X;
        case 'Y': // fall through
        case 'y':
            return CHAR_Y;
        case 'Z': // fall through
        case 'z':
            return CHAR_Z;
        case ' ':
            return ALL_OFF;
        default:
            return 0;
        }
    }

    void startCondition()
    {
        digitalWrite(Din_Pin, LOW);
        wait();
        digitalWrite(Sclk_Pin, LOW);
    }

    void endCondition()
    {
        digitalWrite(Sclk_Pin, HIGH);
        wait();
        digitalWrite(Din_Pin, HIGH);
        wait();
    }

    void sendBit(const uint8_t bit)
    {
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

    void sendByte(uint8_t data)
    {
        for (auto i = 0; i < 8; ++i) {
            const auto bit = data & 0x01;
            sendBit(bit);
            data >>= 1;
        }
    }

    bool changed      = false;
    bool enabled      = true;
    int decimal_point = -1;
    uint8_t patterns[NUM_DIGITS];

public:
    TM1640(const uint8_t Din_Pin, const uint8_t Sclk_Pin)
        : Din_Pin(Din_Pin), Sclk_Pin(Sclk_Pin) {}

    enum
    {
        SPECIAL_NUMBER_MINUS_SIGN = -1,
        SPECIAL_NUMBER_ALL_OFF    = -10,
    };

    void init()
    {
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
        sendByte(0b10001111);
        endCondition();
    }

    void clearAll()
    {
        for (auto i = 0; i < NUM_DIGITS; ++i) {
            patterns[i] = 0;
        }
        changed = true;
    }

    void allOn()
    {
        for (auto i = 0; i < NUM_DIGITS; ++i) {
            patterns[i] = 0xff;
        }
        setEnable(true);
        changed = true;
    }

    void allOff()
    {
        setEnable(false);
    }

    /**
     * @note Execute immidiately
     */
    void setEnable(const bool _enable)
    {
        enabled = _enable;
        if (!enabled) {
            startCondition();
            sendByte(0b10000000);
            endCondition();
        } else {
            Serial.println("setEnable");
            startCondition();
            sendByte(0b10001000);
            endCondition();
        }
    }
    bool getEnable() const
    {
        return enabled;
    }

    void setDigit(const int digit, const uint8_t value)
    {
        uint8_t pattern = toLedPattern(value);
        if (patterns[digit] != pattern) {
            changed         = true;
            patterns[digit] = pattern;
        }
    }

    /**
     * @param  digit: count from left to right, start from 0, -1 to invalidate
     * @retval None
     */
    void setDecimalPoint(const int digit)
    {
        decimal_point = digit;
    }

    void update()
    {
        changed = true;
    }

    void loop()
    {
        if (!changed) {
            return;
        }
        if (!enabled) {
            return;
        }
        // workaround: must set brightness every time or it will be dark
        startCondition();
        sendByte(0b10001111);
        endCondition();

        startCondition();
        sendByte(0b11000000); // from 0

        for (auto i = 0; i < NUM_DIGITS; ++i) {
            uint8_t data = patterns[i];
            if (i == decimal_point) {
                data |= DIGIT_DP;
            }
            sendByte(data);
        }
        endCondition();
        changed = false;
    }

    void test()
    {
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
}
