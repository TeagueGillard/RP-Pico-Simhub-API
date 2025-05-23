
//-------------------------
// ------- DEFINES & Vars
//-------------------------
#include <Adafruit_NeoPixel.h>
#include "utilities.h"
#include "utilitiesrgb.h"

#if(STRIP1_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip1(STRIP1_RGBLEDCOUNT, STRIP1_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

#if(STRIP2_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip2(STRIP2_RGBLEDCOUNT, STRIP2_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

#if(STRIP3_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip3(STRIP3_RGBLEDCOUNT, STRIP3_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

#if(STRIP4_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip4(STRIP4_RGBLEDCOUNT, STRIP4_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

/// <summary>
/// Read rgb strip data
/// </summary>
/// <param name="stripIndex">Which RGB strip is targeted.</param>
/// <param name="ledcount">How many leds the strip has.</param>
/// <param name="rightToLeft">Should the strip be fed from right to left.</param>
void readStrip(int stripIndex, int ledcount, bool rightToLeft, int maxBrightness) {
	byte r, g, b;
	for (int i = 0; i < ledcount; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();
		if (rightToLeft) {
			setRGB(stripIndex, ledcount - 1 - i, maxBrightness, r, g, b);
		}
		else {
			setRGB(stripIndex, i, maxBrightness, r, g, b);
		}
	}
}

/// <summary>
/// Read leds data from serial port.
/// </summary>
void readLeds() {
#if(STRIP1_RGBLEDCOUNT > 0)
	readStrip(1, STRIP1_RGBLEDCOUNT, STRIP1_RIGHTTOLEFT, STRIP1_MAX_BRIGHTNESS);
#endif

#if(STRIP2_RGBLEDCOUNT > 0)
	readStrip(2, STRIP2_RGBLEDCOUNT, STRIP2_RIGHTTOLEFT, STRIP2_MAX_BRIGHTNESS);
#endif

#if(STRIP3_RGBLEDCOUNT > 0)
	readStrip(3, STRIP3_RGBLEDCOUNT, STRIP3_RIGHTTOLEFT, STRIP3_MAX_BRIGHTNESS);
#endif

#if(STRIP4_RGBLEDCOUNT > 0)
	readStrip(4, STRIP4_RGBLEDCOUNT, STRIP4_RIGHTTOLEFT, STRIP4_MAX_BRIGHTNESS);
#endif

	if (readValidationSequence()) {
    #if(STRIP1_RGBLEDCOUNT > 0)
        led_strip1.show();
    #endif
    #if(STRIP2_RGBLEDCOUNT > 0)
        led_strip2.show();
    #endif
    #if(STRIP3_RGBLEDCOUNT > 0)
        led_strip3.show();
    #endif
    #if(STRIP4_RGBLEDCOUNT > 0)
        led_strip4.show();
    #endif
	}
}

/// <summary>
/// Setup for the LEDs.
/// </summary>
void setupLeds() {

#if(STRIP1_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip1(STRIP1_RGBLEDCOUNT, STRIP1_DATAPIN, NEO_GRB + NEO_KHZ800);
  led_strip1.begin();
#endif

#if(STRIP2_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip2(STRIP2_RGBLEDCOUNT, STRIP2_DATAPIN, NEO_GRB + NEO_KHZ800);
  led_strip2.begin();
#endif

#if(STRIP3_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip3(STRIP3_RGBLEDCOUNT, STRIP3_DATAPIN, NEO_GRB + NEO_KHZ800);
  led_strip3.begin();
#endif

#if(STRIP4_RGBLEDCOUNT > 0)
  Adafruit_NeoPixel led_strip4(STRIP4_RGBLEDCOUNT, STRIP4_DATAPIN, NEO_GRB + NEO_KHZ800);
  led_strip4.begin();
#endif


}
