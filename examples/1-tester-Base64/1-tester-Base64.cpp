#include "Particle.h"

#include "Base64RK.h"

int base64Handler(String data);
int hexHandler(String data);
int textHandler(String data);

void setup() {
	Serial.begin(9600);
	Particle.function("base64", base64Handler);
	Particle.function("hex", hexHandler);
	Particle.function("text", textHandler);
}

void loop() {
}

int base64Handler(String data) {
	bool success = false;

	size_t bufLen = data.length();
	uint8_t *buf = new uint8_t[Base64::getMaxDecodedSize(bufLen)];
	if (buf) {
		success = Base64::decode(data, buf, bufLen);

		if (success) {
			char *hex = new char[bufLen * 2 + 1];
			if (hex) {
				for(size_t ii = 0; ii < bufLen; ii++) {
					sprintf(&hex[ii * 2], "%02x", buf[ii]);
				}

				Particle.publish("base64->hex", hex, PRIVATE);
				Serial.printlnf("base64->hex %s", hex);

				delete[] hex;
			}
			else {
				success = false;
			}
		}
		delete[] buf;
	}

	return success;
}

int hexHandler(String data) {
	// 64 is the largest possible function data, converted from hex makes up to 32 bytes of binary data
	uint8_t buf[32];
	size_t bufLen = 0;

	// Convert hex bytes into binary data
	for(size_t ii = 0; ii < data.length(); ii += 2) {
		char hex[3];
		hex[0] = data[ii];
		hex[1] = data[ii + 1];
		hex[2] = 0;
		int value;
		if (sscanf(hex, "%02x", &value) == 1) {
			buf[bufLen++] = (uint8_t) value;
		}
	}

	// 32 bytes of binary data can make up to 44 bytes of base64 data, plus a null terminator
	char encoded[45];
	size_t encodedLen = sizeof(encoded);

	// Convert the hex data to Base64
	bool success = Base64::encode(buf, bufLen, encoded, encodedLen, true);
	if (success) {
		Particle.publish("hex->base64", encoded, PRIVATE);
		Serial.printlnf("hex->base64 %s", encoded);
	}

	return success;
}

int textHandler(String data) {
	String encoded = Base64::encodeToString((const uint8_t *)data.c_str(), data.length());
	Particle.publish("text->base64", encoded, PRIVATE);
	Serial.printlnf("text->base64 %s", encoded.c_str());
	return 1;
}

