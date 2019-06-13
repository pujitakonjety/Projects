#include"stdafx.h"
//#include"iostream"
//
//using namespace std;
//void matrix(int(*mat)[50], int i, int rows, int cols){
//	if (i >= rows)
//		return;
//	for (int j = i; j<cols; j++)
//		//cout<<i<<" "<<j<<" "<<endl;
//		cout << mat[i][j] << " ";
//	//cout<<endl;
//	for (int j = i + 1; j<rows; j++)
//		cout << mat[j][cols - 1] << " ";
//	for (int j = cols - 2; j >= i; j--)
//		cout << mat[rows - 1][j] << " ";
//	for (int j = rows - 2; j>i; j--)
//		cout << mat[j][i] << " ";
//	matrix(mat, i + 1, rows - 1, cols - 1);
//}
//int main(){
//	int rows, cols;
//	cin >> rows >> cols;
//	int mat[50][50];
//	for (int i = 0; i<rows; i++){
//		for (int j = 0; j<cols; j++)
//			cin >> mat[i][j];
//	}
//	int p = rows, q = cols;
//	for (int i = 0; i<rows; i++){
//		for (int j = i; j<cols; j++)
//			cout << mat[i][j] << " ";
//		for (int j = i + 1; j<rows; j++)
//			cout << mat[j][cols - 1] << " ";
//		for (int j = cols - 2; j >= i; j--)
//			cout << mat[rows - 1][j] << " ";
//		for (int j = rows - 2; j>i; j--)
//			cout << mat[j][i] << " ";
//		rows--;
//		cols--;
//	}
//	cout << endl;
//
//	matrix(mat, 0, p, q);
//}