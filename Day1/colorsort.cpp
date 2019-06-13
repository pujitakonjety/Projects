// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
void merge(int *array, int lo, int mid, int hi){
	int i = lo, j = mid + 1, ind = 0;
	int temp[100];
	while (i <= mid&&j <= hi){
		if (array[i] < array[j])
			temp[ind++] = array[i++];
		else
			temp[ind++] = array[j++];
	}
	while (i <= mid)
		temp[ind++] = array[i++];
	while (j <= hi)
		temp[ind++] = array[j++];
	int p;
	for (p = 0; p < ind; p++, lo++){
		array[lo] = temp[p];
		//cout<<array[lo]<<" ";
	}
}
void sort(int *array, int lo, int hi){
	if (lo >= hi)
		return;
	int mid = (lo + hi) / 2;
	//	cout<<mid<<endl;
	sort(array, lo, mid);
	sort(array, mid + 1, hi);
	merge(array, lo, mid, hi);

}
int main()
{
	int size, sum = 0;
	cin >> size;
	int *array = (int*)malloc(size*sizeof(int));
	for (int idx = 0; idx < size; idx++)
		cin >> array[idx];
	sort(array, 0, size - 1);
	for (int idx = 0; idx < size; idx++)
		cout << array[idx] << " ";
	cout << endl;


}

