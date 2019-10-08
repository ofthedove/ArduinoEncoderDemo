# Arduino Encoder Demo
Demonstrates how to use a rotary encoder for input in an Arduino sketch. Tested on ESP32.

## Hardware
The controller I used is the DoIt ESP32 Devkit V1. I purchased it from AliExpress. ([link](https://www.aliexpress.com/item/32659152063.html?spm=a2g0s.9042311.0.0.42ab4c4dlEfLZD))

The encoder I selected uses Gray encoding and has detents on every other step. It also has an integrated push button. It too was sourced from AliExpress. ([link](https://www.aliexpress.com/item/2050939127.html?spm=a2g0s.9042311.0.0.42ab4c4dlEfLZD))

I also used an RGB LED with current limiting resistors.

## Circuit

Device Pin | Controller Pin | Software Pin
--- | --- | ---
Encoder CLK | D19 | 19 
Encoder DT | D18 | 18
Encoder SW | D5 | 5
Encoder + | 3v3 | n/a
Encoder GND | GND | n/a
LED Common Cathode | GND | n/a
LED Red | D21 | 21
LED Green | D22 | 22
LED Blue | D23 | 23

## Software
ToDo: Description of software operation
