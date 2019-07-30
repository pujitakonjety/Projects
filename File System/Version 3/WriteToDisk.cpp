#include"stdafx.h"
#include"Declarations.h"
void writeToDisk(char *buffer, char *harddisk, int block_ind){
	FILE *fp = fopen(harddisk, "rb+");
	fseek(fp, block_ind*BLOCK_SIZE, SEEK_CUR);
	fwrite(buffer, BLOCK_SIZE, 1, fp);
	fclose(fp);
}
