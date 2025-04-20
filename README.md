# CH55xSwitchControl

This is an Arduino IDE library for automating the Nintendo Switch using the inexpensive Chinese-made CH552 microcontroller.

<img src="https://user-images.githubusercontent.com/21293572/202479479-fff6e791-59a1-463b-bc7a-f67b4cd12cca.jpg" width="50%">

## What you need
**Hardware**
- CH552 microcontroller board
- A microcontroller board with USB-to-serial conversion function is sold at [Booth](https://bzl.booth.pm/items/4326008).
- A USB cable to connect the microcontroller board to the Nintendo Switch

**Software**
- Arduino IDE

## How to use
### Installing WCHISPTool

Download the installer from the URL below and install WCHISPTool.
After installation, launch WCHISPTool and the CH552 driver will be installed.
https://www.wch-ic.com/downloads/WCHISPTool_Setup_exe.html


link to driver only: https://www.wch-ic.com/downloads/CH372DRV_EXE.html

### Installing the library
While in Arduino IDE, open the Library Manager. Search for this library name "CH55xSwitchControl" and install it.

###  Installing ch55xduino
This is required to use the CH552 microcontroller in Arduino IDE.
1. Open File → Preferences and add the following URL to "Additional Boards Manager URLs".
~~~
https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json
~~~

2. Open Tools → Board → Board Manager, search for "ch55xduino" in the search box, and install it.

3. Select CH552 from Tools → Board.

4. Select "USER CODE w/ 148B USB ram" from Tools → USB Settings.

### Compiling with Arduino IDE
- Ensure ch55xduino is installed and Arduino IDE is configured as above.
- Click Sketch -> Export Compiled Binary. A build folder will now be created next to the .ino file. Inside the build folder is the .hex file.

### Flashing to the CH552

**The board must first be in bootloader mode:**
- Unplug the CH552 device from your computer
- Hold the BOOT button while connecting the board to your PC, using the USB-A connector on the Ch552. You can then release the BOOT button.
- see for more info:
  - https://github.com/wagiminator/CH552-MacroPad-plus/blob/main/README.md
  - https://github.com/DeqingSun/ch55xduino

**Flashing using Arduino IDE**
- While the board is connected and in bootloader mode (see above), press the upload button in Arduino IDE

**Flashing using WCHISPStudio**
- ensure WCHISPTool has been installed (see above)
- Click E8051 USB MCUs (CH54x/CH55x) in the left sidebar
- Under `Chip Option`:
  - Chip Series: CH55x
  - Chip Model CH552
  - Dnld Port: USB
  - Dev List: CH55x---#1 device (or something similar)
    - if you don't see your device listed, make sure you're in bootloader mode (i.e. unplug the CH552 board, and replug it while holding the BOOT button)
- Under `Download File`
  - Click the `...` next to `Object File1`: select the .hex file that you generated (see section on compiling above). Ensure adjacent box is checked.
- Click `Download`. When the progress bar is complete, the firmware should be flashed to the device.

### Input

Please write the following at the beginning of the file you want to use the library in.

~~~
#include <CH55xSwitchControl.h>
~~~
## Command List
### Button
- Command to press a button
- `pushButton(uint16_t button, uint32_t delay_time_msec)`
- button: Button to press
- delay_time_msec: Wait time after pressing the button (1 second = 1000)
- `pushButtonLoop(uint16_t button, uint32_t delay_time_msec, uint16_t loop_num)`
- button: Button to press
- delay_time_msec: Wait time after pressing the button (1 second = 1000)
- loop_num: Number of times to press the button
- Example of use
`
pushButton(BUTTON_A, 500); // Wait 0.5 seconds after pressing the A button
pushButtonLoop(BUTTON_B, 3000, 10); // Press the B button every 3 seconds, repeating 10 times
```

- Command to hold down a button

- `pushButtonContinuous(uint16_t button, uint32_t pushing_time_msec)`

- button: Button to hold down

- pushing_time_msec: Length of time to hold down the button (1 second = 1000)

- Usage example

```
pushButtonContinuous(BUTTON_L, 2000); // Press and hold the L button for 2 seconds, then release it
pushButtonContinuous(BUTTON_CAPTURE, 1500); // Press and hold the capture button for 1.5 seconds, then release it
```

- Command to directly control the input state of a button (for advanced users)

- `pressButton(uint16_t button)`

- button: Button to press

- `releaseButton(uint16_t button)`

- button: button to release

- `BUTTON` definition list

```
BUTTON_NONE
BUTTON_Y
BUTTON_B
BUTTON_A
BUTTON_X
BUTTON_L
BUTTON_R
BUTTON_ZL
BUTTON_ZR
BUTTON_MINUS
BUTTON_PLUS
BUTTON_LCLICK
BUTTON_RCLICK
BUTTON_HOME
BUTTON_CAPTURE
```

### D-pad (directional buttons)

- Command to press D-pad (directional buttons)

- `pushHatButton(uint8_t hat, uint32_t delay_time_msec);`

- hat: D-pad button to press

- delay_time_msec: Wait time after pressing button (1 second = 1000)

- `pushHatButtonLoop(uint8_t hat, uint32_t delay_time_msec, uint16_t loop_num);`

- hat: D-pad button to press
- delay_time_msec: Wait time after pressing the button (1 second = 1000)
- loop_num: Number of times to press the button

- Usage example

```
pushHatButton(HAT_LEFT, 1000); // Wait 1 second after pressing the left key
pushHatButtonLoop(HAT_DOWN, 25, 5); // Press the down key every 0.25 seconds, repeating this 5 times
```

- Command to press and hold the D-pad (directional button)

- `pushHatButtonContinuous(uint8_t hat, uint32_t pushing_time_msec);`

- hat: D-pad button to hold down
- pushing_time_msec: Length of time to press the button (1 second = 1000)

- Usage examples

```
pushHatButtonContinuous(HAT_RIGHT, 5000); // Press and hold the right key for 5 seconds, then release
pushHatButtonContinuous(HAT_UP_LEFT, 2500); // Press and hold the D-pad to the upper left for 2.5 seconds, then release
```

- Commands to directly control the input state of the D-pad (directional buttons) (for advanced users)

- `pressHatButton(uint8_t hat)`

- hat: D-pad button to press

- `releaseHatButton(uint8_t hat)`

- hat: D-pad button to release

- `HAT` definition list

```
HAT_UP
HAT_UP_RIGHT
HAT_RIGHT
HAT_DOWN_RIGHT
HAT_DOWN
HAT_DOWN_LEFT
HAT_LEFT
HAT_UP_LEFT
HAT_CENTER
```

### Stick

The stick coordinates are specified as values ​​from -100 to 100, with 0 as the base point.

- Commands for controlling the stick

- `tiltJoystick(uint8_t lx_per, uint8_t ly_per, uint8_t rx_per, uint8_t ry_per, uint32_t tilt_time_msec);`

- lx_per: L stick tilt amount in X direction
- ly_per: L stick tilt amount in Y direction
- rx_per: R stick tilt amount in X direction
- ry_per: R stick tilt amount in Y direction
- tilt_time_msec: Time to keep the stick tilted

- Usage example

```
tiltJoystick(-100, 0, 0, 0, 5000); // Tilt the L stick to the left for 5 seconds
tiltJoystick(0, 100, 0, 0, 15000); // Tilt the L stick down for 15 seconds
tiltJoystick(0, 0, 100, 100, 10000); // Tilt the R stick down and to the right for 10 seconds
```

- Commands to directly control the input state of the stick (for advanced users)

- `setStickTiltRatio(uint8_t lx_per, uint8_t ly_per, uint8_t rx_per, uint8_t ry_per)`

- lx_per: L stick tilt amount in the X direction
- ly_per: L stick tilt amount in the Y direction
- rx_per: R stick tilt amount in the X direction
- ry_per: R stick tilt amount in the Y direction