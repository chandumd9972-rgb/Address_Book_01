/*
   Name : Chandu M D
   Date : 28 oct 2025
   Description : MP3 Tag reader and editor 
	       * it will reads, displays, and modifies ID3v2 metadata (like title, artist, album, and year) of MP3 files.
               * It helps users easily view and edit song information directly from the command line.
*/


#ifndef header_h
#define header_h


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int validate_file(int, char *argv[]);
int validate_args(int, char* []);
void mp3_view(int, char* []);
int mp3_edit(int, char* []);
void big_little_endian(int *);


#endif
