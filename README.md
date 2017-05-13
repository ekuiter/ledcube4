# LED Cube 4x4x4

This is my implementation of a 4x4x4 LED cube in Arduino, using shift registers (optionally without).

On this branch (master) you can find the Arduino sketch for the cube
inside the `ledcube4` directory.

There's also a simple CoAP server In the `coap` folder. To use it, you
need Python 2 and some libraries (`pip install txthings pyserial`),
then run `python2 coap/ledcube4.py <serial port>` (on my system that's
`/dev/tty.usbmodem1411`).

If you'd like more information on how to build an LED cube yourself, visit the [project homepage](http://www.elias-kuiter.de/elektronik/led-wuerfel).
There you can find demo videos and information on constructing and programming your own cube.
