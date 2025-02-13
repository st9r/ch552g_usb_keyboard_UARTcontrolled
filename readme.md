# USB Mini Keyboard with CH552G
![telegram-cloud-photo-size-2-5289929060786500294-y](https://github.com/user-attachments/assets/d19ecbac-7c16-4ff5-8c06-5418462fbd20)

## Introduction
NON DESTRUCTIVE MOD which allows to integrate cheap CH552G keyboard with various car projects.
In my case - for extending CDC Emulator SWC functionality with USB HID for Android HU to navigate thru CarPlay.  


## What's Inside
UART1 & UART0 use alternative PINS, which allows to use mechanical keys and rotary encoder also.
CH552G RX pin is on P3.4 (PIN11)
![image](https://github.com/user-attachments/assets/a22c0102-b9b1-4c27-bd00-e2eef4785380)

UART1 preconfigured to 38400 
![telegram-cloud-photo-size-2-5289929060786500295-y](https://github.com/user-attachments/assets/32652e06-cee6-4262-87ae-ccc87adff409)


## How to Build

This firmware uses the Arduino platform to simplify the build process. 

1. Install the Arduino IDE.
2. Add support for CH552G:
   - Go to Preferences -> Additional Board Manager.
   - Add https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json.
3. Open the project `ch552g_usb_keyboard_UARTcontrolled.ino`.
   - In the Tools menu, select CH55xDuino board.
   - In Tools, select bootloader: P3.6 (D+) Pull up.
   - In Tools, select clock source: 16MHz (internal) 3.5V or 5V.
   - In Tools, select upload method: USB.
   - In Tools, select USB Setting: USER CODE w/148B USB RAM.
4. Compile the project.
5. Set the keyboard in bootloader mode (see below).
6. Flash the project. (*Original firmware will be completed lost*)

## Setting up the Keyboard in Bootloader Mode

To enter bootloader mode, CH552G require connect pin P3.6 to vcc with a 10K pull-up resistor. To do this:
- Short the R12 on the bottom of the board and connect the board to your PC.
  ![Short](img/short.jpeg?raw=true)
- You can now proceed to flash the firmware.
- Once the firmware is successfully flashed, to *return to bootloader mode, reconnect the USB interface while either pressing the encoder button or in running mode simultaneously press all the buttons*.

```C
  // Go in bootloader more if connected with encoder button pressed
  if (!digitalRead(PIN_BTN_ENC))
  {
    NEO_writeHue(0, NEO_CYAN, NEO_BRIGHT_KEYS); // set led1 to cyan
    NEO_writeHue(1, NEO_BLUE, NEO_BRIGHT_KEYS); // set led2 to blue
    NEO_writeHue(2, NEO_MAG, NEO_BRIGHT_KEYS); //  set led3 to magenta
    NEO_update();                              // update pixels
    BOOT_now();     // jump to bootloader
  }
```



# Firmware feature

This firmware as can setup keyboard in different configuration.
Edit configuration.cpp to change it
To change configuration keep press rotary encoder and change configuration.

In this case only one configuration provided, you can change it for any needs
Current configuration for Android HU & CarPlay
```C
#include "configuration.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

const keyboard_configuration_t configurations[NUM_CONFIGURATION] = {
    {
        .button = { // Custom configuration
            [BTN_1] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_TAB}, // TAB
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_2] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_ESC}, // ESC
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_3] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_DOWN_ARROW}, // 
                    .length = 1,
                    .delay = 0
                }
            },
            [ENC_CW] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_RIGHT_ARROW},
                    .length = 1,
                    .delay = 0
                }
            },
            [ENC_CCW] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_LEFT_ARROW},
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_ENC] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_RETURN},
                    .length = 2,
                    .delay = 0
                }
            },
        }
    }
};

```

## Pinout

- BUTTON 1: P16
- BUTTON 2: P17
- BUTTON 3: P11
- BUTTON R: P33
- ENCODER A: P31
- ENCODER B: P30
- LED: P34
- UART1 RX P3.4
- UART1 TX P3.2

## Additional resources

Here are the resources I used for reprogramming the firmware:

- [How to Program a Really Cheap Microcontroller](https://hackaday.com/2019/02/17/how-to-program-a-really-cheap-microcontroller/#more-345535)
- [RGB Macropad Custom Firmware](https://hackaday.io/project/189914-rgb-macropad-custom-firmware)
- [CH552G Macropad Plus](https://oshwlab.com/wagiminator/ch552g-macropad-plus)
- [ch554_sdcc on GitHub](https://github.com/Blinkinlabs/ch554_sdcc)
- [ch55xduino on GitHub](https://github.com/DeqingSun/ch55xduino)
- [CH552G Product Page](https://www.esclabs.in/product/ch552g-8-bit-usb-device-microcontroller/)
- [LCSC Product Page](https://www.lcsc.com/product-detail/Microcontroller-Units-MCUs-MPUs-SOCs_WCH-Jiangsu-Qin-Heng-CH552G_C111292.html?utm_source=digipart&utm_medium=cpc&utm_campaign=CH552G)
- [CH552G Datasheet](http://www.wch-ic.com/downloads/file/309.html)


# License
![license.png](https://i.creativecommons.org/l/by-sa/3.0/88x31.png)

This work is licensed under Creative Commons Attribution-ShareAlike 3.0 Unported License. 
(http://creativecommons.org/licenses/by-sa/3.0/)
