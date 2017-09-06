#include <stdio.h>
#include <stdlib.h>
struct node
{
	char c;
	node* next;
};
int isempty(node* s)
{
	return s->next==NULL;
}
void push(node* s,char ch)
{
	node* temp;
	temp=(node*)malloc(sizeof(node));
	temp->c=ch;
	temp->next=s->next;
	s->next=temp;
}
char top(node* s)
{
	return s->next->c;
}
void pop(node* s)
{
	node* temp;
	temp=s->next;
	printf("%c ",temp->c);
	s->next=s->next->next;
	free(temp);
}
int main()
{
	char q;
	node* stack;
	stack=(node*)malloc(sizeof(node));
	stack->next=NULL;
	for(int i=0;i<3;i++)
	{
		scanf("%c",&q);
		push(stack,q);
		printf("%d\n",i);
	}
    char r;
	r=top(stack);
	printf("%c ",r);
	while(!isempty(stack))
	{
		pop(stack);
	}
	return 0;
}
