#include <stdio.h>
#include <signal.h>
#include <math.h>
#include "E101.h"

// Written by mathiasronimus

int lineWhiteThreshold = 127;
int minWhiteToSeeLine = 12800;
float kp = 0.1; //Will need to adjust this
int loopDelay = 500000;
int baseSpeed = 64;

//=======================General Functions=======================
void setSpeed(int left, int right) {
	if (left > 255) left = 255;
	if (left < -255) left = -255;
	if (right > 255) right = 255;
	if (right < -255) right = -255;
	set_motor(1, left);
	set_motor(2, right);
}

//Updates white threshold to account for variations in lighting
void updateWhiteThreshold() {
	take_picture();
	int totalWhite = 0;
	//Loop through whole image
	for (int r = 0; r < 240; r++) {
		for (int c = 0; c < 320; c++) {
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
		for (int c = 0; c < 320; c++) {
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

void reverseUntilSeeLine() {
	setSpeed(-50, -50);
	while (!canSeeLine()) {
		take_picture();
		sleep1(0, loopDelay);
	}
	setSpeed(0, 0);
}

void turnUntilSeeLine(bool left) {
	if (left) setSpeed(-100, 100);
	else setSpeed(100, -100);
	while (!canSeeLine()) {
		take_picture();
		sleep1(0, loopDelay);
	}
	setSpeed(0, 0);
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
			setSpeed(baseSpeed + errorSignal*kp, baseSpeed - errorSignal*kp);
		} else {
			//Robot is not on track	
			reverseUntilSeeLine();
		}
		sleep1(0, loopDelay);
	}
}

//=======================Quadrant Two=======================

//=======================Quadrant Three=======================

//=======================Quadrant Four=======================

// Written by finn-nz
void image_analysis() {
  take_picture();
  int sum = 0;
  float kp = 0; //Change this value
  int proportional_signal = 0;
  int w, s;
  for (int i = 0; i < 320; i++) {
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
};

//int get_ir(pin) {
//  int ir = 0;
//  for (int i = 0; i < 5; i++) {
//    ir = ir + get_adc_reading(pin); //Change this
//  }
//  return(ir / 5);
//}

//void check_block(char dir[]) {
//  if (dir[] == "forward") {
//    reading = get_ir(front);
//    if (reading < thresh) {
//      set_motor(0, 0);
//      set_motor(1, 0);
//    }
//  }
//}

int main() {
  // Register signals
  signal(SIGINT, stop);
  
  init();
  quadOneLoop();
}
