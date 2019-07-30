#include"stdafx.h"
#include"declarations.h"
int metadataIntoDisk(struct metadataTable *head, char *harddisk){
	char buffer[BLOCK_SIZE];
	memcpy(buffer, head, sizeof(head));
	writeToDisk(buffer, harddisk,0);
	return 0;
}
