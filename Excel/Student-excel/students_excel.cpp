// Version2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include"stack.h"
#include"stack_int.h"
using namespace std;
struct cell{
	int data;
	char relation[100];
};
void remove_spaces(char *index){
	int ptr = 0;
	for (int ind = 0; index[ind] != '\0'; ind++){
		if (index[ind] != ' ')
			index[ptr++] = index[ind];
	}
	index[ptr] = '\0';
}
bool isEqual(char *rel, char *cols_value){
	int i;
	for (i = 0; rel[i] != ':'&&rel[i]!=' '; i++){
		if (rel[i] != cols_value[i])
			return false;
	}
	if (cols_value[i] == '\0')
		return true;
	return false;
}
int get_cell_value(char *rel){
	int val = 0;
	for (int i = 0; rel[i] != '\0'; i++){
		val = val * 10 + rel[i] - '0';
	}
	return val;

}
int get_value(char *root, char *cols_value, struct cell **mat, int mat_rows, int mat_cols){
	if (strcmp(root, "AVG") == 0 || strcmp(root, "avg") == 0){
		for (int i = 0; i < mat_cols; i++){
			int ans = 0;
			if (isEqual(mat[0][i].relation, cols_value)){
				for (int j = 1; j < mat_rows; j++)
					ans = ans + get_cell_value(mat[j][i].relation);
				return ans /( mat_rows-1);
			}
		}
	}
	else if (strcmp(root, "TOPPER") == 0 || strcmp(root, "topper") == 0){
		for (int i = 0; i < mat_cols; i++){
			int max_marks  = 0,max_row;
			if (isEqual(mat[0][i].relation, cols_value)){
				for (int j = 1; j < mat_rows; j++){
					int marks = get_cell_value(mat[j][i].relation);
					if (max_marks < marks){
						max_marks = marks;
						max_row = j;
					}
				}
				return max_row;
			}
		}
	}
	else if (strcmp(root, "DULLER") == 0 || strcmp(root, "duller") == 0){
		for (int i = 0; i < mat_cols; i++){
			int min_marks = 1000, min_row = 0;
			if (isEqual(mat[0][i].relation, cols_value)){
				for (int j = 1; j < mat_rows; j++){
					int marks = get_cell_value(mat[j][i].relation);
					if (min_marks > marks){
						min_marks = marks;
						min_row = j;
					}
				}
				return min_row;
			}
		}
	}
	else if (strcmp(root, "TOPPER_OF_ALL") == 0 || strcmp(root, "topper_of_all") == 0){
		int max_all = 0,  max_row = 0;
		for (int i = 1; i < mat_rows; i++){
			int ans = 0;
			for (int j = 2; j < mat_cols; j++)
				ans += get_cell_value(mat[i][j].relation);
			if (max_all < ans){
				max_all = ans;
				max_row = i;
			}
		}
		return max_row;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int mat_rows = 10, mat_cols = 10;
	struct cell **mat = (struct cell **)malloc(sizeof(struct cell *) * mat_rows);
	for (int i = 0; i < 10; i++){
		mat[i] = (struct cell*)malloc(sizeof(struct cell) * mat_cols);
	}
	for (int i = 0; i < mat_rows; i++){
		for (int j = 0; j < mat_cols; j++){
			mat[i][j].relation[0] = '0';
			mat[i][j].relation[1] = '\0';
		}
	}
	while (1){
		printf(">");
		char customs[100];
		gets(customs);
		if (isEqual(customs, "EXIT"))
			return 0;
		else if (isEqual(customs, "IMPORT")){
			char file_name[100];
			int ptr = 0;
			int i = 0;
			while (customs[i] != ' ')
				i++;
			i++;
			while (customs[i] != '\0')
				file_name[ptr++] = customs[i++];
			file_name[ptr] = '\0';
			if (ptr-4>=0&&file_name[ptr - 4] != '.'&&file_name[ptr - 3] != 'c'&&file_name[ptr - 2] != 's'&&file_name[ptr - 1] != 'v'){
				file_name[ptr++] = '.';
				file_name[ptr++] = 'c';
				file_name[ptr++] = 's';
				file_name[ptr++] = 'v';
				file_name[ptr] = '\0';
			}

			FILE *fp = fopen(file_name, "r");
			if (fp == NULL){
				printf("file not existed\n");
			}
			i = 0;
			char buffer[1000];
			while (fscanf(fp, "%[^\n]\n", buffer) != EOF){
				int j = 0;
				char* token = strtok(buffer, ",");
				while (token != NULL){
					strcpy(mat[i][j].relation, token);
					token = strtok(NULL, ",");
					j++;
				}
				mat_cols = j;
				i++;

			}
			fclose(fp);
			mat_rows = i;
			printf("rows = %d,cols = %d\n", mat_rows, mat_cols);
		}

		else{
			int ptr = 0;
			char root[100];
			remove_spaces(customs);
			int ind = 0;
			for (; customs[ind]!='\0'&&customs[ind] != '('; ind++)
				root[ptr++] = customs[ind];
			root[ptr] = '\0';
			char col_name[100];
			ind++;
			ptr = 0;
			while (customs[ind] != '\0'&&customs[ind] != ')')
				col_name[ptr++] = customs[ind++];
			col_name[ptr] = '\0';
			int val = get_value(root, col_name, mat, mat_rows, mat_cols);
			if (strcmp(root, "AVG") == 0 || strcmp(root, "avg") == 0)
				printf("%d\n", val);
			else
				printf("%s\n", mat[val][1].relation);
		}
	}

}
