/*
   Name : Chandu M D
   Date : 28 oct 2025
   Description : MP3 Tag reader and editor 
	       * it will reads, displays, and modifies ID3v2 metadata (like title, artist, album, and year) of MP3 files.
               * It helps users easily view and edit song information directly from the command line.
*/

#include"mp3_header.h"
int mp3_edit(int argc, char  *argv[])

{
	char *in[6] = {"-t","-a","-A","-y","-c","-C"};
	char *input[6] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};
	char *b[6] = {"Title","Artist","Album","Year","Content","Comment"};
	int temp;
	int value = 0;
	for(int i = 0;i < 6;i++)
	{
		if(strcmp(argv[2],in[i]) == 0)
		{
			temp = i;
			value = 1;
			break;	
		}

	}
	//validating the arguments.

	if(value == 0)
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

	int len = strlen(argv[3]);	                         //calculate the length of the new name.
	FILE *fp = fopen(argv[4] , "r");                         //open the file sample.mp3 file in read mode.
	FILE *pf = fopen("temp.mp3" , "w");                      //open the file temp.mp3 file in write mode.
	if(fp == NULL)
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
		printf("File not present.\n");
		remove("temp.mp3");
		return 0;
	}

	char buffer[4];			                      //taking an character buffer of size 4 bytes including null character.
	fread(buffer, (sizeof(buffer) - 1), 1, fp);             //here reading first 3 bytes from file to buffer.
	buffer[3] = '\0';

	if(!(strcmp(buffer,"ID3") == 0))                       //compare the buffer with ID3 to check for mp3 tag.
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
		remove("temp.mp3");
		return 0;
	}
	
	fwrite(buffer, (sizeof(buffer) - 1), 1, pf);           //here writing 3 bytes of data from buffer to output file.

	char header[8];                                        //create a character header of 8 bytes.
	fread(header, (sizeof(header)-1), 1, fp);              //reading 7 bytes of heder from input file to header.
	header[7] = '\0';                                      //add null terminator.
	fwrite(header, (sizeof(header)-1), 1, pf);             //write the 7 bytes of header data into the output file.

	for(int i=0; i<6; i++)
	{
		char tag[5];                                    //create a character tag of 5 bytes.
		fread(tag, (sizeof(tag) - 1), 1, fp);           //reading 4 bytes of tag from input file to tag.
		tag[4] = '\0';	                                //add null terminator. 

		int flag = 0;                                   //initialize flag variable to zero.
		if(strcmp(tag, input[temp]) == 0)              // Check if the string 'tag' matches the string stored in input[temp].
		{
			flag = 1;
		}

		fwrite(tag, (sizeof(tag) - 1), 1, pf);          //writing 4 bytes of tag from tag to output file.

		int size;                                   
		fread(&size, 4, 1, fp);                         //read 4 byte of data from input file.
		if(flag == 1)
		{

			len = len + 1;

			//printf("length = %d\n",len);
			big_little_endian(&len);                 //convert the value of len from big-endian to little-endian syatem.
			//printf("length = %d\n",len);
			fwrite(&len, sizeof(int), 1, pf);       //writing the 4 byte of data to output file.
		}
		else
		{
			fwrite(&size, 4, 1, pf);                   //write 4 byte size value to the output file.
		}

		char flg[4];                                      //declare character variable of 4 bytes.
		fread(flg, 3, 1, fp);                             //read the 3 byte of data from input file.
		flg[3] = '\0';                                    //add null terminator.
		fwrite(flg, 3, 1, pf);                            //write 3 byte data to output file.

		//printf("%d\n",size);
		big_little_endian(&size);                         //convert size to correct endian format.
		//printf("%d\n",size);

		if(flag == 1)
		{
			big_little_endian(&len);                   //convert len to correct endian format.

			char s1[len];                             //declare character .
			strcpy(s1, argv[3]);                      //string copy to the 
			s1[len - 1] = '\0';
			//printf("%s\n",s1);
			fwrite(s1, (sizeof(s1) - 1), 1, pf);
			fseek(fp, size-1, SEEK_CUR);

		}
		else
		{
			char s[size];
			for(int j = 0; j < (size - 1); j++)
			{
				fread(&s[j], sizeof(char), 1, fp);
				fwrite(&s[j], sizeof(char), 1, pf);
			}
			s[size - 1] = '\0';
		}
	}
	printf("\n----------------Select Edit option---------------------------\n"   );
	
	printf("------------------Select %s change option-----------------------\n",b[temp]);

	printf("		%s  :  %s\n",b[temp],argv[3]                 );

	printf("----------------%s Changed Succesfully--------------------\n\n",b[temp]);

	int p = ftell(fp);                                    //get the current position of file pointer and store it in p.
	//printf("%d\n",p);
	fseek(fp, p, SEEK_END);                              //move file pointer to the end of the file.
	int e = ftell(fp);                                   //get the position of the end of the file.
	//printf("%d\n",e);
	rewind(fp);                                          //move file pointer to begining of the file.
	fseek(fp, p, SEEK_CUR);                              //move file pointer to the original saved position of p.
	char c;                                              //declare character variable to store data while copying.
	for(int i = p; i <= e; i++)
	{
		fread(&c,1,1,fp);                           //read one byte from input file.
		fwrite(&c,1,1,pf);                          //write that byte to output file.
	}

	remove(argv[4]);                                //removing the input file sample.mp3
	rename("temp.mp3",argv[4]);                     //rename the output file (temp.mp3 to sample.mp3).

	fclose(fp);                                          //close the input file.
	fclose(pf);    					     //close the output file.
	return 0;
}
