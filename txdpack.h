int packTXD(char *files[], int number)
{
	int i, j; // Variables for loops
	int size; // Where we'll store the size of stuff
	char *txdName; // Name of the TXD to output
	char *ddsName; // Name of the DDS being read
	FILE *inputDDS; // File we'll read .DDS data from
	FILE *outputTXD; // File we'll use to write out .TXD data
	txdHeader txdData; // Header of the .TXD file
	txdSubHeader txdSubData; // Subheaders in the .TXD
	ddsHeader ddsData; // Header of each .DDS file

	txdName = new char[strlen(files[0])]; // Make the string long enough
	strcpy(txdName, files[0]); // Copy the file's path and name
	*(strrchr(txdName, '\\') + 1) = '\0'; // Cut off the file part by null-terminating it
	strcat(txdName, "packed.txd"); // Add the name of the file to output

	outputTXD = fopen(txdName, "wb"); // Open the file for binary writing
	if(outputTXD == NULL) // If the file didn't open right
		return 1; // Return the error

	txdData.identifyingBytes0 = 335609855;
	txdData.identifyingBytes1 = 335609855;
	txdData.identifyingBytes2 = 335609855;
	txdData.identifyingBytes3 = 335609855; // Set the proper version
	txdData.eight = 8;
	txdData.four0 = 4;
	txdData.four1 = 4;
	txdData.one0 = 1;
	txdData.one1 = 1;
	txdData.twentyOne = 21;
	txdData.twentyTwo = 22; // Set all the constants
	txdData.ddsCount = number; // Set the number of .DDS files in the .TXD

	inputDDS = fopen(files[0], "rb"); // Open the first .DDS to read from
	if(inputDDS == NULL) // If it didn't open
		return 2; // Return the error

	fseek(inputDDS, 0, SEEK_END); // Go to the end of the file
	size = ftell(inputDDS); // Read the size of the file into our variable for it
	fseek(inputDDS, 0, SEEK_SET); // Go back to the beginning
	fread(&ddsData, sizeof(ddsData), 1, inputDDS); // Read the header data

	txdData.alphaFlag = ddsData.format.flags % 2; // Set the alpha flag properly
	txdData.bitsPerPixel1 = ddsData.format.bitsPerPixel; // Set the bits per pixel
	if(ddsData.format.type > 0x30) // If it's DXTn
	{
		txdData.dxtType = ddsData.format.type - 0x30; // Set that in the .TXD
		if(txdData.alphaFlag == 1) // If it has alpha
		{
			if(txdData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
			{
				txdData.bitsPerPixel0 = 4354; // Set this to the proper 8-bit value
				txdData.ddsType = 9472; // Set this to the proper 8-bit value with alpha
			}
			else if(txdData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
			{
				txdData.bitsPerPixel0 = 4358; // Set this to the proper 16-bit value
				txdData.ddsType = 33024; // Set this to the proper 16-bit value with alpha
			}
			else // Otherwise, it's probably 32 bits per pixel
			{
				txdData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
				txdData.ddsType = 38144; // Set this to the 32-bit value with alpha
			}
		}
		else // Otherwise, if it doesn't have alpha
		{
			if(txdData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
			{
				txdData.bitsPerPixel0 = 4354; // Set this to the proper 8-bit value
				txdData.ddsType = 9728; // Set this to the proper 8-bit value with alpha
			}
			else if(txdData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
			{
				txdData.bitsPerPixel0 = 4358; // Set this to the proper 16-bit value
				txdData.ddsType = 33280; // Set this to the proper 16-bit value with alpha
			}
			else // Otherwise, it's probably 32 bits per pixel
			{
				txdData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
				txdData.ddsType = 38400; // Set this to the 32-bit value with alpha
			}
		}
	}
	else // Otherwise, it's RGBA
	{
		txdData.dxtType = 0; // Set it to zero
		if(txdData.alphaFlag == 1) // If it has alpha
		{
			if(txdData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
			{
				txdData.bitsPerPixel0 = 4358; // Set this to the proper 8-bit value
				txdData.ddsType = 9472; // Set this to the proper 8-bit value with alpha
			}
			else if(txdData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
			{
				txdData.bitsPerPixel0 = 4354; // Set this to the proper 16-bit value
				txdData.ddsType = 768; // Set this to the proper 16-bit value with alpha
			}
			else // Otherwise, it's probably 32 bits per pixel
			{
				txdData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
				txdData.ddsType = 1280; // Set this to the 32-bit value with alpha









if(number > 16) // Cheap way to see if they're packing a level
txdData.ddsType = 38144; // Force it to be right









			}
		}
		else // Otherwise, if it doesn't have alpha
		{
			if(txdData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
			{
				txdData.bitsPerPixel0 = 4358; // Set this to the proper 8-bit value
				txdData.ddsType = 9728; // Set this to the proper 8-bit value with alpha
			}
			else if(txdData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
			{
				txdData.bitsPerPixel0 = 4354; // Set this to the proper 16-bit value
				txdData.ddsType = 512; // Set this to the proper 16-bit value with alpha
			}
			else // Otherwise, it's probably 32 bits per pixel
			{
				txdData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
				txdData.ddsType = 1536; // Set this to the 32-bit value with alpha
			}
		}
	}
	txdData.ddsSize0 = size - 12; // Set the first file size value
	txdData.ddsSize1 = size - 36; // Set the other one
	txdData.width = ddsData.width; // Set the width
	txdData.height = ddsData.height; // Set the height
	txdData.imageSize = txdData.width * txdData.height; // Give it the proper pixels
	txdData.imageSize *= txdData.bitsPerPixel1 / 8; // Give it the proper size
	if(ddsData.format.type > 0x30) // If it's DXTn
		txdData.imageSize /= 4; // It needs to be divided by four
	txdData.mipMaps = ddsData.mipMaps + 1; // Set the number of mip-maps

	ddsName = new char[64]; // Initialize the variable we'll use here
	strcpy(ddsName, files[0]); // Copy the file name to be used here
	ddsName = strrchr(ddsName, '\\') + 1; // Go to the file part, leaving the directory
	*(strrchr(ddsName, '.')) = 0; // Null-terminate the part we don't need
	for(i = 0; i < 64; i++) // For the length of the .TXD's .DDS file name
		if(ddsName[i] != 0) // Until we reach the null-termination
			txdData.fileName[i] = ddsName[i]; // Copy the characters
		else // When we reach the end
			break; // Get out of this loop
	while(i < 64) // And until the rest is filled out
	{
		txdData.fileName[i] = 0; // Put null characters
		i++; // Increment the index variable
	}

	fwrite(&txdData, sizeof(txdData), 1, outputTXD); // Write the header out
	if(txdData.bitsPerPixel1 == 8) // It it's a palleted one
		fseek(outputTXD, -4, SEEK_CUR); // We have to move back four bytes

	while(!feof(inputDDS)) // For the rest of the picture data
		fputc(fgetc(inputDDS), outputTXD); // Copy them over
	fseek(outputTXD, -1, SEEK_CUR); // Go back one byte that's run over in that loop

	fclose(inputDDS); // Close the .DDS file we're done with	
	printf("\n\tPacked: %s.dds", txdData.fileName); // Output the file we've packed

	for(i = 1; i < number; i++)
	{
		txdSubData.identifyingBytes0 = 335609855;
		txdSubData.identifyingBytes1 = 335609855;
		txdSubData.identifyingBytes2 = 335609855; // Set the proper version
		txdSubData.eight = 8;
		txdSubData.four = 4;
		txdSubData.one = 1;
		txdSubData.three = 3;
		txdSubData.twentyOne = 21;
		txdSubData.zero = 0; // Set all the constants

		inputDDS = fopen(files[i], "rb"); // Open the first .DDS to read from
		if(inputDDS == NULL) // If it didn't open
			return 2; // Return the error

		fseek(inputDDS, 0, SEEK_END); // Go to the end of the file
		size = ftell(inputDDS); // Read the size of the file into our variable for it
		fseek(inputDDS, 0, SEEK_SET); // Go back to the beginning
		fread(&ddsData, sizeof(ddsData), 1, inputDDS); // Read the header data

		txdSubData.alphaFlag = ddsData.format.flags % 2; // Set the alpha flag properly
		txdSubData.bitsPerPixel1 = ddsData.format.bitsPerPixel; // Set the bits per pixel
		if(ddsData.format.type > 0x30) // If it's DXTn
		{
			txdSubData.dxtType = ddsData.format.type - 0x30; // Set that in the .TXD
			if(txdSubData.alphaFlag == 1) // If it has alpha
			{
				if(txdSubData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4354; // Set this to the proper 8-bit value
					txdSubData.ddsType = 9472; // Set this to the unknown 8-bit value with alpha
				}
				else if(txdSubData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4358; // Set this to the proper 16-bit value
					txdSubData.ddsType = 33024; // Set this to the proper 16-bit value with alpha
				}
				else // Otherwise, it's probably 32 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
					txdSubData.ddsType = 38400; // Set this to the 32-bit value with alpha
				}
			}
			else // Otherwise, if it doesn't have alpha
			{
				if(txdSubData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4354; // Set this to the proper 8-bit value
					txdSubData.ddsType = 9728; // Set this to the unknown 8-bit value with alpha
				}
				else if(txdSubData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4358; // Set this to the proper 16-bit value
					txdSubData.ddsType = 33280; // Set this to the proper 16-bit value with alpha
				}
				else // Otherwise, it's probably 32 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
					txdSubData.ddsType = 38144; // Set this to the 32-bit value with alpha
				}
			}
		}
		else // Otherwise, it's RGBA
		{
			txdSubData.dxtType = 0; // Set it to zero
			if(txdSubData.alphaFlag == 1) // If it has alpha
			{
				if(txdSubData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4358; // Set this to the proper 8-bit value
					txdSubData.ddsType = 9472; // Set this to the proper 8-bit value with alpha
				}
				else if(txdSubData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4354; // Set this to the proper 16-bit value
					txdSubData.ddsType = 768; // Set this to the proper 16-bit value with alpha
				}
				else // Otherwise, it's probably 32 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
					txdSubData.ddsType = 1280; // Set this to the 32-bit value with alpha









if(number > 16) // Cheap way to see if they're packing a level
txdSubData.ddsType = 38144; // Force it to be right









				}
			}
			else // Otherwise, if it doesn't have alpha
			{
				if(txdSubData.bitsPerPixel1 == 8) // If it's 8 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4358; // Set this to the proper 8-bit value
					txdSubData.ddsType = 9728; // Set this to the proper 8-bit value with alpha
				}
				else if(txdSubData.bitsPerPixel1 == 16) // If it's 16 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4354; // Set this to the proper 16-bit value
					txdSubData.ddsType = 512; // Set this to the proper 16-bit value with alpha
				}
				else // Otherwise, it's probably 32 bits per pixel
				{
					txdSubData.bitsPerPixel0 = 4353; // Set this to the 32-bit value
					txdSubData.ddsType = 1536; // Set this to the 32-bit value with alpha
				}
			}
		}
		txdSubData.ddsSize0 = size - 12; // Set the first file size value
		txdSubData.ddsSize1 = size - 36; // Set the other one
		txdSubData.width = ddsData.width; // Set the width
		txdSubData.height = ddsData.height; // Set the height
		txdSubData.imageSize = txdSubData.width * txdSubData.height; // Give it the proper pixels
		txdSubData.imageSize *= txdSubData.bitsPerPixel1 / 8; // Give it the proper size
		if(ddsData.format.type > 0x30) // If it's DXTn
			txdSubData.imageSize /= 4; // It needs to be divided by four
		txdSubData.mipMaps = ddsData.mipMaps + 1; // Set the number of mip-maps

		ddsName = new char[64]; // Initialize the variable we'll use here
		strcpy(ddsName, files[i]); // Copy the file name to be used here
		ddsName = strrchr(ddsName, '\\') + 1; // Go to the file part, leaving the directory
		*(strrchr(ddsName, '.')) = 0; // Null-terminate the part we don't need
		for(j = 0; j < 64; j++) // For the length of the .TXD's .DDS file name
			if(ddsName[j] != 0) // Until we reach the null-termination
				txdSubData.fileName[j] = ddsName[j]; // Copy the characters
			else // When we reach the end
				break; // Get out of this loop
		while(j < 64) // And until the rest is filled out
		{
			txdSubData.fileName[j] = 0; // Put null characters
			j++; // Increment the index variable
		}

		fwrite(&txdSubData, sizeof(txdSubData), 1, outputTXD); // Write the header out
		if(txdSubData.bitsPerPixel1 == 8) // It it's a palleted one
			fseek(outputTXD, -4, SEEK_CUR); // We have to move back four bytes

		while(!feof(inputDDS)) // For the rest of the picture data
			fputc(fgetc(inputDDS), outputTXD); // Copy them over
		fseek(outputTXD, -1, SEEK_CUR); // Go back one byte that's run over in that loop

		fclose(inputDDS); // Close the .DDS file we're done with	
		printf("\n\tPacked: %s.dds", txdSubData.fileName); // Output the file we've packed
	}

	size = ftell(outputTXD); // Get the size of the .TXD
	size += 12; // Set the size to what we can use in the .TXD header
	fseek(outputTXD, 4, SEEK_SET); // Rewind to where the size is
	fwrite(&size, 4, 1, outputTXD); // Write the proper size

	fseek(outputTXD, -1, SEEK_END); // Go back to where we were at the end

	for(i = 0; i < 2; i++) // Write this termination data twice
	{
		fputc(3, outputTXD);	fputc(0, outputTXD);
		fputc(0, outputTXD);	fputc(0, outputTXD);

		fputc(0, outputTXD);	fputc(0, outputTXD);
		fputc(0, outputTXD);	fputc(0, outputTXD);
	
		fputc(255, outputTXD);	fputc(255, outputTXD);
		fputc(0, outputTXD);	fputc(20, outputTXD);
	}

	fclose(outputTXD); // Close the .TXD, and we're done

	return 0; // No errors!
}
