//// ConsoleApplication2.cpp : Defines the entry point for the console application.
////
//
#include "stdafx.h"
//#include<iostream>
//using namespace std;
//void merge(int *array, int lo, int mid, int hi){
//	int i = lo, j = mid + 1, ind = 0;
//	int temp[100];
//	while (i <= mid&&j <= hi){
//		if (array[i] < array[j])
//			temp[ind++] = array[i++];
//		else
//			temp[ind++] = array[j++];
//	}
//	while (i <= mid)
//		temp[ind++] = array[i++];
//	while (j <= hi)
//		temp[ind++] = array[j++];
//	int p;
//	for (p = 0; p < ind; p++, lo++)
//		array[lo] = temp[p];
//}
//void sort(int *array, int lo, int hi){
//	if (lo > hi)
//		return;
//	int mid = (lo + hi) / 2;
//	sort(array, lo, mid);
//	sort(array, mid + 1, hi);
//	merge(array, lo, mid, hi);
//
//}
//int _tmain(int argc, _TCHAR* argv[])
//{
//	int size, sum = 0;
//	cin >> size;
//	int *array = (int*)malloc(size*sizeof(int));
//	for (int idx = 0; idx < size; idx++)
//		cin >> array[idx];
//	int ptr1 = 0, ptr2 = size - 1;
//	while (ptr1 < ptr2){
//		if (array[ptr1] == 1){
//			while (ptr2 > ptr1&&array[ptr2] != 0)
//				ptr2--;
//			//array[ptr1] = array[ptr1] + array[ptr2] - (array[ptr2] = array[ptr1]);
//			int temp = array[ptr1];
//			array[ptr1] = array[ptr2];
//			array[ptr2] = temp;
//			ptr2--;
//		}
//		ptr1++;
//
//
//	}
//	for (int idx = 0; idx < size; idx++)
//		cout << array[idx] << " ";
//	cout << endl;
//
//
//}
//
