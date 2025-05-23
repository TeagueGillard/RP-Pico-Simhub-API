#ifndef __SHSHAKEITBASE_H__
#define __SHSHAKEITBASE_H__

#include <Arduino.h>
#define SHShakeitBaseSafetyDelay 1000

class FansBase {
private:
	unsigned long lastRead = 0;

public:
	virtual uint8_t motorCount() = 0;

	virtual void safetyStop() {
		uint8_t fansCount = motorCount();
		for (int m = 0; m < fansCount; m++) {
			setMotorOutput(m, 0);
		}
	}

	void safetyCheck() {
		if (millis() - lastRead > SHShakeitBaseSafetyDelay && lastRead > 0) {
			safetyStop();
			lastRead = 0;
		}
	}

	void setFans(uint16_t* values) {
		uint8_t fansCount = motorCount();

		for (int motorIdx = 0; motorIdx < fansCount; motorIdx++) 
		{
			
			uint16_t value = values[motorIdx];
		
			setMotorOutput(motorIdx, value);
		}
		lastRead = millis();
	}

protected:
	virtual void setMotorOutput(uint8_t motorIdx, uint16_t value) = 0;
};

#endif