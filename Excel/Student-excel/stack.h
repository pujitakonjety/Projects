#include<stdlib.h>
struct stack{
	int top;
	int max_size;
	char* ele;
};
struct stack* createstack(int size){
	struct stack *st = (struct stack*)malloc(sizeof(struct stack));
	st->max_size = size;
	st->top = -1;
	st->ele = (char *)malloc(size*sizeof(char));
	return st;


}
void push(char ch, struct stack *st){
	st->top++;
	st->ele[st->top] = ch;
}
char pop(struct stack *st){
	char ch = st->ele[st->top];
	st->top--;
	return ch;
}
