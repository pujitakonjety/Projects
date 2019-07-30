// Harddisk(3).cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include"Declarations.h"
void processCommand(char *command, char *option, char *source_file, char *dest_file){
	char *token;
	token = strtok(command, " ");

	strcpy(option, token);
	token = strtok(NULL, " ");
	if (token!=NULL)
	strcpy(source_file, token);
	token = strtok(NULL, " ");
	if (token != NULL)
	strcpy(dest_file, token);

}
unsigned int findNumber(char *number){
	unsigned int val = 0;
	for (int i = 0; number[i] != '\0'; i++)
		val = val*(number[i] - '0');
	return val;
}

int _tmain(int argc, _TCHAR* argv[])
{
	struct metadataTable *head = NULL;
	while (1){

		printf(">");
		char command[100];
		gets(command);
		char option[20], source_file[20], dest_file[20];
		processCommand(command, option, source_file, dest_file);

		if (strcmp(command, "MOUNT") == 0 || strcmp(command, "mount") == 0)
			head = init();

		else if (strcmp(command, "COPYTOFS") == 0 || strcmp(command, "copytofs") == 0)
			copyToFs(source_file, dest_file,head);

		else if (strcmp(command, "COPYFROMFS") == 0 || strcmp(command, "copyfromfs") == 0)
			copyFromFs(source_file, dest_file,head);

		else if (strcmp(command, "FORMAT") == 0 || strcmp(command, "format") == 0){
			printf("NOT Written");
		}
		else if (strcmp(command, "EXIT") == 0 || strcmp(command, "exit") == 0){
			printf("Exporting metadata to harddisk..\n");
			writeToDisk(head, 0);
			printf("Exporting metadata to harddisk done..\n");
			return 0;
		}
		else if (strcmp(command, "LS") == 0 || strcmp(command, "ls") == 0){
			for (unsigned int i = 0; i < head->no_of_files; i++)
				printf("%s\n", head->files[i].filename);

		}
		else if (strcmp(command, "DELETE") == 0 || strcmp(command, "delete") == 0){
			
			DeleteFile(head,source_file);
		}
		else if (strcmp(command, "DEBUG") == 0 || strcmp(command, "debug") == 0){
			MetaDataInfo(head);
		}
	}
	return 0;
}


