#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define BLOCK_SIZE (16*1024)
#define FILE_BLOCKS (3)
#define TOTAL_BLOCKS (6400)
#define NUM_FILES (32)
#define HARD_DISK "harddisk.hdd"

struct metadata{
	char filename[20];
	unsigned int start_block;
	unsigned int blocks_count;
	unsigned int length;
};
struct metadataTable{
	unsigned int magicnumber;
	unsigned int no_of_files;
	char blocks[TOTAL_BLOCKS];
	struct metadata files[32];
};

struct metadataTable*  init();
void readFromDisk(void *buffer, unsigned int block_ind);
void writeToDisk(void *buffer, unsigned int block_ind);
void copyToFs(char *source_file, char*dest_file, struct metadataTable *head);
void copyFromFs(char *sourcefile, char *destfile, struct metadataTable *head);
void writeToDisk(void *buffer, unsigned int block_ind);
void DeleteFile(struct metadataTable *head, char *name);
void MetaDataInfo(struct metadataTable *head);



