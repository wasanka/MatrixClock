/*
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LedControl_h
#define LedControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const static int SPEED = 10;

const static int ASCII_CHARSET_LENGTH[127] = {
            1,
            1,
            2,
            5,
            5,
            5,
            6,
            2,
            2,
            2,
            5,
            5,
            2,
            4,
            1,
            6,
            5,
            2,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            1,
            2,
            4,
            4,
            4,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            3,// I
            5,
            5,
            5,
            5,
            6,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            2, // [
            6,
            2,
            5,
            5,
            2,
            5,
            5,
            5, // c
            5,
            5,
            4,
            5,
            5,
            1,
            3,
            5,
            1,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            4, //t
            5,
            5,
            5,
            5,
            5,
            5,
            4,
            1,
            4,
            6
    };


const static byte ASCII_CHARSET[127][8] = {
            { // ASCII 32 [ ]
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b0
            }
            ,
            { // ASCII 33 [!]
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b0,
                    0b1
            },
            { // ASCII 34 ["]
                    0b11,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00
            },
            { // ASCII 35 [#]
                    0b00000,
                    0b01010,
                    0b01010,
                    0b11111,
                    0b01010,
                    0b11111,
                    0b01010,
                    0b01010
            },
            { // ASCII 36 [$]
                    0b01110,
                    0b10101,
                    0b10101,
                    0b10100,
                    0b01110,
                    0b00101,
                    0b10101,
                    0b01110
            },
            { // ASCII 37 [%]
                    0b00000,
                    0b00000,
                    0b00000,
                    0b11001,
                    0b10010,
                    0b00100,
                    0b01001,
                    0b10011
            },
            { // ASCII 38 [&]
                    0b011100,
                    0b100010,
                    0b100010,
                    0b100100,
                    0b011001,
                    0b100101,
                    0b100010,
                    0b011101
            },
            { // ASCII 39 [']
                    0b10,
                    0b10,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00
            },
            { // ASCII 40 [(]
                    0b01,
                    0b10,
                    0b10,
                    0b10,
                    0b10,
                    0b10,
                    0b10,
                    0b01
            },
            { // ASCII 41 [)]
                    0b10,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b10
            },
            { // ASCII 42 [*]
                    0b10101,
                    0b01110,
                    0b11111,
                    0b01110,
                    0b10101,
                    0b00000,
                    0b00000,
                    0b00000
            },
            { // ASCII 43 [+]
                    0b00000,
                    0b00100,
                    0b00100,
                    0b11111,
                    0b11111,
                    0b00100,
                    0b00100,
                    0b00000
            },
            { // ASCII 44 [,]
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b01,
                    0b10
            },
            { // ASCII 45 [-]
                    0b0000,
                    0b0000,
                    0b0000,
                    0b1111,
                    0b1111,
                    0b0000,
                    0b0000,
                    0b0000
            },
            { // ASCII 46 [.]
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b0,
                    0b1
            },
            { // ASCII 47 [/]
                    0b000000,
                    0b000001,
                    0b000010,
                    0b000100,
                    0b001000,
                    0b010000,
                    0b100000,
                    0b000000
            },
            { // ASCII 48 [0]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b10011,
                    0b10101,
                    0b11001,
                    0b10001,
                    0b01110
            },
            { // ASCII 49 [1]
                    0b01,
                    0b11,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b01
            },
            { // ASCII 50 [2]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b00001,
                    0b00010,
                    0b00100,
                    0b01000,
                    0b11111
            },
            { // ASCII 51 [3]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b00110,
                    0b00110,
                    0b00001,
                    0b10001,
                    0b01110
            },
            { // ASCII 52 [4]
                    0b10000,
                    0b10000,
                    0b10000,
                    0b10010,
                    0b10010,
                    0b11111,
                    0b00010,
                    0b00010
            },
            { // ASCII 53 [5]
                    0b11111,
                    0b10000,
                    0b10000,
                    0b11110,
                    0b00001,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 54 [6]
                    0b01110,
                    0b10001,
                    0b10000,
                    0b11110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 55 [7]
                    0b11111,
                    0b00001,
                    0b00001,
                    0b00010,
                    0b00100,
                    0b01000,
                    0b10000,
                    0b10000
            },
            { // ASCII 56 [8]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b01110,
                    0b01110,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 57 [9]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01111,
                    0b00001,
                    0b10001,
                    0b01110
            },
            { // ASCII 58 [:]
                    0b0,
                    0b1,
                    0b1,
                    0b0,
                    0b0,
                    0b1,
                    0b1,
                    0b0
            },
            { // ASCII 59 [;]
                    0b00,
                    0b01,
                    0b01,
                    0b00,
                    0b00,
                    0b01,
                    0b10,
                    0b00
            },
            { // ASCII 60 [<]
                    0b0001,
                    0b0010,
                    0b0100,
                    0b1000,
                    0b1000,
                    0b0100,
                    0b0010,
                    0b0001
            },
            { // ASCII 61 [=]
                    0b0000,
                    0b0000,
                    0b1111,
                    0b0000,
                    0b0000,
                    0b1111,
                    0b0000,
                    0b0000
            },
            { // ASCII 62 [>]
                    0b1000,
                    0b0100,
                    0b0010,
                    0b0001,
                    0b0001,
                    0b0010,
                    0b0100,
                    0b1000
            },
            { // ASCII 63 [?]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b00001,
                    0b00110,
                    0b01000,
                    0b00000,
                    0b01000
            },
            { // ASCII 64 [@]
                    0b01110,
                    0b10001,
                    0b10101,
                    0b10101,
                    0b10101,
                    0b10010,
                    0b10000,
                    0b01110
            },
            { // ASCII 65 [A]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b11111,
                    0b10001,
                    0b10001,
                    0b10001
            },
            { // ASCII 66 [B]
                    0b11110,
                    0b10001,
                    0b10001,
                    0b11110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b11110
            },
            { // ASCII 67 [C]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b10000,
                    0b10000,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 68 [D]
                    0b11110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b11110
            },
            { // ASCII 69 [E]
                    0b11111,
                    0b10000,
                    0b10000,
                    0b11110,
                    0b10000,
                    0b10000,
                    0b10000,
                    0b11111
            },
            { // ASCII 70 [F]
                    0b11111,
                    0b10000,
                    0b10000,
                    0b11110,
                    0b10000,
                    0b10000,
                    0b10000,
                    0b10000
            },
            { // ASCII 71 [G]
                    0b01110,
                    0b10001,
                    0b10000,
                    0b10000,
                    0b10111,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 72 [H]
                    0b10001,
                    0b10001,
                    0b10001,
                    0b11111,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001
            },
            { // ASCII 73 [I]
                    0b111,
                    0b010,
                    0b010,
                    0b010,
                    0b010,
                    0b010,
                    0b010,
                    0b111
            },
            { // ASCII 74 [J]
                    0b01111,
                    0b00010,
                    0b00010,
                    0b00010,
                    0b00010,
                    0b10010,
                    0b10010,
                    0b01100
            },
            { // ASCII 75 [K]
                    0b10001,
                    0b10010,
                    0b10100,
                    0b11000,
                    0b11000,
                    0b10100,
                    0b10010,
                    0b10001
            },
            { // ASCII 76 [L]
                    0b10000,
                    0b10000,
                    0b10000,
                    0b10000,
                    0b10000,
                    0b10000,
                    0b10000,
                    0b11111
            },
            { // ASCII 77 [M]
                    0b11011,
                    0b11011,
                    0b10101,
                    0b10101,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001
            },
            { // ASCII 78 [N]
                    0b110001,
                    0b101001,
                    0b100101,
                    0b100011,
                    0b100001,
                    0b100001,
                    0b100001,
                    0b100001
            },
            { // ASCII 79 [O]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 80 [P]
                    0b11110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b11110,
                    0b10000,
                    0b10000,
                    0b10000
            },
            { // ASCII 81 [Q]
                    0b01110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10010,
                    0b01101
            },
            { // ASCII 82 [R]
                    0b11110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b11110,
                    0b10100,
                    0b10010,
                    0b10001
            },
            { // ASCII 83 [S]
                    0b01110,
                    0b10001,
                    0b10000,
                    0b11000,
                    0b00110,
                    0b00001,
                    0b10001,
                    0b01110
            },
            { // ASCII 84 [T]
                    0b11111,
                    0b00100,
                    0b00100,
                    0b00100,
                    0b00100,
                    0b00100,
                    0b00100,
                    0b00100
            },
            { // ASCII 85 [U]
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 86 [V]
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01010,
                    0b00100
            },
            { // ASCII 87 [W]
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10101,
                    0b10101,
                    0b10101,
                    0b11011
            },
            { // ASCII 88 [X]
                    0b10001,
                    0b01010,
                    0b00100,
                    0b00100,
                    0b00100,
                    0b00100,
                    0b01010,
                    0b10001
            },
            { // ASCII 89 [Y]
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01010,
                    0b00100,
                    0b00100,
                    0b00100
            },
            { // ASCII 90 [Z]
                    0b11111,
                    0b00001,
                    0b00001,
                    0b00010,
                    0b00100,
                    0b01000,
                    0b10000,
                    0b11111
            },
            { // ASCII 91 [[]
                    0b11,
                    0b10,
                    0b10,
                    0b10,
                    0b10,
                    0b10,
                    0b10,
                    0b11
            },
            { // ASCII 92 [\]
                    0b000000,
                    0b100000,
                    0b010000,
                    0b001000,
                    0b000100,
                    0b000010,
                    0b000001,
                    0b000000
            },
            { // ASCII 93 []]
                    0b11,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b01,
                    0b11
            },
            { // ASCII 94 [^]
                    0b00100,
                    0b01010,
                    0b10001,
                    0b00000,
                    0b00000,
                    0b00000,
                    0b00000,
                    0b00000
            },
            { // ASCII 95 [_]
                    0b00000,
                    0b00000,
                    0b00000,
                    0b00000,
                    0b00000,
                    0b00000,
                    0b00000,
                    0b11111
            },
            { // ASCII 96 [`]
                    0b10,
                    0b01,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00,
                    0b00
            },
            { // ASCII 97 [a]
                    0b00000,
                    0b00000,
                    0b01110,
                    0b10001,
                    0b00001,
                    0b01111,
                    0b10001,
                    0b01111
            },
            { // ASCII 98 [b]
                    B10000,
                    B10000,
                    B10000,
                    B11110,
                    B10001,
                    B10001,
                    B10001,
                    B11110
            },
            { // ASCII 99 [c]
                    0b00000,
                    0b00000,
                    0b01110,
                    0b10001,
                    0b10000,
                    0b10000,
                    0b10001,
                    0b01110
            },
            { // ASCII 100 [d]
                    B00001,
                    B00001,
                    B00001,
                    B01111,
                    B10001,
                    B10001,
                    B10001,
                    B01111
            },
            { // ASCII 101 [e]
                    0b00000,
                    0b00000,
                    0b01110,
                    0b10001,
                    0b10001,
                    0b11110,
                    0b10000,
                    0b01111
            },
            { // ASCII 102 [f]
                    B0010,
                    B0101,
                    B0100,
                    B1110,
                    B0100,
                    B0100,
                    B0100,
                    B0100
            },
            { // ASCII 103 [g]
                    0b00000,
                    0b00000,
                    0b01110,
                    0b10001,
                    0b10001,
                    0b01111,
                    0b00001,
                    0b01110
            },
            { // ASCII 104 [h]
                    B10000,
                    B10000,
                    B10000,
                    B11110,
                    B10001,
                    B10001,
                    B10001,
                    B10001
            },
            { // ASCII 105 [i]
                    B1,
                    B0,
                    B1,
                    B1,
                    B1,
                    B1,
                    B1,
                    B1
            },
            { // ASCII 106 [j]
                    B001,
                    B000,
                    B001,
                    B001,
                    B001,
                    B001,
                    B101,
                    B010
            },
            { // ASCII 107 [k]
                    B10000,
                    B10000,
                    B10010,
                    B10100,
                    B11000,
                    B10100,
                    B10010,
                    B10001
            },
            { // ASCII 108 [l]
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1
            },
            { // ASCII 109 [m]
                    0b00000,
                    0b00000,
                    0b11011,
                    0b10101,
                    0b10101,
                    0b10101,
                    0b10001,
                    0b10001
            },
            { // ASCII 110 [n]
                    0b00000,
                    0b00000,
                    0b10110,
                    0b11001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001
            },
            { // ASCII 111 [o]
                    0b00000,
                    0b00000,
                    0b01110,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01110
            },
            { // ASCII 112 [p]
                    0b00000,
                    0b00000,
                    0b11110,
                    0b10001,
                    0b10001,
                    0b11110,
                    0b10000,
                    0b10000
            },
            { // ASCII 113 [q]
                    0b00000,
                    0b00000,
                    0b01111,
                    0b10001,
                    0b10001,
                    0b01111,
                    0b00001,
                    0b00001
            },
            { // ASCII 114 [r]
                    0b00000,
                    0b00000,
                    0b10110,
                    0b11001,
                    0b10000,
                    0b10000,
                    0b10000,
                    0b10000
            },
            { // ASCII 115 [s]
                    0b00000,
                    0b00000,
                    0b01110,
                    0b10001,
                    0b01100,
                    0b00010,
                    0b10001,
                    0b01110
            },
            { // ASCII 116 [t]
                    B0100,
                    B0100,
                    B1110,
                    B0100,
                    B0100,
                    B0100,
                    B0101,
                    B0010
            },
            { // ASCII 117 [u]
                    0b00000,
                    0b00000,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10011,
                    0b01101
            },
            { // ASCII 118 [v]
                    0b00000,
                    0b00000,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01010,
                    0b00100
            },
            { // ASCII 119 [w]
                    0b00000,
                    0b00000,
                    0b10001,
                    0b10001,
                    0b10101,
                    0b10101,
                    0b11011,
                    0b10001
            },
            { // ASCII 120 [x]
                    0b00000,
                    0b00000,
                    0b10001,
                    0b01010,
                    0b00100,
                    0b00100,
                    0b01010,
                    0b10001
            },
            { // ASCII 121 [y]
                    0b00000,
                    0b00000,
                    0b10001,
                    0b10001,
                    0b10001,
                    0b01111,
                    0b00001,
                    0b01110
            },
            { // ASCII 122 [z]
                    0b00000,
                    0b00000,
                    0b11111,
                    0b00011,
                    0b00100,
                    0b01000,
                    0b10000,
                    0b11111
            },
            { // ASCII 123 [{]
                    0b0011,
                    0b0100,
                    0b0100,
                    0b1000,
                    0b1000,
                    0b0100,
                    0b0100,
                    0b0011
            },
            { // ASCII 124 [|]
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1,
                    0b1
            },
            { // ASCII 125 [}]
                    0b1100,
                    0b0010,
                    0b0010,
                    0b0001,
                    0b0001,
                    0b0010,
                    0b0010,
                    0b1100
            },
            { // ASCII 126 [~]
                    0b000000,
                    0b000000,
                    0b000000,
                    0b100110,
                    0b011001,
                    0b000000,
                    0b000000,
                    0b000000
            }
    };

class LedControl {
 private :
    /* The array for shifting the data to the devices */
    byte spidata[16];
    /* Send out a single command to the device */
    void spiTransfer(int addr, byte opcode, byte data);

	/* We keep track of the led-status for all 8 devices in this array */
    byte status[64];
     /* Data is shifted out of this pin*/
    int LEDCONTROL_SPI_MOSI;
    /* The clock is signaled on this pin */
    int LEDCONTROL_SPI_CLK;
    /* This one is driven LOW for chip selectzion */
    int LEDCONTROL_SPI_CS;
    /* The maximum number of devices we use */
    int maxDevices;
	
   
 public:
    /* 
     * Create a new controler 
     * Params :
     * dataPin		pin on the Arduino where data gets shifted out
     * clockPin		pin for the clock
     * csPin		pin for selecting the device 
     * numDevices	maximum number of devices that can be controled
     */
    LedControl(int dataPin, int clkPin, int csPin, int numDevices=1);

    /*
     * Gets the number of devices attached to this LedControl.
     * Returns :
     * int	the number of devices on this LedControl
     */
    int getDeviceCount();

    /* 
     * Set the shutdown (power saving) mode for the device
     * Params :
     * addr	The address of the display to control
     * status	If true the device goes into power-down mode. Set to false
     *		for normal operation.
     */
    void shutdown(int addr, bool status);

    /* 
     * Set the number of digits (or rows) to be displayed.
     * See datasheet for sideeffects of the scanlimit on the brightness
     * of the display.
     * Params :
     * addr	address of the display to control
     * limit	number of digits to be displayed (1..8)
     */
    void setScanLimit(int addr, int limit);

    /* 
     * Set the brightness of the display.
     * Params:
     * addr		the address of the display to control
     * intensity	the brightness of the display. (0..15)
     */
    void setIntensity(int addr, int intensity);

    /* 
     * Switch all Leds on the display off. 
     * Params:
     * addr	address of the display to control
     */
    void clearDisplay(int addr);
	
    void clearAll();

    /* 
     * Set the status of a single Led.
     * Params :
     * addr	address of the display 
     * row	the row of the Led (0..7)
     * col	the column of the Led (0..7)
     * state	If true the led is switched on, 
     *		if false it is switched off
     */
    void setLed(int addr, int row, int col, boolean state);

    /* 
     * Set all 8 Led's in a row to a new state
     * Params:
     * addr	address of the display
     * row	row which is to be set (0..7)
     * value	each bit set to 1 will light up the
     *		corresponding Led.
     */
    void setRow(int addr, int row, byte value);

    /* 
     * Set all 8 Led's in a column to a new state
     * Params:
     * addr	address of the display
     * col	column which is to be set (0..7)
     * value	each bit set to 1 will light up the
     *		corresponding Led.
     */
    void setColumn(int addr, int col, byte value);

    /* 
     * Display a hexadecimal digit on a 7-Segment Display
     * Params:
     * addr	address of the display
     * digit	the position of the digit on the display (0..7)
     * value	the value to be displayed. (0x00..0x0F)
     * dp	sets the decimal point.
     */
    void setDigit(int addr, int digit, byte value, boolean dp);

    void print(String s);

    boolean isFirstBitSet(byte b);
    void printSegment(int segment, byte rows[]);
};

#endif	//LedControl.h



