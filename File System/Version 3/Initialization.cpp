#include"stdafx.h"
#include"Declarations.h"

struct metadataTable*  init(){
	char *buffer = (char*)malloc(BLOCK_SIZE*sizeof(char));
	//void *buffer = malloc(BLOCK_SIZE*sizeof(char));
	readFromDisk(buffer, (unsigned int)0);
	struct metadataTable *head = (struct metadataTable*)malloc(sizeof(struct metadataTable));
	unsigned int magic_number = 0x444E524D;

	memcpy(head, buffer, sizeof(struct metadataTable));
	/*memcpy(&head->magicnumber, buffer, sizeof(unsigned int));
	memcpy(&head->no_of_files, buffer + 4, sizeof(unsigned int));
	memcpy(head->blocks, buffer + 8, sizeof(BLOCK_SIZE * 4));
	memcpy(head->files,buffer+25608,)*/

	if (head->magicnumber == magic_number){
		return head;
	}
		
	printf("format disk??");
	printf("y/n");
	char ch = 'a';
	scanf("%c", &ch);
	fflush(stdin);
	if (ch == 'y'){
		head->no_of_files =(unsigned int) 0;
		head->magicnumber = magic_number;
		for (unsigned int i = 0; i < TOTAL_BLOCKS; i++)
			head->blocks[i] = '0';
		memcpy(buffer, head, sizeof(struct metadataTable));
		writeToDisk(buffer, (unsigned int)0);
	}
	return head;
}

void readFromDisk(void *buffer, unsigned int block_ind){
	FILE *fp = fopen(HARD_DISK, "rb+");
	if (fp == NULL){
		printf("NOT Existed \n");
		return;
	}
	fseek(fp, block_ind * BLOCK_SIZE, SEEK_SET);
	fread(buffer, 1, BLOCK_SIZE, fp);
	fclose(fp);
}

void writeToDisk(void *buffer, unsigned int block_ind){
	FILE *fp = fopen(HARD_DISK, "rb+");
	if (fp == NULL){
		printf("NOT Existed \n");
		return;
	}
	fseek(fp, block_ind * BLOCK_SIZE, SEEK_SET);
	fwrite(buffer, 1, BLOCK_SIZE, fp);
	fclose(fp);
}

