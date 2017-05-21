int unpackTXD(char* file)
{
	int i, j; // Variables for loops
	char* directory; // Path to where we'll output the files
	char* ddsName; // Name of the DDS to output
	FILE *inputTXD; // File we'll read .DDS data from
	FILE *outputDDS; // File we'll use to write out .DDS data
	txdHeader txdData; // Header of the .TXD file
	txdSubHeader txdSubData; // Subheaders in the .TXD
	ddsHeader ddsData; // Header of each .DDS file

	directory = new char[strlen(file)]; // Make the string long enough
	strcpy(directory, file); // Copy the file's path and name
	*(strrchr(directory, '\\') + 1) = '\0'; // Cut off the file part by null-terminating it

	inputTXD = fopen(file, "rb"); // Open the file for binary reading
	if(inputTXD == NULL) // If the file didn't open right
		return 1; // Return the error

	fread(&txdData, sizeof(txdData), 1, inputTXD); // Read the header data

	if(txdData.identifyingBytes0 != 335609855 || txdData.fileName[0] == 0x00) // If it's a different version
		return 3; // Return the error

	printf("\n%d Textures:", txdData.ddsCount); // Output the number of .DDSes

	printf("\n\t%s.dds", txdData.fileName); // Output the file name
	printf("\t%dx%d", txdData.width, txdData.height); // Output the dimensions
	printf("\t%dbpp", txdData.bitsPerPixel1); // Output the bits per pixel
	if(txdData.dxtType >= 1 && txdData.dxtType <= 5) // If it's DXTn
		printf("\tDXT%d", txdData.dxtType); // Output the DXTn Number
	else // Otherwise
	{
		printf("\tRGB"); // Output that it's not DXTn
		if(txdData.alphaFlag != 0) // If it has alpha
			printf("A"); // Output if it has alpha
	}
	printf("\tMipMaps: %d", txdData.mipMaps); // Output number of mip-maps

	if(
		txdData.eight != 8
		|| txdData.four0 != 4		|| txdData.four1 != 4
		|| txdData.one0 != 1		|| txdData.one1 != 1
		|| txdData.twentyOne != 21	|| txdData.twentyTwo != 22
		|| txdData.ddsSize0 - 116 != txdData.ddsSize1 - 92
	) // If the .TXD appears corrupt
		return 2; // Return the error

	ddsName = new char[strlen(directory) + 68]; // Make the string long enough
	strcpy(ddsName, directory); // Copy the directory into the name of the output file
	strcat(ddsName, txdData.fileName); // Concatenate the .DDS's name
	strcat(ddsName, ".dds"); // Concatenate the .DDS extension

	ddsData.magic = 542327876; // Set the first four bytes to "DDS "
	ddsData.size = 124; // Set the size of the header

	if(txdData.dxtType >= 1 && txdData.dxtType <= 5) // If it's a DXTn texture
		ddsData.flags = 0x000A1007; // Set the flags accordingly
	else // Otherwise
		ddsData.flags = 0x0002100F; // Make it RGBA

	ddsData.height = txdData.height; // Set the height
	ddsData.width = txdData.width; // Set the width

	if(txdData.dxtType >= 1 && txdData.dxtType <= 5) // If it's a DXTn texture
		ddsData.bytes = txdData.width * 4; // Set the bytes per scanline
	else // Otherwise
		ddsData.bytes = txdData.ddsSize0 - 116; // Set it to the bytes in the image

	ddsData.depth = 0; // It's not a volume texture
	ddsData.mipMaps = txdData.mipMaps - 1; // Set the number of mip-maps

	ddsData.format.size = 32; // Set the size of the sub-structure
	if(txdData.dxtType >= 1 && txdData.dxtType <= 5) // If it's DXTn
	{
		ddsData.format.flags = txdData.alphaFlag + 0x4; // Set it up for DXTn
		ddsData.format.dxt[0] = 'D'; // Write the D in DXTn
		ddsData.format.dxt[1] = 'X'; // Write the X in DXTn
		ddsData.format.dxt[2] = 'T'; // Write the T in DXTn
		ddsData.format.type = txdData.dxtType + 0x30; // Set the n in DXTn
	}
	else // Otherwise
	{
		ddsData.format.flags = txdData.alphaFlag + 0x40; // Set it up for RGBA
		ddsData.format.dxt[0] = 0; // Set what would be the D in DXTn to null
		ddsData.format.dxt[1] = 0; // Set what would be the X in DXTn to null
		ddsData.format.dxt[2] = 0; // Set what would be the T in DXTn to null
		ddsData.format.type = 0; // Set what would be the n in DXTn to null
	}
	ddsData.format.bitsPerPixel = txdData.bitsPerPixel1; // Set the bit per pixel
	ddsData.format.redBitMask = 0x00FF0000; // Set the bit mask for red
	ddsData.format.greenBitMask = 0x0000FF00; // Set the bit mask for green
	ddsData.format.blueBitMask = 0x000000FF; // Set the bit mask for blue
	ddsData.format.alphaBitMask = 0xFF000000; // Set the bit mask for alpha

	ddsData.capabilities = 0x1008; // Set the capabilities
	if(txdData.mipMaps > 1) // If there are mip-maps
		ddsData.capabilities += 0x00400000; // Set that capability flag too

	for(i = 0; i < 11; i++) // For all of the null bytes in the first garbage data
		ddsData.null0[i] = 0; // Set them to null
	for(i = 0; i < 4; i++) // For all of the null bytes in the second garbage data
		ddsData.null1[i] = 0; // Set them to null

	outputDDS = fopen(ddsName, "wb"); // Open the file for binary writing
	if(outputDDS == NULL) // If the file didn't open right
		return 4; // Return the error

	fwrite(&ddsData, sizeof(ddsData), 1, outputDDS); // Write the header

	for(i = 0; i < txdData.ddsSize1 - 92; i++) // For all the bytes in the actual picture
		fputc(fgetc(inputTXD), outputDDS); // Copy from the .TXD

	fclose(outputDDS); // Close the file when we're done with it

	for(i = 1; i < txdData.ddsCount; i++)
	{
		fread(&txdSubData, sizeof(txdSubData), 1, inputTXD); // Read the subheader data
		
		printf("\n\t%s.dds", txdSubData.fileName); // Output the file name
		printf("\t%dx%d", txdSubData.width, txdSubData.height); // Output the dimensions
		printf("\t%dbpp", txdSubData.bitsPerPixel1); // Output the bits per pixel

		if(txdSubData.identifyingBytes0 != 335609855 || txdSubData.fileName[0] == 0x00) // If it's an unsupported version
			return 3; // Complain

		if(txdSubData.dxtType >= 1 && txdSubData.dxtType <= 5) // If it's DXTn
			printf("\tDXT%d", txdSubData.dxtType); // Output the DXTn Number
		else // Otherwise
		{
			printf("\tRGB"); // Output that it's not DXTn
			if(txdSubData.alphaFlag != 0) // If it has alpha
				printf("A"); // Output if it has alpha
		}
		printf("\tMipMaps: %d", txdSubData.mipMaps); // Output number of mip-maps

		if(
			txdSubData.eight != 8		|| txdSubData.three != 3
			|| txdSubData.four != 4		|| txdSubData.zero != 0
			|| txdSubData.one != 1		|| txdSubData.twentyOne != 21
			|| txdSubData.ddsSize0 - 116 != txdSubData.ddsSize1 - 92
		) // If the .TXD appears corrupt
			return 2; // Return the error


		ddsName = new char[strlen(directory) + 68]; // Make the string long enough
		strcpy(ddsName, directory); // Copy the directory into the name of the output file
		strcat(ddsName, txdSubData.fileName); // Concatenate the .DDS's name
		strcat(ddsName, ".dds"); // Concatenate the .DDS extension

		ddsData.magic = 542327876; // Set the first four bytes to "DDS "
		ddsData.size = 124; // Set the size of the header

		if(txdSubData.dxtType >= 1 && txdSubData.dxtType <= 5) // If it's a DXTn texture
			ddsData.flags = 0x000A1007; // Set the flags accordingly
		else // Otherwise
			ddsData.flags = 0x0002100F; // Make it RGBA

		ddsData.height = txdSubData.height; // Set the height
		ddsData.width = txdSubData.width; // Set the width

		if(txdSubData.dxtType >= 1 && txdSubData.dxtType <= 5) // If it's a DXTn texture
			ddsData.bytes = txdSubData.width * 4; // Set the bytes per scanline
		else // Otherwise
			ddsData.bytes = txdSubData.ddsSize0 - 116; // Set it to the bytes in the image

		ddsData.depth = 0; // It's not a volume texture
		ddsData.mipMaps = txdSubData.mipMaps - 1; // Set the number of mip-maps

		ddsData.format.size = 32; // Set the size of the sub-structure
		if(txdSubData.dxtType >= 1 && txdSubData.dxtType <= 5) // If it's DXTn
		{
			ddsData.format.flags = txdSubData.alphaFlag + 0x4; // Set it up for DXTn
			ddsData.format.dxt[0] = 'D'; // Write the D in DXTn
			ddsData.format.dxt[1] = 'X'; // Write the X in DXTn
			ddsData.format.dxt[2] = 'T'; // Write the T in DXTn
			ddsData.format.type = txdSubData.dxtType + 0x30; // Set the n in DXTn
		}
		else // Otherwise
		{
			ddsData.format.flags = txdSubData.alphaFlag + 0x40; // Set it up for RGBA
			ddsData.format.dxt[0] = 0; // Set what would be the D in DXTn to null
			ddsData.format.dxt[1] = 0; // Set what would be the X in DXTn to null
			ddsData.format.dxt[2] = 0; // Set what would be the T in DXTn to null
			ddsData.format.type = 0; // Set what would be the n in DXTn to null
		}
		ddsData.format.bitsPerPixel = txdSubData.bitsPerPixel1; // Set the bit per pixel
		ddsData.format.redBitMask = 0x00FF0000; // Set the bit mask for red
		ddsData.format.greenBitMask = 0x0000FF00; // Set the bit mask for green
		ddsData.format.blueBitMask = 0x000000FF; // Set the bit mask for blue
		ddsData.format.alphaBitMask = 0xFF000000; // Set the bit mask for alpha

		ddsData.capabilities = 0x1008; // Set the capabilities
		if(txdSubData.mipMaps > 1) // If there are mip-maps
			ddsData.capabilities += 0x00400000; // Set that capability flag too

		for(j = 0; j < 11; j++) // For all of the null bytes in the first garbage data
			ddsData.null0[j] = 0; // Set them to null
		for(j = 0; j < 4; j++) // For all of the null bytes in the second garbage data
			ddsData.null1[j] = 0; // Set them to null

		outputDDS = fopen(ddsName, "wb"); // Open the file for binary writing
		if(outputDDS == NULL) // If the file didn't open right
			return 4; // Return the error

		fwrite(&ddsData, sizeof(ddsData), 1, outputDDS); // Write the header

		if(txdSubData.bitsPerPixel1 <= 8) // If it's palleted
			fseek(inputTXD, -4, SEEK_CUR); // Rewind four bytes to the different starting point

		for(j = 0; j < txdSubData.ddsSize1 - 92; j++) // For all the bytes in the actual picture
			fputc(fgetc(inputTXD), outputDDS); // Copy from the .TXD

		fclose(outputDDS); // Close the file when we're done with it
	}

	return 0; // No errors!
}
