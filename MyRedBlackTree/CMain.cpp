#include <stdio.h>
#include "RBTreenode.h"
#include "RBTree.h"
#include <Windows.h>

typedef RBTreeNodeHandler Handle;

void Shownode(TData data, COLOR color)
{
	printf("°ª : %d,", data);
	if (color == black)
		printf("»ö±ò : black\n");
	else
		printf("»ö±ò : red\n");
}

int main()
{
	RBTree test;

	int Insertorder[10] = {5,6,4,7,3,8,2,9,1,10 };
	for (int i = 0; i <10; i++)
	{
		test.Insert(Insertorder[i]);
		system("cls");
		test.ShowTree();
	}

	test.ShowTree();

	int Delorder[10] = { 4,6,5,1,3,2,10,7,8,9 };
	for (int i = 0; i < 10; i++)
	{
		test.Delete(Delorder[i]);
		system("cls");
		test.ShowTree();
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	return 0;
}