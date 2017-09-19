#include <stdio.h>
typedef unsigned int Index;
Index hash(const char *key,int TableSize)
{
	Index Hashval = 0;
	while(*key !='\0')
		Hashval = (Hashval<<5)+*key++;

	return Hashval%TableSize;
}
struct hashtbl*
{
	int TableSize;
	list *thelists;
}
hashtbl* initializaTable(int TableSize)
{
	hashtbl* H;
	H=(hashtbl*)malloc(sizeof(hashtbl));
	H->TableSize=TableSize;
	for(int i=0;i<H->TableSize;i++)
	{
		thelists[i]=(node*)malloc(sizeof(node));
		thelists[i]->next=NULL;
	}
	return H;
}
hashtbl* find(int ele,hashtbl* H)
{
	node* p;
	node* l;
	l=H->thelists[hash(ele,H->TableSize)];
	p=list.find(ele,l);
	return p;
}
