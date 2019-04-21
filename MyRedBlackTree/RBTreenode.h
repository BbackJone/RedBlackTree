#pragma once

typedef int TData;
enum COLOR {black, red};
typedef void(*Action)(TData dat, COLOR _color);

struct RBnode {
	COLOR color;
	TData data;
	RBnode* right;
	RBnode* left;
	RBnode* parent;
};

class RBTreeNodeHandler
{
public:
	static RBnode* MakeRBTreeNode();
	static void TSetData(RBnode* node, TData _data);

	static void MakeLeftSubTree(RBnode* main, RBnode* sub);
	static void MakeRightSubTree(RBnode* main, RBnode* sub);

	static RBnode* ChangeLeftSubTree(RBnode* main, RBnode* sub);
	static RBnode* ChangeRightSubTree(RBnode* main, RBnode* sub);

	static void PreorderTraverse(RBnode* node, Action act);
	static void InorderTraverse(RBnode* node, Action act);
	static void PostorderTraverse(RBnode* node, Action act);

	static void DeleteTree(RBnode* node);
};