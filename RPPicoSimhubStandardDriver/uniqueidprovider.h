
#include <EEPROM.h>

#define uniqueid_sig1  0x55
#define uniqueid_sig2  0x58
#define uniqueid_sigstart_length 2
#define uniqueid_length 20

int GetStorageStart() {
	return EEPROM.length() - uniqueid_length - uniqueid_sigstart_length - 1;
}

String GetUniqueId() {
	int storageStart = GetStorageStart();

	if (EEPROM[storageStart] == uniqueid_sig1
		&& EEPROM[storageStart + 1] == uniqueid_sig2) {

		char data[uniqueid_length + 1];

		for (int i = 0; i < uniqueid_length; i++)
		{
			data[i] = EEPROM.read(storageStart + uniqueid_sigstart_length + i);
		}
		data[uniqueid_length] = '\0';
		return String(data);
	}
	else {
		EEPROM[storageStart] = uniqueid_sig1;
		EEPROM[storageStart + 1] = uniqueid_sig2;
		randomSeed(analogRead(A1));
		for (int i = 0; i < uniqueid_length; i++) {
			EEPROM[storageStart + uniqueid_sigstart_length + i] = random('A', 'Z');
		}
		return GetUniqueId();
	}
}

void ResetUniqueId() {
	EEPROM[GetStorageStart()] = uniqueid_sig1 + 1;
}