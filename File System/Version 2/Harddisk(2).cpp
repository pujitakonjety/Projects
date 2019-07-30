// Harddisk(2).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"declarations.h"



int _tmain(int argc, _TCHAR* argv[])
{
	char harddisk[100];
	printf("harddisk:");
	scanf("%s", harddisk);
	struct metadataTable *head = (struct metadataTable*)malloc(sizeof(struct metadataTable));
	head->no_of_files = 0;
	for (int i = 0; i < totalblocks; i++){
		head->blocks[i].value = (unsigned)0;
	}
	fflush(stdin);
	while (1){
		
		printf(">"); 
		char options[50];
		gets(options);

		if (isEqual(options, "copytodisk")||isEqual(options,"COPYTODISK")){
			char *filename = get_filename(options);
			copyToHardDisk(filename, head,harddisk);
		}
		else if (isEqual(options, "copyfromdisk") || isEqual(options,"COPYFROMDISK")){

			char *token = strtok(options, " ");
			token = strtok(NULL, " ");
			char *filename = token;
			token = strtok(NULL, " ");
			char *dest = token;

			//char *dest = get_dest_filename(options);
			//char*filename = get_filename(options);
			copyFromDisk(filename ,dest, harddisk, head);
		}
		else if (strcmp(options, "ls") == 0 || strcmp(options, "LS")){
			for (int i = 0; i < head->no_of_files; i++){
				printf("%s\n", head->files[i]->filename);
			}
		}
		else if (isEqual(options,"delete")){
			char *token = strtok(options, " ");
			token = strtok(NULL, " ");
			token = strtok(NULL, " ");
			char *filename = token;
			deleteFromDisk(head, filename);
		}
		fflush(stdin);

	}
	return 0;
}

