#include <stdio.h>
#include <math.h>
#include "E101.h"

// Written by mathiasronimus

int lineWhiteThreshold = 127;
int minWhiteToSeeLine = 12800;
double kp = 0.5; //Will need to adjust this

//=======================General Functions=======================
void setSpeed(int left, int right) {
	set_motor(0, left);
	set_motor(1, right);
}

//Updates white threshold to account for variations in lighting
void updateWhiteThreshold() {
	take_picture();
	int totalWhite = 0;
	//Loop through whole image
	for (var r = 0; r < 240; r++) {
		for (var c = 0; c < 320; c++) {
			totalWhite += get_pixel(r, c, 3);
		}
	}
	//Set to average of all pixels
	lineWhiteThreshold = totalWhite / 76800;
}

//rowStart and rowEnd are inclusive. Remember to take picture before using.
double getLineErrorSignal(int rowStart, int rowEnd) {
	int error = 0; //If negative, go left, if positive, go right
	for (int r = rowStart; r <= rowEnd; r++) {
		//Loop through the rows we are looking at
		for (int c = 0; c < 320; c++) {
			//Loop through the columns in the row
			if (get_pixel(r, c, 3) > lineWhiteThreshold) {
				//This pixel is white
				error += c - 160;
			}
		}
	}
	//Return the Average error of the rows
	return (double) error / (rowEnd - rowStart + 1);
}

//Returns number of white pixels in image. Call take picture first.
int numWhiteInImg() {
	int numWhite;
	for (int r = 0; r < 240; r++) {
		for (int c = 0; c < 320, c++) {
			//Loop through image
			if (get_pixel(r, c, 3) > lineWhiteThreshold) {
				//Pixel is white
				numWhite++;
			}
		}
	}
	return numWhite;
}

bool canSeeLine() {
	if (numWhiteInImg() > minWhiteToSeeLine) return true;
	else return false;
}

//=======================Quadrant One=======================

void quadOneLoop() {
	updateWhiteThreshold();
	bool active = true;
	double errorSignal;
	while(active) {
		take_picture();	
		if (canSeeLine()) {
			//Robot is on track	
			errorSignal = getLineErrorSignal(110, 130);
			setSpeed(127 + errorSignal*kp, 127 - errorSignal*kp);
		} else {
			//Robot is not on track	
		}
	}
}

//=======================Quadrant Two=======================

//=======================Quadrant Three=======================

//=======================Quadrant Four=======================

// Written by finn-nz
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
    };
    else {
      s = 0;
    };
    sum = sum + (i - 160) * s;
  };
  proportional_signal = sum * kp;
};

int get_ir_reading() {
  int avg = 0;
  for (int i = 0; i < 5; i++) {
    avg = avg + get_adc_reading(ir_sensor_1);
  };
  return(avg / 5);
};

int main() {
  init();
<<<<<<< HEAD
  updateWhiteThreshold();
};
=======
  quadOneLoop();
}
>>>>>>> d4eac23b005b8e8b468d939f269322edd7ea6d28
