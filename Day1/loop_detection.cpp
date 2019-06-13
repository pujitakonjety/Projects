//// ConsoleApplication2.cpp : Defines the entry point for the console application.
////
//
#include "stdafx.h"
//#include<iostream>
//using namespace std;
//struct linkedlist{
//	int data;
//	struct linkedlist *next;
//};
//struct linkedlist* createnode(int val){
//	struct linkedlist *newnode = (struct linkedlist*)malloc(sizeof(struct linkedlist));
//	newnode->data = val;
//	newnode->next = NULL;
//	return newnode;
//}
//void detect_loop(struct linkedlist *head){
//	struct linkedlist *sptr, *fptr;
//	sptr = head;
//	fptr = head;
//	do{
//		sptr = sptr->next;
//		fptr = fptr->next->next;
//	} while (fptr != NULL && fptr->next != NULL&&sptr != fptr);
//	if (sptr == fptr)
//		cout << "loop detected" << endl;
//	else
//		return;
//
//	sptr = head;
//	while (sptr != fptr){
//		sptr = sptr->next;
//		fptr = fptr->next;
//	}
//	cout << fptr->data;
//
//}
//int _tmain(int argc, _TCHAR* argv[])
//{
//
//	int size, count;
//	cin >> size >> count;
//	int val;
//	cin >> val;
//	struct linkedlist *head, *ptr, *loop = NULL;
//	head = createnode(val);
//	size--;
//	count--;
//	if (count == 0)
//		loop = head;
//	ptr = head;
//	while (size--){
//		cin >> val;
//		ptr->next = createnode(val);
//		count--;
//		if (count == 0)
//			loop = ptr->next;
//		ptr = ptr->next;
//	}
//	ptr->next = loop;
//	detect_loop(head);
//}
//
