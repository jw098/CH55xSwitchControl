
#include "src/CH55xSwitchControl.h"


void setup() {
  USBInit();

  pushButtonLoop(BUTTON_B, 500, 5);

}

void loop() {
  pushButton(BUTTON_B, 100);
}