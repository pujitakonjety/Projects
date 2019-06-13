// Version2.cpp : Defines the entry point for the console application.
//

//excel with operations of many arguments 
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
int isCellDigits(struct cell **mat, int row, int col){
	int val = 0;
	for (int ind = 0; mat[row][col].relation[ind] != '\0'; ind++){
		if (!is_digit(mat[row][col].relation[ind]))
			return -1;
		val = val * 10 + mat[row][col].relation[ind] - '0';
	}
	return val;
}
void Update(struct stack *st, char *str, int *ptr){
	while (st->ele[st->top] != '('){
		str[*ptr] = st->ele[st->top];
		*ptr = *ptr + 1;
		str[*ptr] = ' ';
		*ptr = *ptr + 1;
		pop(st);
	}
	pop(st);

}
int calc(int val1, int val2, char ch){
	if (ch == '*')
		return val1*val2;
	if (ch == '+')
		return val1 + val2;
	if (ch == '-')
		return val1 - val2;
	if (ch == '/')
		return val1 / val2;
	return 0;
}

int infixTopostfix(struct stack* st, char *str, int size){
	while (st->top != -1){
		str[size++] = st->ele[st->top];
		pop(st);
	}
	str[size] = '\0';
	int val = 0;
	struct stack_int *postfix = createstack_int(30);
	for (int i = 0; i < size; i++){
		if (str[i] == '\0')
			break;
		if (str[i] == ' ')
			continue;
		if (is_operator(str[i])){
			int val2 = postfix->ele[postfix->top];
			pop_int(postfix);
			int val1 = postfix->ele[postfix->top];
			pop_int(postfix);
			push_int(calc(val1, val2, str[i]), postfix);
			continue;
		}
		while (is_digit(str[i])){
			val = val * 10 + str[i] - '0';
			i++;
		}
		push_int(val, postfix);
		i--;
		val = 0;
	}
	for (int i = 0; i < size; i++)
		cout << str[i];
	cout << endl;

	return postfix->ele[0];
	//return 56;

}
int priority(char s){
	if (s == '*' || s == '/')
		return 5;
	if (s == '+' || s == '-')
		return 2;
	return 12;
}
void insert(struct stack *st, char s, char *str, int *ind){

	if (st->top == -1 || st->ele[st->top] == '(' || priority(st->ele[st->top]) <= priority(s)){
		push(s, st);
		return;
	}
	while (priority(st->ele[st->top]) > priority(s)){
		str[*ind] = st->ele[st->top];
		*ind = *ind + 1;
		str[*ind] = ' ';
		*ind = *ind + 1;
		pop(st);
	}



}
int reverse(int n){
	int ans = 0, count = 0;
	while (n>0 && n % 10 == 0){
		count++;
		n = n / 10;
	}
	while (n > 0){

		ans = ans * 10 + n % 10;
		n = n / 10;
	}
	cout << ans*pow(10, count) << "hihi" << endl;
	return ans*pow(10, count);
}
int Eval(struct cell **mat, int row, int col){
	int val = isCellDigits(mat, row, col);
	if (val != -1)
		return val;
	char str[100];
	int ptr = 0;

	struct stack *st = createstack(50);
	for (int idx = 0; mat[row][col].relation[idx] != '\0'; idx++){
		if (is_operator(mat[row][col].relation[idx]) || mat[row][col].relation[idx] == '(')
			insert(st, mat[row][col].relation[idx], str, &ptr);
		else if (mat[row][col].relation[idx] == ')')
			Update(st, str, &ptr);
		else if (is_char(mat[row][col].relation[idx]) && is_digit(mat[row][col].relation[idx + 1])){
			int val1 = mat[row][col].relation[idx] - 'A';
			int val2 = mat[row][col].relation[idx + 1] - '1';
			idx++;
			int ans = reverse(Eval(mat, val1, val2));
			if (ans == 0)
				str[ptr++] = '0';
			while (ans != 0){
				str[ptr++] = ans % 10 + '0';
				ans = ans / 10;
			}
			str[ptr++] = ' ';

		}

		else{
			int t = 0;
			while (is_digit(mat[row][col].relation[idx])){
				str[ptr++] = mat[row][col].relation[idx];
				idx++;
			}
			idx--;
			str[ptr++] = ' ';

		}




	}
	str[ptr] = '\0';
	return infixTopostfix(st, str, ptr);
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

			//printf("%d", get_cell_value(mat, row, col));
			cout << Eval(mat, row, col) << endl;
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


