# MicroPython

<video src="https://www.youtube.com/watch?v=07vG-_CcDG0" alt="CircuitPython"></video>

Experimental Port of The MicroPython Project to 8-Bit AVR Architecture Devices, 
specifically the Atmega16U2 found on the Arduino USB2SERIAL and Arduino UNO Boards.
The project aims to put an implementation of Python 3.x on microcontrollers and small embedded systems.
You can find the official website at [micropython.org](http://www.micropython.org).

#### Original Source: https://github.com/micropython/micropython/tree/master/ports/minimal
#### Custom Port Source: https://github.com/TheMindVirus/micropython/blob/master/ports/avr8/src/USBtoSerial.c

#### Useful Links:
https://github.com/tewarid/arduino-usb-serial \
https://tewarid.github.io/2016/08/10/arduino-usb-serial-firmware-from-scratch.html \
https://store.arduino.cc/products/uno-mini-le \
https://store.arduino.cc/collections/core-family/products/arduino-uno-rev3 \
https://www.arduino.cc/en/Main.USBSerial \
https://forum.micropython.org/viewtopic.php?t=685 \
https://github.com/micropython/micropython/tree/master/examples/embedding

#### Additional Credits:
 * Moco/LUFA USB Firmware for AVR Microcontrollers - Dean Camera @ FourWalledCubicle
 * Arduino, Atmel, Adafruit Industries, Microchip, Microsoft, Raspberry Pi Foundation, et al.

### WARNING: This project is in beta stage and is subject to changes of the code-base, including project-wide name changes and API changes.

MicroPython implements the entire Python 3.4 syntax (including exceptions,
`with`, `yield from`, etc., and additionally `async`/`await` keywords from
Python 3.5). The following core datatypes are provided: `str` (including
basic Unicode support), `bytes`, `bytearray`, `tuple`, `list`, `dict`, `set`,
`frozenset`, `array.array`, `collections.namedtuple`, classes and instances.
Builtin modules include `sys`, `time`, and `struct`, etc. Select ports have
support for `_thread` module (multithreading). Note that only a subset of
Python 3 functionality is implemented for the data types and modules.

MicroPython can execute scripts in textual source form or from precompiled
bytecode, in both cases either from an on-device filesystem or "frozen" into
the MicroPython executable.

See the repository http://github.com/micropython/pyboard for the MicroPython
board (PyBoard), the officially supported reference electronic circuit board.

#### Major components in this repository:
- py/ -- The Core Python implementation, including compiler, runtime, and
  core library.
- mpy-cross/ -- The MicroPython cross-compiler which is used to turn scripts
  into precompiled bytecode.
- ports/minimal/ -- A minimal MicroPython port. Start with this if you want
  to port MicroPython to another microcontroller.
- ports/avr8/ -- Experimental 8-Bit AVR MicroPython port.
- tests/ -- Test framework and test scripts.

The subdirectories above may include README's with additional info.

External dependencies
---------------------

Building MicroPython ports may require some dependencies installed.
Suggested packages include but are not limited to the following:
```
build-essential, gcc-make, <architecture>-<platform>-gcc, python3
```

Additionally, to develop and compile the experimental 8-Bit AVR source code,
you will need to install and configure Microchip Studio and the LUFA Extension.
The user interface is borrowed from Microsoft Visual Studio and Extensions install in the same way.
https://www.microchip.com/en-us/development-tools-tools-and-software/microchip-studio-for-avr-and-sam-devices

Contributing
------------

MicroPython is an open-source project and welcomes contributions.
To be productive, please be sure to follow the
[Contributors' Guidelines](https://github.com/micropython/micropython/wiki/ContributorGuidelines)
and the [Code Conventions](https://github.com/micropython/micropython/blob/master/CODECONVENTIONS.md).
Note that MicroPython is licenced under the MIT license, and all contributions
should follow this license.
