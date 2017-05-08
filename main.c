#include <stdio.h>
#include "E101.h"

int image_analysis() {
  take_picture();
  int sum = 0;
  float kp = 0; //Change this value
  int proportional_signal = 0;
  int w, s;
  for (int i = 0; i < 320, i++) {
    w = get_pixel(i, 120, 3);
    if (w > 127) {
      s = 1;
    }
    else {
      s = 0;
    }
    sum = sum + (i - 160) * s;
  }
  proportional_signal = sum * kp;
}

int main() {
  init();
}
