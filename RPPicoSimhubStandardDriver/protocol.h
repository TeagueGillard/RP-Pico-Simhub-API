#include "utilities.h"
#include "ledscore.h"
#include "matrixcore.h"
#include "fanscore.h"

#include "uniqueidprovider.h"
#include "enums.h"

#define PROTOCOLVERSION "SIMHUB_1.2"

void (*customSerialDataCallback)(int) = 0;

int messageend = 0;
String command = "";

/// <summary>
/// Read commands from serial port.
/// </summary>
void processCommands() {
	// Protects unwanted upload.
	protectUpload();

	// If no fans activity, stop them.
	fansSafetyCheck();

	// Read data
	if (Serial.available()) {
		char c = (char)Serial.read();

		if (messageend < 6) {
			if (c == (char)0xFF) {
				messageend++;
			}
			else {
				messageend = 0;
			}
		}

		if (messageend >= 3 && c != (char)(0xff)) {
			command += c;

			while (command.length() < 5) {
				c = WaitAndReadOneByte();
				command += c;
			}

			// *** DEVICE GENERAL INFORMATIONS  ***
			
			// Get protocol version
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)proto
			if (command == F("proto")) {
				Serial.println(F(PROTOCOLVERSION));
			}

			// Get device name
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)dname
			else if (command == F("dname")) {
				Serial.println(F(DEVICE_NAME));
			}

			// Get brand name
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)dname
			else if (command == F("bname")) {
				Serial.println(F(DEVICE_BRAND));
			}

			// Get device picture
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)dname
			else if (command == F("dpict")) {
				Serial.println(F(DEVICE_PICTURE_URL));
			}

			// Get device auto detect state
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)dname
			else if (command == F("ddete")) {
				Serial.println((int)DEVICE_AUTODETECT_ALLOWED);
			}

			// Get device type
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)dtype
			else if (command == F("dtype")) {
				Serial.println((int)DEVICE_TYPE);
			}

			// Get upload protection informations
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)ulock
			else if (command == F("ulock")) {
				Serial.print(ENABLE_UPLOAD_PROTECTION);
				Serial.print(",");
				Serial.println(UPLOAD_AVAILABLE_DELAY);
			}

			// *** SERIAL NUMBER  ***

			// Get serial number
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)snumb
			else if (command == F("snumb")) {
				Serial.println(GetUniqueId());
			}

			// Reset serial number
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)snumb
			else if (command == F("rnumb")) {
				ResetUniqueId();
				Serial.println(GetUniqueId());
			}

			// *** LEDS ***

			// Get leds count
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)ledsc
			else if (command == F("ledsc")) {
				Serial.println(STRIP1_RGBLEDCOUNT + STRIP2_RGBLEDCOUNT + STRIP3_RGBLEDCOUNT + STRIP4_RGBLEDCOUNT);
			}

			// Get leds Layout
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)ledsl
			else if (command == F("ledsl")) {
				Serial.println(F(LEDS_LAYOUT));
			}

			// Get default buttons profile colors
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)butdc
			else if (command == F("butdc")) {
				Serial.println(F(DEFAULT_BUTTONS_COLORS));
			}

			// Send leds data (in binary) terminated by (0xFF)(0xFE)(0xFD)
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)sleds(RL1)(GL1)(BL1)(RL2)(GL2)(BL2) .... (0xFF)(0xFE)(0xFD)
			else if (command == F("sleds")) {
				readLeds();
			}

			// *** MATRIX ***

			// Get 8x8 matrix count
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)matxc
			else if (command == F("matxc")) {
				Serial.println(MATRIX_ENABLED > 0 ? 1 : 0);
			}

			// Set 8x8 matrix content
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)sleds(RL1)(GL1)(BL1)(RL2)(GL2)(BL2) .... (0xFF)(0xFE)(0xFD)
			else if (command == F("smatx")) {
				readMatrix();
			}

			// *** FANS ***
			
			// Get fans count
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)fansc
			else if (command == F("fansc")) {
				Serial.println(getFansCount());
			}

			// Set fans values (16bits)
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)sfans(FAN1 MSB)(FAN1 LSB)(FAN2 MSB)(FAN2 LSB)(FAN3 MSB)(FAN3 LSB) .... (0xFF)(0xFE)(0xFD)
			else if (command == F("sfans")) {
				readFans();
			}

			// Vendor message
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)vendo
			else if (command == F("vendo")) {
				int messageLength = ((int)WaitAndReadOneByte() << 8) + (int)WaitAndReadOneByte();
				if (customSerialDataCallback != 0) {
					customSerialDataCallback(messageLength);
				}
			}

			// Unlock upload
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)unloc
			else if (command == F("unloc")) {
				unlockUpload();
			}

			command = "";
			messageend = 0;
		}
	}
}