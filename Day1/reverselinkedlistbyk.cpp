#include"stdafx.h"
//#include<iostream>
//#include<malloc.h>
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
//struct linkedlist* reverse(struct linkedlist *p){
//	struct linkedlist *t = NULL, *prev = NULL;
//	while (p != NULL){
//		t = p->next;
//		p->next = prev;
//		prev = p;
//		p = t;
//	}
//	return prev;
//}
//struct linkedlist* reverse_by_k(struct linkedlist *head, int k){
//	int count = 0;
//	struct linkedlist *ptr = head, *temp = head, *temp2 = head, *nptr, *dummy;
//	struct linkedlist *d = createnode(-1);
//	dummy = d;
//	while (ptr != NULL){
//		count++;
//		if (count%k == 0){
//			nptr = ptr->next;
//			ptr->next = NULL;
//			dummy->next = reverse(temp);
//			temp2 = temp;
//			temp = nptr;
//			temp2->next = nptr;
//			dummy = temp2;
//			ptr = nptr;
//			continue;
//		}
//		ptr = ptr->next;
//	}
//	return d->next;
//}
//int main(){
//	int size;
//	cin >> size;
//	int val;
//	cin >> val;
//	struct linkedlist *head, *ptr;
//	head = createnode(val);
//	size--;
//	ptr = head;
//	while (size--){
//		cin >> val;
//		ptr->next = createnode(val);
//		ptr = ptr->next;
//	}
//	int k;
//	cin >> k;
//	head = reverse_by_k(head, k);
//	ptr = head;
//	while (ptr != NULL){
//		cout << ptr->data << " ";
//		ptr = ptr->next;
//	}
//
//
//
//}