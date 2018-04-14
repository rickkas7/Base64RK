// This node.js script is used to generate the unit test data files.
// It creates base64 data from raw binary data of various lengths to make
// sure padding and the bit math works properly.

var sampleNum = 1;
var info = [];

var badChars = [
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
];

for(var ii = 0; ii < 16; ii++) {
	generateRandomSample(ii);
}
generateRandomSample(33);
generateRandomSample(66);
generateRandomSample(130);
generateRandomSample(256);


console.log('TestEntry testEntries[] = {');

for(var ii = 0; ii < info.length; ii++) {
	console.log('\t' + info[ii] + (((ii + 1) < info.length) ? ',' : ''));
}

console.log('};');

function generateRandomSample(len) {
	var buf = Buffer.alloc(len);
	
	var rawStr = '';
	for(var ii = 0; ii < len; ii++) {
		var samp = Math.floor(Math.random() * 256);
		buf.writeUInt8(samp, ii);
		
		if (ii > 0) {
			rawStr += ', ';
		}
		rawStr += samp;
	}
	console.log('const uint8_t data' + sampleNum + '[] = {' + rawStr + '};');
	
	var base64 = buf.toString('base64');
	console.log('const char *enc' + sampleNum + ' = "' + base64 + '";');

	var infoStr = '{ data' + sampleNum + ', ' + len + ', enc' + sampleNum + '}'; 
	info.push(infoStr);
	
	sampleNum++;
}

