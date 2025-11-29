/*
   Name : Chandu M D
   Date : 28 oct 2025
   Description : MP3 Tag reader and editor 
	       * it will reads, displays, and modifies ID3v2 metadata (like title, artist, album, and year) of MP3 files.
               * It helps users easily view and edit song information directly from the command line.
*/

#include "mp3_header.h"
int main(int argc, char* argv[])
{
	if(validate_args(argc, argv) == 0)
	{
		return 0;
	}

	if(strcmp(argv[1] , "-v") == 0)
	{
		mp3_view(argc, argv);
	}
	if(strcmp(argv[1] , "-e") == 0)
	{
		mp3_edit(argc, argv);
	}
	return 0;
}
