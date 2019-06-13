// Version2.cpp : Defines the entry point for the console application.
//

//excel with only 2 operands and eacn operand can again have another 2 operands .......

#include "stdafx.h"
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

struct cell{
	int data;
	char relation[100];
};
bool is_digit(char s){
	int n = s - '0';
	if (n <= 9 && n >= 0)
		return true;
	return false;
}
bool is_char(char s){
	if (s >= 'A'&&s <= 'Z')
		return true;
	return false;
}
bool is_operator(char s){
	if (s == '+' || s == '-' || s == '*' || s == '/')
		return true;
	return false;
}
void remove_spaces(char *index){
	int ptr = 0;
	for (int ind = 0; index[ind] != '\0'; ind++){
		if (index[ind] != ' ')
			index[ptr++] = index[ind];
	}
	index[ptr] = '\0';
}
void store_cell_value(struct cell **mat, char *index, int row, int col){
	int k = 0;
	for (int ind = 3; index[ind] != '\0'; ind++){
		cout << index[ind] << endl;
		mat[row][col].relation[k++] = index[ind];
	}
	mat[row][col].relation[k] = '\0';
}
/*int* find_operands(struct cell **mat, int row, int col){
int *operands = (int *)malloc(5 * sizeof(int));
for (int i = 0; i < 5; i++)
operands[i] = -1;
int ptr = 0;
char op = '0';
for (int ind = 0; mat[row][col].relation[ind] != '\0'; ind++){
if (is_char(mat[row][col].relation[ind]) && is_digit(mat[row][col].relation[ind + 1])){
operands[ptr++] = mat[row][col].relation[ind] - 'A';
operands[ptr++] = mat[row][col].relation[ind+1] - '1';
}
if (is_operator(mat[row][col].relation[ind])){
op = mat[row][col].relation[ind];
}


}
operands[ptr] = (int)op;
return operands;
}*/
int* find_operands(struct cell **mat, int row, int col){
	int *operands = (int *)malloc(6 * sizeof(int));
	for (int i = 0; i < 6; i++)
		operands[i] = -1;
	int ptr = 0;
	char op = '0';
	for (int ind = 0; mat[row][col].relation[ind] != '\0'; ind++){
		if (is_char(mat[row][col].relation[ind]) && is_digit(mat[row][col].relation[ind + 1])){
			operands[ptr++] = mat[row][col].relation[ind] - 'A';
			operands[ptr++] = mat[row][col].relation[ind + 1] - '1';
		}
		if (is_operator(mat[row][col].relation[ind])){
			if (operands[1] == -1)
				operands[5] = 1;
			op = mat[row][col].relation[ind];
		}


	}
	operands[4] = op;
	return operands;
}
int isCellDigits(struct cell **mat, int row, int col){
	int val = 0;
	for (int ind = 0; mat[row][col].relation[ind] != '\0'; ind++){
		if (!is_digit(mat[row][col].relation[ind]))
			return -1;
		val = val * 10 + mat[row][col].relation[ind] - '0';
	}
	return val;
}
int find_value(struct cell **mat, int row, int col){
	int val = 0;
	if (is_char(mat[row][col].relation[0])){
		for (int ind = 3; mat[row][col].relation[ind] != '\0'; ind++)
			val = val * 10 + mat[row][col].relation[ind] - '0';
	}
	else{
		for (int ind = 0; mat[row][col].relation[ind] != '\0'; ind++){
			if (is_operator(mat[row][col].relation[ind]))
				break;
			val = val * 10 + mat[row][col].relation[ind] - '0';
		}

	}
	return val;

}
/*int get_cell_value(struct cell **mat, int row, int col){
cout << row << col << " in func" << endl;
int cell_value = isCellDigits(mat, row, col);
//cout << cell_value << " ((" << endl;
if (cell_value != -1)
return cell_value;
//int operands[5];
int *operands = find_operands(mat, row, col);
char op = operands[4];
if (operands[3] == -1 && operands[4] == -1)
return find_value(mat, row, col) + get_cell_value(mat, operands[0], operands[1]);
else
return get_cell_value(mat, operands[0], operands[1]) + get_cell_value(mat, operands[2], operands[3]);


}*/
int get_cell_value(struct cell **mat, int row, int col){
	cout << row << col << " in func" << endl;
	int cell_value = isCellDigits(mat, row, col);
	//cout << cell_value << " ((" << endl;
	if (cell_value != -1)
		return cell_value;
	//int operands[5];
	int *operands = find_operands(mat, row, col);
	char op = operands[4];
	if (op == '+'){
		if (operands[3] == -1 && operands[2] == -1)
			return find_value(mat, row, col) + get_cell_value(mat, operands[0], operands[1]);
		else
			return get_cell_value(mat, operands[0], operands[1]) + get_cell_value(mat, operands[2], operands[3]);

	}
	else if (op == '*'){
		if (operands[2] == -1 && operands[3] == -1)
			return find_value(mat, row, col) * get_cell_value(mat, operands[0], operands[1]);
		else
			return get_cell_value(mat, operands[0], operands[1]) * get_cell_value(mat, operands[2], operands[3]);
	}
	else if (op == '/' && operands[5] == 1){
		if (operands[2] == -1 && operands[3] == -1)
			return find_value(mat, row, col) / get_cell_value(mat, operands[0], operands[1]);
		else
			return get_cell_value(mat, operands[0], operands[1]) / get_cell_value(mat, operands[2], operands[3]);
	}
	else if (op == '/'&&operands[5] == -1){
		if (operands[2] == -1 && operands[3] == -1)
			return  get_cell_value(mat, operands[0], operands[1]) / find_value(mat, row, col);
		else
			return get_cell_value(mat, operands[0], operands[1]) / get_cell_value(mat, operands[2], operands[3]);
	}
	else if (op == '-'&&operands[5] == 1){
		if (operands[2] == -1 && operands[3] == -1)
			return find_value(mat, row, col) - get_cell_value(mat, operands[0], operands[1]);
		else
			return get_cell_value(mat, operands[0], operands[1]) - get_cell_value(mat, operands[2], operands[3]);
	}
	else{
		if (operands[2] == -1 && operands[3] == -1)
			return  get_cell_value(mat, operands[0], operands[1]) - find_value(mat, row, col);
		else
			return get_cell_value(mat, operands[0], operands[1]) - get_cell_value(mat, operands[2], operands[3]);
	}



}


