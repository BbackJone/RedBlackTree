#pragma once
#include "RBTreenode.h"
typedef RBTreeNodeHandler Handler;

class RBTree
{
private:
	RBnode* Vroot;
	RBnode* root;
public:
	void Insert(TData _data);	//insert node that has _data
	//Utility function of Insert.
	void FixDoubleRed(RBnode* up, RBnode* down);	//up and down is red nodes that make violation to fix. up is parent, down is child.
	void Recoloring(RBnode* _node, RBnode* left, RBnode* right);
	void RotateRight(RBnode* _node);
	void RotateLeft(RBnode* _node);

	RBnode* Find(TData _data);		//find node that has _data and return the node.
	bool Delete(TData _data);		//delete node that has _data
	//Utility function of delete
	void DecreaseBH(RBnode* _node);
	void DecreaseBH_DoubleRedCheck(TData delNodedata);
	COLOR GetColor(RBnode* _node);

	RBnode* GetRoot() { return root; }

	void ShowTree();	//Show state of tree on console screen.
	//Utiliy function of Showtree. 
	void ShowTree(RBnode* pNode, int width, int height, int maxheight);
	int GetHeight(RBnode* _node);
public:
	RBTree();
	~RBTree();
};

