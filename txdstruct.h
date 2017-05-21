#include "stdint.h"
struct txdHeader // First header in the .TXD
{
	int32_t twentyTwo; // This should be 22
	int32_t fileSize; // Add 12 to get the file size
	int32_t identifyingBytes0; // 335609855
	int32_t one0; // Should be 1
	int32_t four0; // Should be 4
	int32_t identifyingBytes1; // 335609855
	int32_t ddsCount; // Number of .DDS textures in the .TXD
	int32_t twentyOne; // Should be 21
	int32_t ddsSize0; // Subtract 116 to get the first .DDS's size
	int32_t identifyingBytes2; // 335609855
	int32_t one1; // Should be 1
	int32_t ddsSize1; // Subtract 92 to get the first .DDS's size
	int32_t identifyingBytes3; // More 335609855
	int32_t eight; // Should be 8
	int32_t bitsPerPixel0; // 4354 if it's 8-bit, 4358 if it's 16-bit, or 4353 if it's 32-bit
	char fileName[64]; // Add .DDS to get the file name
	int32_t ddsType; // Determines the type of .DDS file it is
		/* 512: 16-bit				// 33280
		 * 768: 16-bit (alpha)		// 33024
		 * 1536: 32-bit				// 38400
		 * 1280: 32-bit (alpha)		// 38144
		 * 9728: 8-bit				// ? DXTn
		 * 9472: 8-bit (alpha)		// ? DXTn
		 */
	int32_t alphaFlag; // Makes half of the above pointless if you ask me
	int16_t width; // Texture width
	int16_t height; // Texture height
	int8_t bitsPerPixel1; // You know, the bits per pixel shows up almost as unnecessarily as the identifyingBytes
	int8_t mipMaps; // Number of mip-maps in the image
	int8_t four1; // Should be 4
	int8_t dxtType; // If it uses DXT compression, this will be 1, 2, 3, 4, or 5 for the type ('1' - 0x30 == 1)
	int32_t imageSize; // Usually the width times the height, but in 8-bit images this is where the data starts
};

struct txdSubHeader // Headers of the consequent .DDS entries
{
	int32_t three; // Should be 3
	int32_t zero; // Should be 0
	int32_t identifyingBytes0; // 335609855
	int32_t twentyOne; // Should be 21
	int32_t ddsSize0; // Subtract 116 to get the .DDS's size
	int32_t identifyingBytes1; // 335609855
	int32_t one; // Should be 1
	int32_t ddsSize1; // Subtract 92 to get the .DDS's size
	int32_t identifyingBytes2; // 335609855
	int32_t eight; // Should be 8
	int32_t bitsPerPixel0; // 4354 if it's 8-bit, 4358 if it's 16-bit, or 4353 if it's 32-bit
	char fileName[64]; // Add .DDS to get the file name
	int32_t ddsType; // Determines the type of .DDS file it is
		/* 512: 16-bit				// 33280
		 * 768: 16-bit (alpha)		// 33024
		 * 1536: 32-bit				// 38400
		 * 1280: 32-bit (alpha)		// 38144
		 * 9728: 8-bit				// ? DXTn
		 * 9472: 8-bit (alpha)		// ? DXTn
		 */
	int32_t alphaFlag; // Makes half of the above pointless if you ask me
	int16_t width; // Texture width
	int16_t height; // Texture height
	int8_t bitsPerPixel1; // You know, the bits per pixel shows up almost as unnecessarily as the identifyingBytes
	int8_t mipMaps; // Number of mip-maps in the image
	int8_t four; // Should be 4
	int8_t dxtType; // If it uses DXT compression, this will be 1, 2, 3, 4, or 5 for the type
	int32_t imageSize; // Usually the width times the height, but in 8-bit images this is where the data starts
};
