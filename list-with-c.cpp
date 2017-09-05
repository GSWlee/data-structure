#include <stdio.h>
#include <stdlib.h>
struct node
{
	int num;
	node* next;
};
void makenew(node* l)
{
	l->next=NULL;
}
int isempty(node* l)
{
	return l->next==NULL;
}
node* find(node* l,int target)
{
	node* position;
	position=l->next;
	while(position->num==target||!isempty(position))
	{
		position=position->next;
	}
	if(position->next==NULL&&position->num!=target)
		printf("Not find.\n");
	return position;
}
node* findper(node* l,int target)
{
	node* position;
	position=l;
	while(position->next->num==target||!isempty(position->next))
	{
		position=position->next;
	}
	if(position->next->next==NULL&&position->next->num!=target)
		printf("Not find.\n");
	return position;
}
void add(node *l,int num,int pos)
{
	node* temp,*position;
	position=find(l,pos);
	if(position->next==NULL&&position->num!=pos)
	{
		printf("Cann't add.\n");
	}
	else
    {
        temp=malloc(sizeof(node));
        temp->num=num;
        temp->next=position->next;
        position->next=temp;
    }
}
void show(node * l)
{
	node*p;
	p=l->next;
	while(p->next!=NULL)
	{
		printf("%d ",p->num);
		p=p->next;
	}
	printf("\n");
}
void deleteone(node* l,int target)
{
	node* temp,*position;
	position=findper(l,target);
	if(position->next->next==NULL&&position->next->num!=target)
	{
		printf("Cann't delete.\n");
	}
	else
	{
	    temp=position->next;
        position->next=position->next->next;
        free(temp);
	}
}
void deletel(node* l)
{
	node* p,*temp;
	p=l->next;
	l->next=NULL;
	while(p->next!=NULL)
	{
		temp=p;
		p=p->next;
		free(temp);
	}
}
int main()
{
	node* header;
	makenew(header);
	int a,b;
	scanf("%d",&a);
	node* q;
	q->num=a;
	q->next=NULL;
	header->next=q;
	b=a;
	while(scanf("%d",&a)==1)
	{
		add(header,a,b);
	}
	show(header);
	int m,n;
	scanf("%d%d",&m,&n);
	add(header,m,n);
	show(header);
	deleteone(header,m);
	show(header);
	deletel(header);
	return 0;
}
