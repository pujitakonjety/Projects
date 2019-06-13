#include"stdafx.h"
//#include<iostream>
//#include<stdlib.h>
//#include<map>
//using namespace std;
//
//struct linkedlist{
//	int data;
//	struct linkedlist *next;
//	struct linkedlist *randptr;
//};
//
//struct linkedlist* createnode(int val){
//	struct linkedlist *newnode = (struct linkedlist*)malloc(sizeof(struct linkedlist));
//	newnode->data = val;
//	newnode->next = NULL;
//	return newnode;
//}
//struct linkedlist* create_clone(struct linkedlist *head){
//	map<linkedlist*, linkedlist*>mp;
//	map<linkedlist*, linkedlist*>::iterator it;
//	struct linkedlist *ptr = head, *head2, *ptr2;
//	head2 = createnode(head->data);
//	ptr2 = head2;
//	ptr = head->next;
//	while (ptr != NULL){
//		ptr2->next = createnode(ptr->data);
//		ptr2 = ptr2->next;
//		ptr = ptr->next;
//	}
//	ptr2 = head2;
//	ptr = head;
//	while (ptr != NULL){
//		mp.insert(pair<struct linkedlist*, struct linkedlist*>(ptr, ptr2));
//		ptr = ptr->next;
//		ptr2 = ptr2->next;
//	}
//	ptr = head;
//	ptr2 = head2;
//	while (ptr != NULL){
//		it = mp.find(ptr->randptr);
//		ptr2->randptr = it->second;
//		ptr = ptr->next;
//		ptr2 = ptr2->next;
//	}
//	return head2;
//}
//
//
//int main(){
//	struct linkedlist *node1 = createnode(1);
//	struct linkedlist *node2 = createnode(2);
//	struct linkedlist *node3 = createnode(3);
//	struct linkedlist *node4 = createnode(4);
//	struct linkedlist *node5 = createnode(5);
//	struct linkedlist *node6 = createnode(6);
//	node1->next = node2;
//	node1->randptr = node3;
//	node2->next = node3;
//	node2->randptr = node5;
//	node3->next = node4;
//	node3->randptr = node1;
//	node4->next = node5;
//	node4->randptr = node6;
//	node5->next = node6;
//	node5->randptr = node2;
//	node6->next = NULL;
//	node6->randptr = node4;
//	node1 = create_clone(node1);
//	struct linkedlist *ptr = node1;
//	while (ptr != NULL){
//		cout << ptr->data << " ";
//		cout << ptr->randptr->data << " ";
//		ptr = ptr->next;
//
//	}
//}
