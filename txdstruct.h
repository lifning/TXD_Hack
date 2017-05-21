struct txdHeader // First header in the .TXD
{
	int twentyTwo; // This should be 22
	int fileSize; // Add 12 to get the file size
	int identifyingBytes0; // 335609855
	int one0; // Should be 1
	int four0; // Should be 4
	int identifyingBytes1; // 335609855
	int ddsCount; // Number of .DDS textures in the .TXD
	int twentyOne; // Should be 21
	int ddsSize0; // Subtract 116 to get the first .DDS's size
	int identifyingBytes2; // 335609855
	int one1; // Should be 1
	int ddsSize1; // Subtract 92 to get the first .DDS's size
	int identifyingBytes3; // More 335609855
	int eight; // Should be 8
	int bitsPerPixel0; // 4354 if it's 8-bit, 4358 if it's 16-bit, or 4353 if it's 32-bit
	char fileName[64]; // Add .DDS to get the file name
	int ddsType; // Determines the type of .DDS file it is
		/* 512: 16-bit				// 33280
		 * 768: 16-bit (alpha)		// 33024
		 * 1536: 32-bit				// 38400
		 * 1280: 32-bit (alpha)		// 38144
		 * 9728: 8-bit				// ? DXTn
		 * 9472: 8-bit (alpha)		// ? DXTn
		 */
	int alphaFlag; // Makes half of the above pointless if you ask me
	short width; // Texture width
	short height; // Texture height
	char bitsPerPixel1; // You know, the bits per pixel shows up almost as unnecessarily as the identifyingBytes
	char mipMaps; // Number of mip-maps in the image
	char four1; // Should be 4
	char dxtType; // If it uses DXT compression, this will be 1, 2, 3, 4, or 5 for the type ('1' - 0x30 == 1)
	int imageSize; // Usually the width times the height, but in 8-bit images this is where the data starts
};

struct txdSubHeader // Headers of the consequent .DDS entries
{
	int three; // Should be 3
	int zero; // Should be 0
	int identifyingBytes0; // 335609855
	int twentyOne; // Should be 21
	int ddsSize0; // Subtract 116 to get the .DDS's size
	int identifyingBytes1; // 335609855
	int one; // Should be 1
	int ddsSize1; // Subtract 92 to get the .DDS's size
	int identifyingBytes2; // 335609855
	int eight; // Should be 8
	int bitsPerPixel0; // 4354 if it's 8-bit, 4358 if it's 16-bit, or 4353 if it's 32-bit
	char fileName[64]; // Add .DDS to get the file name
	int ddsType; // Determines the type of .DDS file it is
		/* 512: 16-bit				// 33280
		 * 768: 16-bit (alpha)		// 33024
		 * 1536: 32-bit				// 38400
		 * 1280: 32-bit (alpha)		// 38144
		 * 9728: 8-bit				// ? DXTn
		 * 9472: 8-bit (alpha)		// ? DXTn
		 */
	int alphaFlag; // Makes half of the above pointless if you ask me
	short width; // Texture width
	short height; // Texture height
	char bitsPerPixel1; // You know, the bits per pixel shows up almost as unnecessarily as the identifyingBytes
	char mipMaps; // Number of mip-maps in the image
	char four; // Should be 4
	char dxtType; // If it uses DXT compression, this will be 1, 2, 3, 4, or 5 for the type
	int imageSize; // Usually the width times the height, but in 8-bit images this is where the data starts
};
