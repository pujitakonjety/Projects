#include"stdafx.h"
#include"declarations.h"
void copyFromDisk(char *filename, char *dest, char *harddisk, struct metadataTable *head){
	char *buffer = (char*)malloc(sizeof(char)*(BLOCK_SIZE));

	FILE *fp = fopen(dest, "wb");
	if (fp == NULL){
		printf("not existed");
		return;
	}
	for (int idx = 0; idx < head->no_of_files; idx++){
		if (strcmp(head->files[idx]->filename, filename) == 0){
			unsigned int ind = head->files[idx]->start_block;
			unsigned int file_size = head->files[idx]->length;
			for (unsigned int i = 0; i < head->files[idx]->blocks_count; i++){
				writeToBuffer(buffer, ind,harddisk);
				if (file_size < (BLOCK_SIZE)){
					fwrite(buffer, file_size, 1, fp);
					break;
				}
				else{
					fwrite(buffer, BLOCK_SIZE, 1, fp);
				}
					
				file_size -= (BLOCK_SIZE);
				ind++;
			}
			fclose(fp);
			return;

		}
	}
}