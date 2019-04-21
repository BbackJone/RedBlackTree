#pragma once

typedef int LData;

typedef struct _node
{
	LData data;
	_node* next;
}Node;

typedef struct _linkedlist
{
	Node* head;
	Node* cur;
	Node* before;
	int numOfData;
	int(*comp)(LData d1, LData d2);
}LinkedList;

typedef LinkedList List;

void InitList(List* list);
void LInsert(List* list, LData data);
void SInsert(List* list, LData data);
void FInsert(List* list, LData data);

int LFirst(List* list, LData* data);
int LNext(List* list, LData* data);

LData LRemove(List* list);
int LCount(List* list);

void LSetSortRule(List* list, int(*comp)(LData d1, LData d2));