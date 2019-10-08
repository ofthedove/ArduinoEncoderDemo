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
ToDo: High level, encoder in lights out. below should maybe go in interrupt section.

The encoder inputs are read in an interrupt, as they change quite quickly. The interrupt handler needs to be very fast, so rather than processing the encoder values directly they're placed in a queue which is read and processed in the main loop, outside the interrupt context.

### Global Constants
This section names all of the hardware pins used and sets the button debounce time and encoder queue size. Increasing the button debounce time will make the button less susceptable to bounce but also less responsive, decreasing it will have the opposite effect. The button on my encoder is quite good, so a small value is sufficient.

### Global Variables


### Interrupt Service Routines


### Setup


### Main Loop
