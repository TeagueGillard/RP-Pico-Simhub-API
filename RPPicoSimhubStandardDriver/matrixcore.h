//-------------------------
// ------- DEFINES & Vars
//-------------------------

#include "utilities.h"
#include "utilitiesrgb.h"

/// Simple rotation index remapping
int remapIndex(int index, int rotation) {
  int row = index / 8; // Calculate the row number (0-7)
  int col = index % 8; // Calculate the column number (0-7)
  int newIndex = 0;

  // Handle different rotation cases
  switch (rotation) {
    case 90:
      // For 90 degrees: New row becomes old column, and new column becomes (7 - old row)
      newIndex = col * 8 + (7 - row);
      break;

    case 180:
      // For 180 degrees: New row becomes (7 - old row), and new column becomes (7 - old column)
      newIndex = (7 - row) * 8 + (7 - col);
      break;

    case 270:
      // For 270 degrees: New row becomes (7 - old column), and new column becomes old row
      newIndex = (7 - col) * 8 + row;
      break;

    default:
      // No rotation, return the original index
      newIndex = index;
      break;
  }

  return newIndex;
}

/// <summary>
/// Read matrix data
/// </summary>
/// <param name="stripIndex">Pointer to the matrix RGB strip.</param>
/// <param name="layout">Layout</param>
void readMatrixRGBData(int stripIndex, int layout, int maxBrightness) {
	int ledcount = 8 * 8;

	byte r, g, b;
	for (int i = 0; i < ledcount; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

		int ledNumber = remapIndex(i, MATRIX_ROTATION);

		if (layout == MATRIX_SERPENTINE || layout == MATRIX_REVERSESERPENTINE) {
			int Y = ledNumber / 8;
			int X = ledNumber % 8;
			if (layout == MATRIX_SERPENTINE) {
				if (!(Y % 2)) {
					X = 7 - X;
				}
			}
			else if (layout == MATRIX_REVERSESERPENTINE) {
				if ((Y % 2)) {
					X = 7 - X;
				}
			}
			ledNumber = Y * 8 + X;
		}
		setRGB(0, ledNumber, maxBrightness, r, g, b);
	}
}



/// <summary>
/// Read matrix data from serial port.
/// </summary>
void readMatrix() {
#if(MATRIX_ENABLED > 0)
	readMatrixRGBData(led_matrix, MATRIX_LAYOUT, MATRIX_MAX_BRIGHTNESS);
	if (readValidationSequence()) {
		led_stripMatrix.show();
	}
#endif
}


/// <summary>
/// Setup for the Matrix.
/// </summary>
void setupMatrix() {

#if(MATRIX_ENABLED > 0)
  Adafruit_NeoPixel led_stripMatrix(64, MATRIX_DATAPIN, NEO_GRB + NEO_KHZ800);
	led_stripMatrix.begin();
#endif
}
