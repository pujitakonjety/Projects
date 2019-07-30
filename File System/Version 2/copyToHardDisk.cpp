#include"stdafx.h"
#include"declarations.h"
void copyToHardDisk(char *filename,struct metadataTable *head,char *harddisk){
	/*int i;
	for (i = filesblocks; i < totalblocks; i++){
		if (head->blocks[i].value == (unsigned)0)
			break;
	}
	FILE *fp = fopen(harddisk, "rb+");
	if (fp == NULL){
		printf("file not existed");
		return;
	}
	unsigned int start_pnt = i*blocksize;
	fseek(fp, start_pnt, SEEK_CUR);
	FILE *fq = fopen(filename, "rb");
	char ch = 'a';
	unsigned int bytes_count = 0;
	head->files[head->no_of_files] = createEntry(filename);
	head->files[head->no_of_files]->start_block = i;
	head->no_of_files++;
	while (fread(&ch, sizeof(char), 1, fq)){
		fwrite(&ch, sizeof(char), 1, fp);
		bytes_count++;
	}
	unsigned int number_of_blocks = floor(bytes_count);
	head->files[head->no_of_files - 1]->blocks_count = number_of_blocks;
	head->files[head->no_of_files - 1]->length = bytes_count;
	while (number_of_blocks--){
		head->blocks[i++].value= (unsigned)1;
	}
	fclose(fq);
	fclose(fp);*/
	
	FILE *fq = fopen(filename, "rb");
	fseek(fq, 0, SEEK_END);
	unsigned int file_size = ftell(fq);
	rewind(fq);
	//fclose(fq);
	unsigned int number_of_blocks = floor(file_size);
	unsigned int count = 0,block_ind = 0;
	for (unsigned int i = filesblocks; i < totalblocks; i++){
		 block_ind = i;
		while (head->blocks[i].value == (unsigned int)0){
			count++;
			i++;
		}
		if (count == number_of_blocks)
			break;
		count = 0;
	}

	head->files[head->no_of_files] = createEntry(filename);
	head->files[head->no_of_files]->start_block = block_ind;
	for (unsigned int i = 0; i < number_of_blocks; i++){
		head->blocks[block_ind].value = (unsigned int)1;
		block_ind++;

	}
	block_ind = head->files[head->no_of_files]->start_block;
	head->files[head->no_of_files]->blocks_count = number_of_blocks;
	head->files[head->no_of_files]->length = file_size;
	head->no_of_files++;
	char *buffer = (char*)malloc(BLOCK_SIZE*sizeof(char));
	for (unsigned int i = 0; i < number_of_blocks; i++){
		//memcpy(buffer, fq, sizeof(buffer));
		if (file_size>BLOCK_SIZE)
			fread(buffer,BLOCK_SIZE,1, fq);
			//fread(buffer, sizeof(char), BLOCK_SIZE, fq);
		else
			fread(buffer,file_size,1, fq);
			//fread(buffer, sizeof(char), file_size, fq);
		file_size -= BLOCK_SIZE;
		writeToDisk(buffer, harddisk, block_ind);
		block_ind++;
	}
	fclose(fq);

}