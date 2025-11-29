/*
   Name : Chandu M D
   Date : 28 oct 2025
   Description : MP3 Tag reader and editor 
	       * it will reads, displays, and modifies ID3v2 metadata (like title, artist, album, and year) of MP3 files.
               * It helps users easily view and edit song information directly from the command line.
*/


#include "mp3_header.h"
//including all the header files
void mp3_view(int argc, char *argv[])
{
	char* M[6] = {"Title     : ", "Artist    : ", "Album     : ", "Year      : ", "Music     : ", "Comment   : "};

	validate_file(argc, argv);		 //validating the file that is mp3 file or not.
	
	FILE *fp = fopen(argv[2],"r");   //here opening the file if file not there printing the error message.
	if(fp == NULL)                   //condition checking if file pointer is equal to null address then file is not exist.
	{
		printf("there is no such file.\n");
		exit(0);
	}

	char buffer[4];			                //taking an character buffer of size 4 bytes including null character.
	fread(buffer, (sizeof(buffer) - 1), 1, fp);     //here reading first 3 bytes from file to buffer.
	buffer[3] = '\0';
	int r = strcmp(buffer,"ID3");                   //compare the buffer with ID3 to check for mp3 tag.
	if(r == 0)
	{
		printf("%s is a mp3 file\n", argv[2]);
	}
	else
	{
		printf("Error, %s is not a mp3 file.\n", argv[2]);
		exit(0);
	}
	printf("--------------------------------------------------------------------------\n");
	printf("mp3 Tag Reader and Editor for ID3v2\n");
	printf("--------------------------------------------------------------------------\n");

	fseek(fp,7,SEEK_CUR);		      //moving the file pointer 7 bytes ahead from the current position to skip header data.

	for(int i = 0;i < 6;i++)
	{
		printf("%s",M[i]);

		char tag[5];			       //taking an character tag 5 bytes including null character.
		fread(tag, (sizeof(tag) - 1), 1, fp); //here reading an 4 bytes data from file to tag.

		int size;			     //declare an integer variable to store the frame size.
		fread(&size, sizeof(int), 1, fp);   //read 4 bytes from file to size.
		big_little_endian(&size);	   //convert the size value from big-endian to little-endian syatem.

		fseek(fp, 3, SEEK_CUR);  	  //moving the file pointer 3 bytes ahead from the current position .
				
		char content[size];                //create an character array to store the frame content.
		for(int k=0; k<(size-1); k++)     //loop to read (size-1) bytes of data from file.
		{
			fread(&content[k], sizeof(char), 1, fp);   //read one character at a time into the content array.
		}
		content[size - 1] = '\0';                         //add null terminator to make it valid string.

		printf("      %s\n", content);                    //print the tag content.
	}

	printf("--------------------------------------------------------------------------\n");
	fclose(fp);                                             //close the file.

}

void big_little_endian(int *size)        //function to convert the 4 byte integer from big-endian to little-endian format.
{
	char* ptr = (char*)size;	//create a character pointer to access each byte of integer

	for(int i=0; i<2; i++)
	{
		char temp = ptr[i];     //temporarily store the byte at position i.
		ptr[i] = ptr[3 - i];   //swap byte i with its corresponding byte.
		ptr[3 - i] = temp;    //complete the byte swap.
	}
}

int validate_file(int argc, char* argv[])     //function to validate the file is .mp3 or not.
{
	int l = strlen(argv[2]);    //taking the length of the file
	if(argv[2][l-4] == '.' && argv[2][l-3] == 'm' && argv[2][l-2] == 'p' && argv[2][l-1] == '3') 
	//condition to check the given file is .mp3 or not.
	{
		return 1;
	}
	else
	{
		printf("------------------------------------------------------------------------------------\n");
		printf("Error: ");
		for(int i = 0; i < argc; i++)
		{
			printf("%s ",argv[i]);
		}
		printf(" : INVALID ARGUMENTS\nUSAGE : \n");
		printf("To View please send command like this : ./a.out -v mp3filename\n");
		printf("To Edit please send command like this : ./a.out -e -t/-a/-A/-y/-C/-c New_name mp3filename\n");
		printf("To Get help please send command like this : ./a.out --help\n");
		printf("------------------------------------------------------------------------------------\n");
		return 0;
	}
}

int validate_args(int argc, char *argv[]) //function to validate the command line arguments.
{
	if(argc == 2)
	{
		  if((strcmp(argv[1],"--help") == 0))
        	{
                printf("----------------------------------------------------------------------\n");
                printf("usage : mp3tag -[taAyCc] value file1\n");
                printf("        mp3tag -v\n");
                printf("-t      Modifies a Title tag\n");
                printf("-a      Modifies a Artist tag\n");
                printf("-A      Modifies a Album tag\n");
                printf("-y      Modifies a Year tag\n");
                printf("-C      Modifies a Content tag\n");
                printf("-c      Modifies a Comment tag\n");
                printf("------------------------------------------------------------------------\n");
		return 1;
        	}
	}
	if(argc == 3)
	{
	
		if(strcmp(argv[1], "-e") == 0)
		{
			printf("------------------------------------------------------------------------------------\n");
			printf("Error: ");
			for(int i = 0; i < argc; i++)
			{
				printf("%s ",argv[i]);
			}
			printf(" : INVALID ARGUMENTS\nUSAGE : \n");
			printf("To View please send command like this : ./a.out -v mp3filename\n");
			printf("To Edit please send command like this : ./a.out -e -t/-a/-A/-y/-C/-c New_name mp3filename\n");
			printf("To Get help please send command like this : ./a.out --help\n");
			printf("------------------------------------------------------------------------------------\n");
			return 0;

		}
		if(strcmp(argv[1], "-v"))
		{
   			printf("------------------------------------------------------------------------------------\n");
                	printf("Error: ");
                	for(int i = 0; i < argc; i++)
                	{
                        	printf("%s ",argv[i]);
                	}
                	printf(" : INVALID ARGUMENTS\nUSAGE : \n");
			printf("To View please send command like this : ./a.out -v mp3filename\n");
			printf("To Edit please send command like this : ./a.out -e -t/-a/-A/-y/-C/-c New_name mp3filename\n");
			printf("To Get help please send command like this : ./a.out --help\n");
                	printf("------------------------------------------------------------------------------------\n");
			return 0;
		}
	}
	if(argc == 5 && (strcmp(argv[1], "-e")))
	{
   		printf("------------------------------------------------------------------------------------\n");
                printf("Error: ");
                for(int i = 0; i < argc; i++)
                {
                        printf("%s ",argv[i]);
                }
                printf(" : INVALID ARGUMENTS\nUSAGE : \n");
		printf("To View please send command like this : ./a.out -v mp3filename\n");
		printf("To Edit please send command like this : ./a.out -e -t/-a/-A/-y/-C/-c New_name mp3filename\n");
		printf("To Get help please send command like this : ./a.out --help\n");
                printf("------------------------------------------------------------------------------------\n");
                return 0;
	}
	if(argc == 3 || argc == 5)
	{
		return 1;
	}

	printf("------------------------------------------------------------------------------------\n");
	printf("Error: ");
	for(int i = 0; i < argc; i++)
	{
		printf("%s ",argv[i]);
	}
	printf(" : INVALID ARGUMENTS\nUSAGE : \n");
	printf("To View please send command like this : ./a.out -v mp3filename\n");
	printf("To Edit please send command like this : ./a.out -e -t/-a/-A/-y/-C/-c New_name mp3filename\n");
	printf("To Get help please send command like this : ./a.out --help\n");
	printf("------------------------------------------------------------------------------------\n");

	return 0;
}	
