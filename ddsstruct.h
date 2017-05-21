struct ddsHeader // Header of the .DDS files themselves
{
	int magic; // "DDS "
	int size; // 124
	int flags; // RGBA: 0x0002100F, DXTn: 0x000A1007
		/* DDSD_CAPS				0x00000001
		 * DDSD_HEIGHT				0x00000002
		 * DDSD_WIDTH				0x00000004
		 * DDSD_PITCH				0x00000008
		 * DDSD_PIXELFORMAT			0x00001000
		 * DDSD_MIPMAPCOUNT			0x00020000
		 * DDSD_LINEARSIZE			0x00080000
		 * DDSD_DEPTH				0x00800000
		 */
	int height; // Height of image
	int width; // Width of image
	int bytes; // Bytes per scanline if not compressed, bytes in main image if compressed
	int depth; // Depth for volume textures
	int mipMaps; // Number of mip-maps
	int null0[11]; // Garbage nothingness
	struct pixelFormat // Stuff to do with the DDS type
	{
		int size; // 32
		int flags; // RGBA: 0x00000041, DXTn: 0x00000005
			/* DDPF_ALPHAPIXELS		0x00000001
			 * DDPF_FOURCC			0x00000004
			 * DDPF_RGB				0x00000040
			 */
		char dxt[3]; // "DXT" in DXTn-compressed images
		char type; // Last character of the four-character code in "DXTn"
		int bitsPerPixel; // In RGB formats
		int redBitMask; // Mask for red channel in RGB formats
		int greenBitMask; // Green mask
		int blueBitMask; // Blue mask
		int alphaBitMask; // Alpha mask
	} format; // Sub-structure
	int capabilities; // 0x00401008
			/* DDSCAPS_COMPLEX		0x00000008
			 * DDSCAPS_TEXTURE		0x00001000
			 * DDSCAPS_MIPMAP		0x00400000
			 */
	int null1[4]; // Garbage
};