#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define BLOCK_SIZE (16*1024)
#define filesblocks 3
#define totalblocks 6400
struct boolean{
	unsigned int value : 1;
};
struct metadataTable{
	unsigned int magicnumber;
	unsigned int no_of_files;
	struct boolean blocks[totalblocks];
	struct metadata *files[32];
};
struct metadata{
	char filename[20];
	unsigned int start_block;
	unsigned int blocks_count;
	unsigned int length;
};
int isEqual(char *inp1, char *inp2);

struct metadata* createEntry(char *file_name);
char *get_filename(char *options);
unsigned  floor(int val);
void copyToHardDisk(char *filename, struct metadataTable *head, char *harddisk);
char *get_dest_filename(char *options);
void copyFromDisk(char *filename, char *dest, char *harddisk, struct metadataTable *head);
void writeToDisk(char *buffer, char *harddisk, int block_ind);
void writeToBuffer(char *buffer, unsigned int block_ind, char *harddisk);
void deleteFromDisk(struct metadataTable *head, char *filename);