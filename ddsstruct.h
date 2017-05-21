#include "stdint.h"
struct ddsHeader // Header of the .DDS files themselves
{
	int32_t magic; // "DDS "
	int32_t size; // 124
	int32_t flags; // RGBA: 0x0002100F, DXTn: 0x000A1007
		/* DDSD_CAPS				0x00000001
		 * DDSD_HEIGHT				0x00000002
		 * DDSD_WIDTH				0x00000004
		 * DDSD_PITCH				0x00000008
		 * DDSD_PIXELFORMAT			0x00001000
		 * DDSD_MIPMAPCOUNT			0x00020000
		 * DDSD_LINEARSIZE			0x00080000
		 * DDSD_DEPTH				0x00800000
		 */
	int32_t height; // Height of image
	int32_t width; // Width of image
	int32_t bytes; // Bytes per scanline if not compressed, bytes in main image if compressed
	int32_t depth; // Depth for volume textures
	int32_t mipMaps; // Number of mip-maps
	int32_t null0[11]; // Garbage nothingness
	struct pixelFormat // Stuff to do with the DDS type
	{
		int32_t size; // 32
		int32_t flags; // RGBA: 0x00000041, DXTn: 0x00000005
			/* DDPF_ALPHAPIXELS		0x00000001
			 * DDPF_FOURCC			0x00000004
			 * DDPF_RGB				0x00000040
			 */
		char dxt[3]; // "DXT" in DXTn-compressed images
		char type; // Last character of the four-character code in "DXTn"
		int32_t bitsPerPixel; // In RGB formats
		int32_t redBitMask; // Mask for red channel in RGB formats
		int32_t greenBitMask; // Green mask
		int32_t blueBitMask; // Blue mask
		int32_t alphaBitMask; // Alpha mask
	} format; // Sub-structure
	int32_t capabilities; // 0x00401008
			/* DDSCAPS_COMPLEX		0x00000008
			 * DDSCAPS_TEXTURE		0x00001000
			 * DDSCAPS_MIPMAP		0x00400000
			 */
	int32_t null1[4]; // Garbage
};
