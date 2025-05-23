#ifndef __SHUTILITIESRGB__
#define __SHUTILITIESRGB__

/// <summary>
/// Set RGB  data with brightness
/// </summary>
/// <param name="stripIndex"></param>
/// <param name="ledIndex"></param>
/// <param name="maxBrightness"></param>
/// <param name="r"></param>
/// <param name="g"></param>
/// <param name="b"></param>
void setRGB(int stripIndex, int ledIndex, int maxBrightness, uint8_t r, uint8_t g, uint8_t b) {
  #if(MATRIX_ENABLED > 0 && stripIndex == 0)
	  led_stripMatrix.setPixelColor(ledIndex, (uint8_t)((int)r * maxBrightness / 255), (uint8_t)((int)g * maxBrightness / 255), (uint8_t)((int)b * maxBrightness / 255));
  #endif

  #if(STRIP1_RGBLEDCOUNT > 0 && stripIndex == 1)
	  led_strip1.setPixelColor(ledIndex, (uint8_t)((int)r * maxBrightness / 255), (uint8_t)((int)g * maxBrightness / 255), (uint8_t)((int)b * maxBrightness / 255));
  #endif

  #if(STRIP2_RGBLEDCOUNT > 0 && stripIndex == 2)
	  led_strip2.setPixelColor(ledIndex, (uint8_t)((int)r * maxBrightness / 255), (uint8_t)((int)g * maxBrightness / 255), (uint8_t)((int)b * maxBrightness / 255));
  #endif

  #if(STRIP3_RGBLEDCOUNT > 0 && stripIndex == 3)
	  led_strip3.setPixelColor(ledIndex, (uint8_t)((int)r * maxBrightness / 255), (uint8_t)((int)g * maxBrightness / 255), (uint8_t)((int)b * maxBrightness / 255));
  #endif

  #if(STRIP4_RGBLEDCOUNT > 0 && stripIndex == 4)
	  led_strip4.setPixelColor(ledIndex, (uint8_t)((int)r * maxBrightness / 255), (uint8_t)((int)g * maxBrightness / 255), (uint8_t)((int)b * maxBrightness / 255));
  #endif
}
#endif // !__SHUTILITIES__