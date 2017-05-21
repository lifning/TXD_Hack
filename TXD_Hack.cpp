#include "stdafx.h"
#include "txdstruct.h"
#include "ddsstruct.h"
#include "txdunpack.h"
#include "txdpack.h"
int main(int argc, char *argv[])
{
	int i;
	char *file;

	printf("Lightning's Sonic Heroes PC .TXD Utility\n");

	if(argc <= 1)
	{
		printf("\n\tUnpack: TXD_Hack [.TXD File]");
		printf("\n\tPack: TXD_Hack [.DDS File] [.DDS File] [.DDS File] ...");
	}
	else if(argc == 2)
		unpackTXD(argv[1]);
	else
	{
		file = argv[0];
		for(i = 0; i < argc - 1; i++)
			argv[i] = argv[i + 1];
		argv[argc - 1] = file;
		argc--;
		for(i = 0; i < argc / 2; i++)
		{
			file = argv[i];
			argv[i] = argv[argc - i - 1];
			argv[argc - i - 1] = file;
		}
		packTXD(argv, argc);
	}

	printf("\n\nDone.");
	return 0;
}