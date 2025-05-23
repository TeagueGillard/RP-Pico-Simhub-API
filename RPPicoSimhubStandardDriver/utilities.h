#ifndef __SHUTILITIES__
#define __SHUTILITIES__

#if defined(ENABLE_UPLOAD_PROTECTION) && ENABLE_UPLOAD_PROTECTION == 1
#include <avr/wdt.h>
#endif

bool uploadUnlocked = 0;

/// <summary>
/// Pretects the pro micro from anwanted upload, it can be unlocked by a physical reset, or the "unloc" command.
/// </summary>
void protectUpload() {
#if defined(ENABLE_UPLOAD_PROTECTION) && ENABLE_UPLOAD_PROTECTION == 1
	if (ENABLE_UPLOAD_PROTECTION && !uploadUnlocked) {
		if (millis() > UPLOAD_AVAILABLE_DELAY) {
			wdt_disable();
			wdt_reset();
		}
	}
#endif
}

/// <summary>
/// Unlock upload protection.
/// </summary>
void unlockUpload() {
	uploadUnlocked = true;
	Serial.println("Upload unlocked");
}

/// <summary>
/// Wait for data to be available and reads one byte.
/// </summary>
/// <returns></returns>
int WaitAndReadOneByte() {
	while (!Serial.available()) {}
	return Serial.read();
}

// Reads leds end of message
bool readValidationSequence() {
	// 3 bytes end of message, it must be (0xFF)(0xFE)(0xFD) to be taken into account, it's a super simple way to be sure we reached the correct end.
	bool valid = true;
	for (int i = 0; i < 3; i++) {
		valid = valid && (WaitAndReadOneByte() == 0xFF - i);
	}
	return valid;
}

byte readByte() {
	while (!Serial.available()) {}
	return Serial.read();
}

#define read16Bits() ((uint16_t)(((uint16_t)readByte()) << 8) + (uint16_t)readByte())
#define read32Bits() ((uint32_t)( (((uint32_t)read16Bits() )<< 16) + (uint32_t)read16Bits() )   )

#endif // !__SHUTILITIES__