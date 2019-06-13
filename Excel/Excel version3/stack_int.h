#include<stdlib.h>
struct stack_int{
	int top;
	int max_size;
	int* ele;
};
struct stack_int* createstack_int(int size){
	struct stack_int *sta = (struct stack_int*)malloc(sizeof(struct stack_int));
	sta->max_size = size;
	sta->top = -1;
	sta->ele = (int *)malloc(size*sizeof(int));
	return sta;


}
void push_int(int ch, struct stack_int *sta){
	sta->top++;
	sta->ele[sta->top] = ch;
}
int pop_int(struct stack_int *sta){
	int  ch = sta->ele[sta->top];
	sta->top--;
	return ch;
}
