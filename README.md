# Base64RK - Base64 Encoder/Decoder for Particle

Useful for transmitting binary data in places where only text strings are allowed. On the Particle platform, functions, publish, and subscribe need encoding of binary data.

- [https://en.wikipedia.org/wiki/Base64](https://en.wikipedia.org/wiki/Base64)
- [https://tools.ietf.org/html/rfc4648](https://tools.ietf.org/html/rfc4648)


## API

### encode

Encode binary data to Base64

```
static bool encode(const uint8_t *src, size_t srcLen, char *dst, size_t &dstLen, bool nullTerminate);
```

- src Pointer to the binary data to encode.

- srcLen Length of the binary data to encode in bytes.

- dst Pointer to the buffer to hold the character string. See getEncodedSize() for
information on how large of a buffer you need.

- dstLen On input, the length of the buffer pointed to by dst. On successful return,
the number of bytes of text data.

- nullTerminate true to add a null terminator, false to not. Note that the length in dstLen
does NOT include the null terminator if included.

- Returns true on success or false on failure (buffer too small, for example)

This method does not break the data into lines. The intended use case of this is things like
Particle.publish and the line breaks are not helpful and just use up extra bytes.

This method does not allocate memory. It is MT safe.
	 
--

### getEncodedSize

Determine the buffer size for the encoded Base64 data

```
static size_t getEncodedSize(size_t srcLen, bool nullTerminate);
```
- srcLen The size of the data in bytes

- nullTerminate true if you will be adding a null terminator or false if not

The size is (srcLen + 2) / 3 * 4.

This method does not allocate memory. It is MT safe.
	 
--

### encodeToString

Encode binary data and return it as a String object.

```
static String encodeToString(const uint8_t *src, size_t srcLen);
```

- src Pointer to the binary data to encode.

- srcLen Length of the binary data to encode in bytes.

- Returns A String object containing Base64 data

This method does not break the data into lines. The intended use case of this is things like
Particle.publish and the line breaks are not helpful and just use up extra bytes.

This is relatively efficient (the buffer is only allocated once using reserve) but using
the other encode() method does not require a memory allocation and is more efficient.

This method is MT safe.
	 
--

### decode (c-string)

Decode Base64 encoded data back to binary data from a c-string

```
static bool decode(const char *src, uint8_t *dst, size_t &dstLen);
```
	
- src Pointer to the source string. You can directly pass a String object if desired.

- dst Pointer to a buffer to store te binary data in

- dstLen On input, the size of the buffer pointed to by dst. On successful return, the
number of actual bytes.

- Returns true on a successful decode or false on error (invalid input or dstLen too small)

The input src must not contain line breaks (CRLF). The intended use case of this is things like
Particle.publish and the line breaks are not helpful and just use up extra bytes.

This method does not allocate memory. It is MT safe.

--

### decode (buffer and length)

Decode Base64 encoded data back to binary data from a buffer and length

```
static bool decode(const char *src, size_t srcLen, uint8_t *dst, size_t &dstLen);
```

- src Pointer to the source string. It does not need to be null terminated.

- srcLen The length of the source string in bytes

- dst Pointer to a buffer to store te binary data in

- dstLen On input, the size of the buffer pointed to by dst. On successful return, the
number of actual bytes.

- Returns true on a successful decode or false on error (invalid input or dstLen too small)

The input src must not contain line breaks (CRLF). The intended use case of this is things like
Particle.publish and the line breaks are not helpful and just use up extra bytes.

This method does not allocate memory. It is MT safe.

--

### getMaxDecodedSize

Get the maximum size of the decoded data, given Base64 encoded string of srcLen

```
static size_t getMaxDecodedSize(size_t srcLen);
```

This is ((srcLen + 3) / 4) * 3. The actual data may be smaller than this if it's not a multiple
of 3 bytes and padding is inserted. The actual length will be returned in dstLen for decode.

This method does not allocate memory. It is MT safe.
	 

## Examples


### examples/1-tester-Base64

This example uses Particle functions and publish to test the various methods.

For example, given the code running on device test2:

```
particle call test2 text "hello world"
```

The following will appear on debug serial and published:

```
text->base64 aGVsbG8gd29ybGQ=
```

You can then decode this to hex:

```
particle call test2 base64 aGVsbG8gd29ybGQ=
``` 

which generates:

```
base64->hex 68656c6c6f20776f726c64
```

You can also convert hex back to base64:

```
particle call test2 hex "68656c6c6f20776f726c64"
```

```
hex->base64 aGVsbG8gd29ybGQ=
```


### examples/2-unittest-Base64

This example runs pre-generated sample data through the parser and decoder to make sure they work properly.

## Test Code

There is also code in the test directory, for off-device testing. 

### generate-test-data

This is the node.js tool that generated the test data used in the unit tests (both on-device and off-device).

### unit-test

The unit-test is designed to run on a standard gcc environment, such as Mac or Linux, or cygwin. It encodes and decodes a variety of data samples and makes sure they match the expected data.

Data from size 0 to 16 bytes is tested, as well as other sizes up to 512 bytes, to make sure a variety of padding circumstances are tested, as well as a large number of bit combinations.

Particularly useful is running under Linux with [valgrind](http://valgrind.org/) installed. The `make check` target runs the unit-test program under valgrind. The tool detects common memory errors including if the code:

- Accesses memory it shouldn't (areas not yet allocated, areas that have been freed, areas past the end of heap blocks, inaccessible areas of the stack).
- Uses uninitialized values in dangerous ways.
- Leaks memory.
- Does bad frees of heap blocks (double frees, mismatched frees).
- Passes overlapping source and destination memory blocks to memcpy() and related functions.



 