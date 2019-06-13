// ConsoleApplication3.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
//#include<iostream>
//using namespace std;
//void find_count(char(*str)[100], char *s, int i, int j, int rows, int cols, int len){
//
//	int x[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
//	int y[8] = { 1, -1, 1, 0, -1, 1, 0, -1 };
//	int row = i, col = j;
//	for (int k = 0; k < 8; k++){
//		i = row;
//		j = col;
//		int ind;
//		for (ind = 0; ind < len; ind++){
//			if (i<0 || j<0 || i >= rows || j >= cols || s[ind] != str[i][j])
//				break;
//			i = i + x[k];
//			j = j + y[k];
//		}
//		if (ind >= len)
//			cout << row << " " << col << " " << i - x[k] << " " << j - y[k] << endl;
//
//	}
//
//
//}
//
//int main(){
//	int rows, cols;
//	cin >> rows >> cols;
//	char str[100][100];
//	fflush(stdin);
//	for (int i = 0; i < rows; i++){
//		for (int j = 0; j<cols; j++)
//			cin >> str[i][j];
//		//fflush(stdin);
//	}
//	fflush(stdin);
//	int len;
//	cin >> len;
//	char s[100];
//	for (int i = 0; i < len; i++)
//		cin >> s[i];
//
//
//	for (int i = 0; i < rows; i++){
//		for (int j = 0; j < cols; j++){
//			if (str[i][j] == s[0])
//				find_count(str, s, i, j, rows, cols, len);
//		}
//	}
//	return 0;
//}
//
