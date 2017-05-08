//TODO: Import ecs library somehow
#include <cmath>
int lineWhiteThreshold = 127;

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

//=======================Quadrant One=======================

//=======================Quadrant Two=======================

//=======================Quadrant Three=======================

//=======================Quadrant Four=======================

int main() {
	init();
	updateWhiteThreshold();
}