int _tmain(int argc, _TCHAR* argv[])
{
	struct cell **mat = (struct cell **)malloc(sizeof(struct cell *) * 10);
	for (int i = 0; i < 10; i++){
		mat[i] = (struct cell*)malloc(sizeof(struct cell) * 10);
	}
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			mat[i][j].relation[0] = '0';
			mat[i][j].relation[1] = '\0';
		}
	}
	while (1){
		printf(">");
		char options[100];
		scanf("%s", options);
		if (strcmp(options, "SET") == 0){
			char index[100];
			gets(index);
			remove_spaces(index);
			//cout << index;
			int col = index[1] - '1';
			int row = index[0] - 'A';
			cout << row << col << endl;
			store_cell_value(mat, index, row, col);

		}
		else if (strcmp(options, "GET") == 0){
			char index[10];
			gets(index);
			remove_spaces(index);
			int col = index[1] - '1';
			int row = index[0] - 'A';
			cout << row << col << "***" << endl;

			printf("%d", get_cell_value(mat, row, col));
		}
		else if (strcmp(options, "PRINT") == 0){
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					printf("%s ", mat[i][j].relation);
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


					fprintf(fp, "%s", mat[i][j].relation);
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
				int j = 0, ptr = 0;
				for (int ind = 0; buffer[ind] != '\0'; ind++){
					if (buffer[ind] == ','){
						j++;
						mat[i][j].relation[ptr] = '\0';
						ptr = 0;
						continue;

					}
					mat[i][j].relation[ptr++] = buffer[ind];
				}
			}
			fclose(fp);
		}
		printf("\n");

	}


	return 0;

}


