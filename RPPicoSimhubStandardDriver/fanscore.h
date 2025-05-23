//-------------------------
// ------- DEFINES & Vars
//-------------------------
#include "utilities.h"

#if(FANS_CONTROLLER == FANS_25KHZPWM)

/// PWM FANS
/// **********
#define VALID_FANS
#include "FansPWMFans.h"
FansPWMFans fansController;

void setupFans() {
	fansController.begin(PWMFANS_COUNT, PWMFANS_PIN_O1, PWMFANS_PIN_O2, PWMFANS_PIN_O3);
	fansController.setMin(PWMFANS_MIN_OUTPUT_O1, PWMFANS_MIN_OUTPUT_O2, PWMFANS_MIN_OUTPUT_O3);
	fansController.setMax(PWMFANS_MAX_OUTPUT_O1, PWMFANS_MAX_OUTPUT_O2, PWMFANS_MAX_OUTPUT_O3);
	fansController.setRelays(PWMFANS_RELAY_PIN_01, PWMFANS_RELAY_PIN_02, PWMFANS_RELAY_PIN_03,
		PWMFANS_RELAY_DELAY_01, PWMFANS_RELAY_DELAY_02, PWMFANS_RELAY_DELAY_03,
		PWMFANS_RELAY_REVERSELOGIC_01, PWMFANS_RELAY_REVERSELOGIC_02, PWMFANS_RELAY_REVERSELOGIC_03
	);
}

#elif(FANS_CONTROLLER == FANS_CUSTOM)

/// CUSTOM FANS
/// **********
#define VALID_FANS
#include "FansCustom.h"
FansCustom fansController;

void setupFans() {
	fansController.begin();
}

#else

/// NO FANS
/// **********
void setupFans() {
}

#endif

#ifdef VALID_FANS
uint16_t fansBuffer[8];
#endif

int getFansCount() {
#ifdef VALID_FANS
	return fansController.motorCount();
#else
	return 0;
#endif
}


void readFans() {
#ifdef VALID_FANS
	int motorsCount = fansController.motorCount();
	for (int i = 0; i < getFansCount(); i++) {
		fansBuffer[i] = read16Bits();
	}
	if (readValidationSequence()) {
		fansController.setFans(fansBuffer);
	}
#endif
}

void fansSafetyCheck() {
#ifdef VALID_FANS
	return fansController.safetyCheck();
#endif
}
