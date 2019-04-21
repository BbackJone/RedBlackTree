#include "LinkedList.h"
#include <stdlib.h>

void InitList(List * list)
{
	list->head = (Node*)malloc(sizeof(Node));
	list->head->next = NULL;

	list->cur = NULL;
	list->before = NULL;

	list->numOfData = 0;
	list->comp = NULL;
}

void LInsert(List * list, LData data)
{
	list->numOfData++;

	if (list->comp == NULL)
		FInsert(list, data);
	else
		SInsert(list, data);
}

void SInsert(List * list, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	Node* pred = list->head;
	while (pred->next != NULL &&
		list->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;
}

void FInsert(List * list, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = list->head->next;
	list->head->next = newNode;
}

int LFirst(List * list, LData * data)
{
	if (list->head->next == NULL)
		return 0;

	list->cur = list->head->next;
	list->before = list->head;

	*data = list->cur->data;
	return 1;
}

int LNext(List * list, LData * data)
{
	if (list->cur->next == NULL)
		return 0;

	list->before = list->cur;
	list->cur = list->cur->next;

	*data = list->cur->data;
	return 1;
}

LData LRemove(List * list)
{
	Node* delNode = list->cur;
	LData ret = list->cur->data;

	list->before->next = list->cur->next;
	list->cur = list->before;

	free(delNode);
	list->numOfData--;
	return ret;
}

int LCount(List * list)
{
	return list->numOfData;
}

void LSetSortRule(List * list, int(*comp)(LData d1, LData d2))
{
	list->comp = comp;
}
