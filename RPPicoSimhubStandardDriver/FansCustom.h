#ifndef __CUSTOMFANS_H__
#define __CUSTOMFANS_H__

#include <Arduino.h>
#include "FansBase.h"

class FansCustom : public FansBase {
private:

	// How many outputs are available, up to 8
	byte enabledOutputs = 2;
public:

	uint8_t motorCount() {
		return enabledOutputs;
	}

	// Called when the idle timeout is triggered. Fans will set to 0 using setMotorOutput. 
	void safetyStop() override {
		FansBase::safetyStop();
		// do any extra stopping (relays, power etc ... after it)
	}

	void begin() {
		// Initialize your fans here if needed
	}

protected:

	void setMotorOutput(uint8_t motorIdx, uint16_t value) {
		// Implement your fan control, values are unsigned 16bits integers
	}
};

#endif