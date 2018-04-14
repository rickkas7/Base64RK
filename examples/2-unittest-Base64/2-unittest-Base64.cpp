#include "Base64RK.h"

#define DEBUG_PRINT Serial.printf

typedef struct TestEntry {
	const uint8_t *data;
	size_t dataLen;
	const char *enc;
} TestEntry;

const uint8_t data1[] = {};
const char *enc1 = "";
const uint8_t data2[] = {28};
const char *enc2 = "HA==";
const uint8_t data3[] = {174, 208};
const char *enc3 = "rtA=";
const uint8_t data4[] = {50, 224, 208};
const char *enc4 = "MuDQ";
const uint8_t data5[] = {45, 18, 235, 6};
const char *enc5 = "LRLrBg==";
const uint8_t data6[] = {117, 199, 153, 221, 160};
const char *enc6 = "dceZ3aA=";
const uint8_t data7[] = {141, 12, 188, 48, 173, 45};
const char *enc7 = "jQy8MK0t";
const uint8_t data8[] = {69, 143, 148, 125, 213, 3, 148};
const char *enc8 = "RY+UfdUDlA==";
const uint8_t data9[] = {251, 162, 166, 60, 129, 131, 46, 13};
const char *enc9 = "+6KmPIGDLg0=";
const uint8_t data10[] = {207, 40, 204, 254, 77, 71, 61, 8, 128};
const char *enc10 = "zyjM/k1HPQiA";
const uint8_t data11[] = {156, 150, 213, 174, 117, 59, 70, 220, 210, 63};
const char *enc11 = "nJbVrnU7RtzSPw==";
const uint8_t data12[] = {192, 54, 173, 19, 126, 84, 26, 250, 167, 5, 50};
const char *enc12 = "wDatE35UGvqnBTI=";
const uint8_t data13[] = {20, 1, 15, 77, 224, 141, 153, 47, 186, 170, 200, 227};
const char *enc13 = "FAEPTeCNmS+6qsjj";
const uint8_t data14[] = {85, 166, 130, 169, 193, 117, 194, 81, 238, 64, 180, 228, 127};
const char *enc14 = "VaaCqcF1wlHuQLTkfw==";
const uint8_t data15[] = {65, 130, 145, 17, 247, 99, 158, 36, 117, 8, 192, 1, 193, 234};
const char *enc15 = "QYKREfdjniR1CMABweo=";
const uint8_t data16[] = {9, 55, 253, 179, 203, 93, 237, 58, 252, 200, 168, 145, 115, 53, 31};
const char *enc16 = "CTf9s8td7Tr8yKiRczUf";
const uint8_t data17[] = {254, 76, 140, 77, 16, 52, 119, 229, 186, 225, 109, 181, 134, 34, 229, 153, 235, 1, 16, 126, 17, 14, 13, 12, 138, 248, 230, 60, 73, 128, 116, 204, 207};
const char *enc17 = "/kyMTRA0d+W64W21hiLlmesBEH4RDg0MivjmPEmAdMzP";
const uint8_t data18[] = {155, 159, 208, 168, 221, 216, 113, 8, 58, 136, 77, 93, 86, 50, 80, 91, 14, 102, 10, 54, 2, 158, 195, 75, 40, 245, 84, 177, 116, 54, 235, 217, 124, 232, 205, 113, 111, 33, 231, 251, 246, 136, 41, 167, 201, 234, 20, 83, 225, 67, 131, 210, 97, 194, 1, 252, 158, 253, 84, 135, 119, 1, 254, 11, 182, 208};
const char *enc18 = "m5/QqN3YcQg6iE1dVjJQWw5mCjYCnsNLKPVUsXQ269l86M1xbyHn+/aIKafJ6hRT4UOD0mHCAfye/VSHdwH+C7bQ";
const uint8_t data19[] = {101, 43, 33, 221, 108, 128, 221, 221, 52, 11, 40, 166, 120, 198, 79, 0, 141, 127, 183, 226, 197, 232, 52, 29, 136, 1, 16, 27, 216, 71, 149, 251, 131, 94, 22, 118, 25, 255, 214, 119, 91, 182, 203, 228, 67, 22, 88, 180, 161, 42, 182, 125, 183, 239, 186, 216, 23, 11, 17, 144, 124, 201, 177, 3, 83, 68, 131, 249, 52, 189, 2, 28, 74, 172, 214, 117, 126, 249, 239, 90, 22, 204, 161, 243, 232, 166, 103, 150, 20, 240, 60, 93, 187, 67, 57, 231, 1, 102, 221, 194, 76, 162, 8, 89, 72, 150, 146, 247, 181, 134, 242, 205, 179, 19, 155, 68, 94, 82, 214, 56, 1, 111, 109, 78, 155, 216, 73, 7, 80, 243};
const char *enc19 = "ZSsh3WyA3d00CyimeMZPAI1/t+LF6DQdiAEQG9hHlfuDXhZ2Gf/Wd1u2y+RDFli0oSq2fbfvutgXCxGQfMmxA1NEg/k0vQIcSqzWdX7571oWzKHz6KZnlhTwPF27QznnAWbdwkyiCFlIlpL3tYbyzbMTm0ReUtY4AW9tTpvYSQdQ8w==";
const uint8_t data20[] = {177, 224, 149, 210, 54, 194, 123, 141, 157, 224, 99, 1, 189, 114, 37, 230, 250, 149, 161, 158, 138, 226, 5, 18, 131, 169, 202, 130, 46, 109, 102, 35, 113, 199, 109, 178, 98, 137, 249, 69, 227, 130, 232, 246, 105, 101, 97, 234, 120, 151, 31, 41, 90, 20, 15, 246, 90, 214, 39, 139, 86, 52, 78, 174, 35, 95, 63, 226, 241, 127, 164, 219, 174, 140, 255, 17, 120, 118, 97, 131, 133, 35, 231, 117, 215, 74, 14, 110, 70, 42, 110, 7, 37, 234, 139, 210, 224, 36, 71, 227, 68, 155, 236, 191, 61, 83, 11, 189, 88, 60, 208, 3, 109, 121, 32, 71, 169, 58, 125, 112, 116, 16, 153, 200, 74, 242, 89, 141, 143, 25, 211, 92, 179, 227, 223, 183, 219, 18, 54, 208, 80, 253, 11, 76, 69, 150, 4, 48, 238, 73, 165, 25, 133, 200, 80, 207, 84, 182, 64, 251, 156, 76, 255, 112, 227, 235, 154, 29, 191, 86, 217, 118, 219, 51, 38, 173, 6, 111, 14, 55, 195, 13, 45, 236, 66, 180, 39, 109, 110, 7, 47, 61, 103, 100, 117, 55, 89, 35, 64, 106, 106, 42, 238, 37, 70, 20, 8, 128, 34, 131, 56, 120, 103, 125, 149, 182, 130, 217, 38, 102, 24, 170, 111, 47, 113, 79, 142, 4, 167, 80, 12, 174, 102, 74, 129, 109, 204, 12, 252, 200, 95, 97, 51, 215, 169, 148, 191, 113, 155, 228, 145, 235, 35, 252, 53, 177};
const char *enc20 = "seCV0jbCe42d4GMBvXIl5vqVoZ6K4gUSg6nKgi5tZiNxx22yYon5ReOC6PZpZWHqeJcfKVoUD/Za1ieLVjROriNfP+Lxf6Tbroz/EXh2YYOFI+d110oObkYqbgcl6ovS4CRH40Sb7L89Uwu9WDzQA215IEepOn1wdBCZyEryWY2PGdNcs+Pft9sSNtBQ/QtMRZYEMO5JpRmFyFDPVLZA+5xM/3Dj65odv1bZdtszJq0Gbw43ww0t7EK0J21uBy89Z2R1N1kjQGpqKu4lRhQIgCKDOHhnfZW2gtkmZhiqby9xT44Ep1AMrmZKgW3MDPzIX2Ez16mUv3Gb5JHrI/w1sQ==";


