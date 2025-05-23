#ifndef __SHPWMFANS_H__
#define __SHPWMFANS_H__

#include <Arduino.h>
#include "FansBase.h"
#include "src/TimerOne/TimerOne.h"

class FansPWMFans : public FansBase {
private:

	byte pins[3];
	uint16_t mins[3];
	uint16_t maxs[3];

	int relays[3];
	unsigned long offSince[3];
	unsigned long offDelay[3] = { 2000,2000,2000 };
	byte reverseRelayLogic[3] = { 0,0,0 };
	byte enabledOutputs;
public:

	uint8_t motorCount() {
		return enabledOutputs;
	}

	void safetyStop() override {
		FansBase::safetyStop();

		for (int i = 0; i < enabledOutputs; i++) {
			if (relays[i] > 0) {
				SetRelayState(i, false);
			}
		}
	}

	void begin(byte pEnabledOutputs, byte pPin01, byte pPin02, byte	pPin03) {
		Timer1.initialize(40);

		pins[0] = pPin01;
		pins[1] = pPin02;
		pins[2] = pPin03;
		enabledOutputs = pEnabledOutputs;
		for (int i = 0; i < pEnabledOutputs; i++) {
			Timer1.pwm(pins[i], 0);
		}
	}

	void setMin(uint16_t pMin01, uint16_t pMin02, uint16_t	pMin03) {
		mins[0] = pMin01;
		mins[1] = pMin02;
		mins[2] = pMin03;
	}

	void setMax(uint16_t pMax01, uint16_t pMax02, uint16_t	pMax03) {
		maxs[0] = pMax01;
		maxs[1] = pMax02;
		maxs[2] = pMax03;
	}

	void setRelays(
		// PINS
		int r01, int r02, int r03,
		// DELAYS
		int d01, int d02, int d03,
		// Reverse relay logic
		bool l01, bool l02, bool l03) {
		relays[0] = r01;
		relays[1] = r02;
		relays[2] = r03;

		offDelay[0] = d01;
		offDelay[1] = d02;
		offDelay[2] = d03;

		reverseRelayLogic[0] = l01;
		reverseRelayLogic[1] = l02;
		reverseRelayLogic[2] = l03;
		for (int i = 0; i < enabledOutputs; i++) {
			if (relays[i] >= 0) {
				pinMode(relays[i], OUTPUT);
				SetRelayState(i, false);
			}
			offSince[i] = 0;
		}
	}

protected:

	void SetRelayState(int relayIdx, bool state) {
		int relayPin = relays[relayIdx];
		if (relayPin >= 0) {
			if (!state) {
				digitalWrite(relayPin, reverseRelayLogic[relayIdx] ? HIGH : LOW);
			}
			else {
				digitalWrite(relayPin, reverseRelayLogic[relayIdx] ? LOW : HIGH);
			}
		}
	}

	void setMotorOutput(uint8_t motorIdx, uint16_t value) {
		double value2 = (double)value / (double)UINT16_MAX * 1023.0;

		if (value2 < mins[motorIdx]) {
			value2 = 0;
		}
		else {
			value2 = (value2) / 1023.0 * (double)maxs[motorIdx];
		}

		Timer1.pwm(pins[motorIdx], (unsigned int)value2);

		if (relays[motorIdx] >= 0) {
			if (value2 > 0) {
				SetRelayState(motorIdx, true);
				offSince[motorIdx] = 0;
			}
			else {
				if (offSince[motorIdx] == 0) {
					offSince[motorIdx] = millis();
				}

				if ((millis() - offSince[motorIdx]) > offDelay[motorIdx]) {
					SetRelayState(motorIdx, false);
					offSince[motorIdx] = 0;
				}
			}
		}
	}
};

#endif