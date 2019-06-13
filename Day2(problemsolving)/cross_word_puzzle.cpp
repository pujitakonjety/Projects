#include"stdafx.h"
//#include<iostream>
//#include<string.h>
//using namespace std;
//bool find(char(*str)[100], int i, int j, char * s, int ind, int rows, int cols, int x, int y){
//	if (ind >= s.length())
//		return true;
//
//	if (i >= rows || j >= cols || i<0 || j<0 || str[i][j] != s[ind])
//		return false;
//	return true && find(str, i + x, j + y, s, ind + 1, rows, cols, x, y);
//
//}
//
//int main(){
//	int x[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
//	int y[8] = { 1, -1, 1, 0, -1, 1, 0, -1 };
//	int rows, cols;
//	cin >> rows >> cols;
//	char str[100][100];
//	fflush(stdin);
//	for (int i = 0; i < rows; i++){
//		for (int j = 0; j<cols; j++)
//			cin >> str[i][j];
//		//fflush(stdin);
//	}
//	char s[100];
//	scanf("%s", s);
//	for (int i = 0; i < rows; i++){
//		for (int j = 0; j < cols; j++){
//			if (str[i][j] == s[0]){
//				for (int ind = 0; ind<8; ind++){
//					if (find(str, i, j, s, 0, rows, cols, x[ind], y[ind]))
//						cout << i << " " << j << " " << i + (strlen(s) - 1)*x[ind] << " " << j + (strlen(s) - 1)*y[ind] << endl;
//				}
//			}
//		}
//	}
//
//
//}
//using namespace std;
//bool find(char(*str)[100], int i, int j, string s, int ind, int rows, int cols, int x, int y){
//	if (ind >= s.length())
//		return true;
//
//	if (i >= rows || j >= cols || i<0 || j<0 || str[i][j] != s[ind])
//		return false;
//	return true && find(str, i + x, j + y, s, ind + 1, rows, cols, x, y);
//
//}
//
//int main(){
//	int x[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
//	int y[8] = { 1, -1, 1, 0, -1, 1, 0, -1 };
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
//	string s;
//	gets(s);
//	for (int i = 0; i < rows; i++){
//		for (int j = 0; j < cols; j++){
//			if (str[i][j] == s[0]){
//				for (int ind = 0; ind<8; ind++){
//					if (find(str, i, j, s, 0, rows, cols, x[ind], y[ind]))
//						cout << i << " " << j << " " << i + (s.length() - 1)*x[ind] << " " << j + (s.length() - 1)*y[ind] << endl;
//				}
//			}
//		}
//	}
//
//
//}