TestEntry testEntries[] = {
	{ data1, 0, enc1},
	{ data2, 1, enc2},
	{ data3, 2, enc3},
	{ data4, 3, enc4},
	{ data5, 4, enc5},
	{ data6, 5, enc6},
	{ data7, 6, enc7},
	{ data8, 7, enc8},
	{ data9, 8, enc9},
	{ data10, 9, enc10},
	{ data11, 10, enc11},
	{ data12, 11, enc12},
	{ data13, 12, enc13},
	{ data14, 13, enc14},
	{ data15, 14, enc15},
	{ data16, 15, enc16},
	{ data17, 33, enc17},
	{ data18, 66, enc18},
	{ data19, 130, enc19},
	{ data20, 256, enc20}
};

void runTests() {
	size_t numTestEntries = sizeof(testEntries) / sizeof(testEntries[0]);
	for(size_t testNum = 0; testNum < numTestEntries; testNum++) {
		DEBUG_PRINT("test %lu starting\n", testNum);

		size_t encodedLen = Base64::getEncodedSize(testEntries[testNum].dataLen, true);

		//DEBUG_PRINT("dataLen=%lu encodedLen=%lu\n", testEntries[testNum].dataLen, encodedLen);

		char *encoded = new char[encodedLen];

		bool success = Base64::encode(testEntries[testNum].data, testEntries[testNum].dataLen, encoded, encodedLen, true);
		if (success) {
			if (strcmp(encoded, testEntries[testNum].enc) == 0) {
				// Successfully encoded
				size_t srcLen = strlen(encoded);

				size_t decodedLen = Base64::getMaxDecodedSize(srcLen);
				uint8_t *decoded = new uint8_t[decodedLen];

				success = Base64::decode(encoded, decoded, decodedLen);
				if (success) {
					if (decodedLen == testEntries[testNum].dataLen) {

					}
					else {
						DEBUG_PRINT("test %lu decode length mismatch got %lu expected %lu\n", testNum, decodedLen, testEntries[testNum].dataLen);
					}
				}
				else {
					DEBUG_PRINT("test %lu decode returned false\n", testNum);
				}

				// Overwrite the null terminator to make sure we're paying attention to the length
				encoded[srcLen] = 'A';

				success = Base64::decode(encoded, srcLen, decoded, decodedLen);
				if (success) {
					if (decodedLen == testEntries[testNum].dataLen) {

					}
					else {
						DEBUG_PRINT("test %lu decode length mismatch got %lu expected %lu\n", testNum, decodedLen, testEntries[testNum].dataLen);
					}
				}
				else {
					DEBUG_PRINT("test %lu decode returned false\n", testNum);
				}

				delete[] decoded;
			}
			else {
				DEBUG_PRINT("test %lu encoded data did not match\n", testNum);
				DEBUG_PRINT("got: %s\n", encoded);
				DEBUG_PRINT("exp: %s\n", testEntries[testNum].enc);
			}
		}
		else {
			DEBUG_PRINT("test %lu encode returned false (with termination)\n", testNum);
		}

		delete[] encoded;

		// Repeat with non-terminated string
		encodedLen = Base64::getEncodedSize(testEntries[testNum].dataLen, false);

		encoded = new char[encodedLen];

		success = Base64::encode(testEntries[testNum].data, testEntries[testNum].dataLen, encoded, encodedLen, false);
		if (success) {
			if (encodedLen == strlen(testEntries[testNum].enc)) {
				if (strncmp(encoded, testEntries[testNum].enc, encodedLen) == 0) {
					// Successfully encoded
				}
				else {
					DEBUG_PRINT("test %lu encoded data did not match (no termination)\n", testNum);
				}
			}
			else {
				DEBUG_PRINT("test %lu encoded length did not match (no termination)\n", testNum);
			}
		}
		else {
			DEBUG_PRINT("test %lu encode returned false (no termination)\n", testNum);
		}

		delete[] encoded;

		// Repeat with buffer too small

		encodedLen = Base64::getEncodedSize(testEntries[testNum].dataLen, false);
		if (encodedLen > 1) {
			encodedLen--;
			encoded = new char[encodedLen];

			success = Base64::encode(testEntries[testNum].data, testEntries[testNum].dataLen, encoded, encodedLen, false);
			if (success) {
				DEBUG_PRINT("test %lu returned success but should have failed with buffer too small", testNum);
			}

			delete[] encoded;
		}

		// Test encode to string
		String encodedStr = Base64::encodeToString(testEntries[testNum].data, testEntries[testNum].dataLen);
		if (encodedStr.length() == (int)strlen(testEntries[testNum].enc)) {
			if (strcmp(encodedStr, testEntries[testNum].enc) == 0) {
			}
			else {
				DEBUG_PRINT("test %lu encoded data did not match (string)\n", testNum);
			}
		}
		else {
			DEBUG_PRINT("test %lu encoded length did not match (string)\n", testNum);
		}
	}
}

void setup() {
	Serial.begin(9600);
}

void loop() {
	runTests();
	Serial.printlnf("freeMemory=%lu", System.freeMemory());
	delay(10000);
}
