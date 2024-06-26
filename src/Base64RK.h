#ifndef __BASE64RK_H
#define __BASE64RK_H

#include "Particle.h"

/**
 * @brief Class for Base64 encoding and decoding
 *
 * Useful for transmitting binary data in places where only text strings are allowed. On the
 * Particle platform, functions, publish, and subscribe need encoding of binary data.
 *
 * https://en.wikipedia.org/wiki/Base64
 * https://tools.ietf.org/html/rfc4648
 */
class Base64 {
public:
	/**
	 * @brief Encode binary data to Base64
	 *
	 * @param src Pointer to the binary data to encode.
	 *
	 * @param srcLen Length of the binary data to encode in bytes.
	 *
	 * @param dst Pointer to the buffer to hold the character string. See getEncodedSize() for
	 * information on how large of a buffer you need.
	 *
	 * @param dstLen On input, the length of the buffer pointed to by dst. On successful return,
	 * the number of bytes of text data.
	 *
	 * @param nullTerminate true to add a null terminator, false to not. Note that the length in dstLen
	 * does NOT include the null terminator if included.
	 *
	 * @param lineBreakAt -1 to not add line breaks, or the column to add line breaks, which
	 * must be a multiple of 4 and is typically 76, sometimes 64. Default is to not add
	 * line breaks.
	 * 
	 * @return true on success or false on failure (buffer too small, for example)
	 *
	 * This method does not allocate memory. It is MT safe.
	 */
	static bool encode(const uint8_t *src, size_t srcLen, char *dst, size_t &dstLen, bool nullTerminate, int lineBreakAt = -1);

	/**
	 * @brief Determine the buffer size for the encoded Base64 data
	 *
	 * @param srcLen The size of the data in bytes
	 *
	 * @param nullTerminate true if you will be adding a null terminator or false if not
	 *
	 * @param lineBreakAt -1 to not add line breaks, or the column to add line breaks, which
	 * must be a multiple of 4 and is typically 76, sometimes 64. Default is to not add
	 * line breaks.
	 * 
	 * The size is (srcLen + 2) / 3 * 4 plus line breaks if requested.
	 *
	 * This method does not allocate memory. It is MT safe.
	 */
	static size_t getEncodedSize(size_t srcLen, bool nullTerminate, int lineBreakAt = -1);

	/**
	 * @brief Encode binary data and return it as a String object.
	 *
	 * @param src Pointer to the binary data to encode.
	 *
	 * @param srcLen Length of the binary data to encode in bytes.
	 * 
	 * @param lineBreakAt -1 to not add line breaks, or the column to add line breaks, which
	 * must be a multiple of 4 and is typically 76, sometimes 64. Default is to not add
	 * line breaks.
	 *
	 * @return A String object containing Base64 data
	 *
	 * This is relatively efficient (the buffer is only allocated once using reserve) but using
	 * the other encode() method does not require a memory allocation and is more efficient.
	 *
	 * This method is MT safe.
	 */
	static String encodeToString(const uint8_t *src, size_t srcLen, int lineBreakAt = -1);

	/**
	 * @brief Encode binary data and store it as a String object.
	 *
	 * @param src Pointer to the binary data to encode.
	 *
	 * @param srcLen Length of the binary data to encode in bytes.
	 *
	 * @param output Filled in with the Base64 representation of the data. Is emptied before using.
	 *
	 * @param lineBreakAt -1 to not add line breaks, or the column to add line breaks, which
	 * must be a multiple of 4 and is typically 76, sometimes 64. Default is to not add
	 * line breaks.
	 *
	 * This is relatively efficient (the buffer is only allocated once using reserve) but using
	 * the other encode() method does not require a memory allocation and is more efficient.
	 *
	 * This method is MT safe.
	 */
	static void encodeToString(const uint8_t *src, size_t srcLen, String &output, int lineBreakAt = -1);


	/**
	 * @brief Decode Base64 encoded data back to binary data from a c-string
	 *
	 * @param src Pointer to the source string. You can directly pass a String object if desired.
	 *
	 * @param dst Pointer to a buffer to store te binary data in
	 *
	 * @param dstLen On input, the size of the buffer pointed to by dst. On successful return, the
	 * number of actual bytes.
	 *
	 * @return true on a successful decode or false on error (invalid input or dstLen too small)
	 *
	 * This method does not allocate memory. It is MT safe.
	 */
	static bool decode(const char *src, uint8_t *dst, size_t &dstLen);


	/**
	 * @brief Decode Base64 encoded data back to binary data from a buffer and length
	 *
	 * @param src Pointer to the source string. It does not need to be null terminated.
	 *
	 * @param srcLen The length of the source string in bytes
	 *
	 * @param dst Pointer to a buffer to store te binary data in
	 *
	 * @param dstLen On input, the size of the buffer pointed to by dst. On successful return, the
	 * number of actual bytes.
	 *
	 * @return true on a successful decode or false on error (invalid input or dstLen too small)
	 *
	 * This method does not allocate memory. It is MT safe.
	 */
	static bool decode(const char *src, size_t srcLen, uint8_t *dst, size_t &dstLen);

	/**
	 * @brief Get the maximum size of the decoded data, given Base64 encoded string of srcLen
	 *
	 * This is ((srcLen + 3) / 4) * 3. The actual data may be smaller than this if it's not a multiple
	 * of 3 bytes and padding is inserted. The actual length will be returned in dstLen for decode.
	 *
	 * This method does not allocate memory. It is MT safe.
	 */
	static size_t getMaxDecodedSize(size_t srcLen);

private:
	static const char *encodeTable;
	static const uint8_t decodeTable[];
};



#endif /* __BASE64RK_H */

