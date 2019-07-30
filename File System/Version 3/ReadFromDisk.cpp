#include"stdafx.h"
#include"Declarations.h"
void writeToBuffer(char *buffer, unsigned int block_ind, char *harddisk){
	FILE *fp = fopen(harddisk, "rb+");
	char ch = 'a';
	fseek(fp, (block_ind)*BLOCK_SIZE, SEEK_CUR);
	fread(buffer, sizeof(char), BLOCK_SIZE, fp);
	fclose(fp);
}