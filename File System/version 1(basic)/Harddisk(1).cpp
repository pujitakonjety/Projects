// Harddisk(1).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define max_limit 20

int isEqual(char *inp1,char *inp2){
	int i;
	for (i = 0; inp1[i] != '\0'&&inp1[i]!=' '; i++){
		if (inp1[i] != inp2[i])
			return 0;
	}
	if (inp2[i] == '\0')
		return 1;
	return 0;

}
struct metadata* createEntry(char *file_name){
	struct metadata *newentry = (struct metadata*)malloc(sizeof(struct metadata));
	strcpy(newentry->filename, file_name);
	return newentry;


}
char *get_filename(char *options){
	int i = 0, ptr = 0;
	while (options[i] != '\0'&&options[i] != ' ')
		i++;
	char *file_name = (char*)malloc(16 * sizeof(char));
	i++;
	while (options[i] != '\0')
		file_name[ptr++] = options[i++];
	file_name[ptr] = '\0';
	return file_name;
	
}
int _tmain(int argc, _TCHAR* argv[])
{
	//struct metadataTable *head = NULL;
	struct metadataTable *head = (struct metadataTable *)malloc(sizeof(struct metadataTable));
	FILE *fp = fopen("hardDisk.hdd", "rb+");
	rewind(fp);
	char ch = 'a';
	int p;
	for ( p = 0; p < (2 * 1024 * 1024); p++){
		fread(&ch, 1, 1, fp);
		if (ch != '\0')
			break;
	}
	fclose(fp);
	if (p>=(2*1024*1024)){
		for (int i = 0; i < 20; i++)
			head->files[i] = NULL;
	}
	else{
		fread(head, sizeof(head), 1, fp);
		for (int ind = 0; ind < max_limit; ind++){
			fread(head->files[ind], sizeof(head->files[ind]), 1, fp);
		}
	}
	fclose(fp);

	while (1){
		printf(">");
		char options[32];
		gets(options);
		if (isEqual(options, "copyto") || isEqual(options, "COPYTO")){
			FILE *fp = fopen("hardDisk.hdd", "rb+");
			rewind(fp);
			if (fp == NULL){
				printf("file no existed");
				continue;
			}
			
			
			char *file_name = get_filename(options);
			int i = 0;
			int files_count = 0;
			unsigned int start_ptr;

			if (head->files[0] == NULL)
				start_ptr = 2 * 1024 * 1024;
			else{
				while (head->files[i] != NULL)
					i++;
				files_count = i;
				start_ptr = head->files[i - 1]->length + head->files[i - 1]->offset;
			}
			


			FILE *fq = fopen(file_name, "rb+");
			if (fq == NULL){
				printf("file no existed");
				continue;
			}
			rewind(fp);
			fseek(fp, start_ptr, SEEK_CUR);
			char ch = 'a';
			int bytes_count = 0;
			while (fread(&ch, sizeof(char), 1, fq) != 0){
				if (fwrite(&ch, sizeof(char), 1, fp) == 0)
					printf("largefile");
				bytes_count++;
			}
			fclose(fq);
			fclose(fp);
			head->files[files_count] = createEntry(file_name);
			//strcpy(head->files[files_count]->filename, file_name);
			head->files[files_count]->length = bytes_count;
			head->files[files_count]->offset = start_ptr;
		}

		else if (isEqual(options, "Ls") || isEqual(options, "ls")){
			int i = 0;
			while (head->files[i] != NULL){
				printf("%s\n", head->files[i]->filename);
				i++;
			}
		}
		else if (isEqual(options, "DELETE") | isEqual(options, "delete")){
			char *file_name = get_filename(options);
			int i = 0, flag = 0;
			while (head->files[i] != NULL){
				if (strcmp(head->files[i]->filename, file_name) == 0){
					//int var = head->files[i]->length + head->files[i]->offset;
					//flag = 0;


					while (head->files[i] != NULL){

						if (head->files[i + 1] == NULL){
							head->files[i] = NULL;
							break;
						}
						strcpy(head->files[i]->filename, head->files[i + 1]->filename);
						head->files[i]->offset = head->files[i + 1]->offset;
						head->files[i]->length = head->files[i + 1]->length;
						i++;
					}
					/*head->files[i - 2] = NULL;
					flag = 1;
					break;*/
				}
				/*if (flag == 1)
					break;*/
				i++;
			}
		}
		else if (strcmp(options, "FORMAT") == 0 || (strcmp(options, "format") == 0)){
			for (int i = 0; i < max_limit; i++)
				head->files[i] = NULL;
		}
		else if (isEqual(options, "COPYFROM") || isEqual(options, "copyfrom")){
			char *file_name = get_filename(options);
			FILE *fq = fopen("hoooo.pdf", "wb");
			if (fq == NULL){
				printf("invalid file");
				continue;
			}
			for (int i = 0; head->files[i] != NULL; i++){
				if (strcmp(head->files[i]->filename, file_name) == 0){
					FILE *fp = fopen(head->files[i]->filename,"rb");

					char ch = 'a';
					int count = 0;
					while (fread(&ch, sizeof(char), 1, fp)!=0){
						fwrite(&ch, sizeof(char), 1, fq);
						count++;
					}
					fclose(fp);
					fclose(fq);
					break;
				}
			}
		}
		else if (strcmp(options, "exit") == 0){
			FILE *fp = fopen("hardDisk.hdd", "rb+");
			if (fp == NULL){
				printf("file not exixted\n");
				continue;
			}
			//rewind(fp);
			fwrite(&head, sizeof(head), 1, fp);
			for (int i = 0; i < max_limit;i++){
				fwrite(&head->files[i], sizeof(head->files[i]), 1, fp);
			}
			fclose(fp);
			return 0;

		}
	}

}

