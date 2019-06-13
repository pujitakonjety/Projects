// Day3 - excel.cpp : Defines the entry point for the console application.
//
//basic excel version with 5 commands
#include "stdafx.h"
#include<iostream>
#include<string.h>
using namespace std;
int find_number(char *index){
	int idx = 0;
	while (index[idx] != '=')
		idx++;
	int val = 0;
	idx++;
	for (; index[idx] != '\0'; idx++){
		if (index[idx] == ' ')
			continue;
		val = val * 10 + index[idx] - '0';
	}
	return val;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	int mat[10][10];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++)
			mat[i][j] = 0;
	}

	while (1){
		printf(">");
		char options[100];
		scanf("%s", options);
		if (strcmp(options, "SET") == 0){
			char index[100];
			gets(index);
			int val = find_number(index);
			int ind = 0;
			while (index[ind] == ' ')
				ind++;

			int row = index[ind+1] - '1';
			int col = index[ind] - 'A';
			//printf("%d,%d\n", row, col);
			mat[row][col] = val;
			

		}
		else if (strcmp(options, "GET") == 0){
			char index[10];
			scanf("%s", index);
			int row = index[1] - '1';
			int col = index[0] - 'A';
			//printf("%d,%d\n", row, col);
			//printf("%d", mat[row][col]);
		}
		else if (strcmp(options, "PRINT") == 0){
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					printf("%d ", mat[i][j]);
				}
				printf("\n");
			}
		}
		else if (strcmp(options, "EXPORT") == 0){
			char  file_name[100];
			scanf("%s", file_name);
			FILE *fp = fopen(file_name, "w");
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){


					fprintf(fp, "%d", mat[i][j]);
					fputc(',', fp);
				}
				fputc('\n', fp);
			}
			fclose(fp);
		}
		else if (strcmp(options, "EXIT") == 0)
			return 0;
		else if (strcmp(options, "IMPORT") == 0){
			char  file_name[100];
			scanf("%s", file_name);
			FILE *fp = fopen(file_name, "r");
			char s;
			for (int i = 0; i < 10; i++){
				char buffer[100];

				fscanf(fp, "%s", buffer);
				int j = 0, val = 0;
				for (int ind = 0; buffer[ind] != '\0'; ind++){
					if (buffer[ind] == ','){
						j++;
						mat[i][j] = 0;
						val = 0;
						continue;

					}
					val = val * 10 + buffer[ind] - '0';
				}
			}
			fclose(fp);
		}
		printf("\n");
		}
		
		return 0;
	}
