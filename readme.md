# Traffic light

Easy toy for my son. Built on board [Digispark ATiny85 Model A](http://digistump.com/wiki/digispark/tutorials/modelbi2c).
Three-color traffic light emulator. Switches automatically in the RED-YELLOW-GREEN-YELLOW cycle and blinks before switching to the next color.
A short press on the button switches colors. Long press the button puts the device into the "unregulated intersection" mode (yellow blink permanentlytly). Returns to normal mode by pressing the button or by a timeout of 30 seconds.

## Connect digispark ATiny85 to Arduino IDE

I used [official tutorial](http://digistump.com/wiki/digispark/tutorials/connecting) in `windows 10 x64 build 22H2` with [Arduino 1.6.5r5](https://downloads.arduino.cc/arduino-1.6.5-r5-windows.exe) and it just work.
Some users experience [problems when connecting the board via USB 3.0](https://habr.com/ru/post/413927/). But I didn't encounter this, because used USB 2.0 hub.