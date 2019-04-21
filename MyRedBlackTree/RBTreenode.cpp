#include "RBTreenode.h"
#include <stdlib.h>
#include <stdio.h>

RBnode * RBTreeNodeHandler::MakeRBTreeNode()
{
	RBnode* newNode = (RBnode*)malloc(sizeof(RBnode));
	newNode->right = nullptr;
	newNode->left = nullptr;
	newNode->parent = nullptr;
	newNode->color = red;

	return newNode;
}

void RBTreeNodeHandler::TSetData(RBnode* node, TData _data)
{
	node->data = _data;
}

void RBTreeNodeHandler::MakeLeftSubTree(RBnode* main, RBnode* sub)
{
	if (main->left != nullptr)
		DeleteTree(main->left);
	main->left = sub;
	if (sub != nullptr)
		sub->parent = main;
}
void RBTreeNodeHandler::MakeRightSubTree(RBnode* main, RBnode* sub)
{
	if (main->right != nullptr)
		DeleteTree(main->right);
	main->right = sub;
	if (sub != nullptr)
		sub->parent = main;
}

RBnode * RBTreeNodeHandler::ChangeLeftSubTree(RBnode* main, RBnode* sub)
{
	RBnode*  ret = main->left;

	main->left = sub;
	if (sub != nullptr)
		sub->parent = main;

	return ret;
} 
RBnode * RBTreeNodeHandler::ChangeRightSubTree(RBnode* main, RBnode* sub)
{
	RBnode* ret = main->right;

	main->right = sub;
	if(sub != nullptr)
		sub->parent = main;
	return ret;
}

void RBTreeNodeHandler::PreorderTraverse(RBnode* node, Action act)
{
	if (node == nullptr)
		return;

	act(node->data,node->color);
	PreorderTraverse(node->left, act);
	PreorderTraverse(node->right, act);
}
void RBTreeNodeHandler::InorderTraverse(RBnode* node, Action act)
{
	if (node == nullptr)
		return;

	InorderTraverse(node->left,act);
	act(node->data, node->color);
	InorderTraverse(node->right, act);
}
void RBTreeNodeHandler::PostorderTraverse(RBnode* node, Action act)
{
	if (node == nullptr)
		return;

	PostorderTraverse(node->left, act);
	PostorderTraverse(node->right, act);
	act(node->data, node->color);
}

void RBTreeNodeHandler::DeleteTree(RBnode* node)
{
	if (node == nullptr)
		return;
	DeleteTree(node->left);
	DeleteTree(node->right);
	printf("노드를 삭제하였습니다\n");
	free(node);
}