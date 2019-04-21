#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include "RBTree.h"
#include "LinkedList.h"

void RBTree::Insert(TData _data)
{
	//Make New node
	RBnode* newNode = Handler::MakeRBTreeNode();
	Handler::TSetData(newNode, _data);

	//Find location to insert node
	RBnode* cur = root;

	if (cur == nullptr)	//root is empty
	{
		newNode->color = black;
		root = newNode;
		Vroot->right = root;
		root->parent = Vroot;
	}
	else
	{
		while (cur != nullptr)
		{
			if (cur->data < newNode->data)
			{
				if (cur->right == nullptr)
				{
					Handler::MakeRightSubTree(cur, newNode);
					break;
				}
				else
					cur = cur->right;
			}
			else
			{
				if (cur->left == nullptr)
				{
					Handler::MakeLeftSubTree(cur, newNode);
					break;
				}
				else
					cur = cur->left;
			}
		}

		//Check double-red
		if (root != cur)
		{
			if (cur->color == red)
				FixDoubleRed(cur, newNode);
		}
	}
}

void RBTree::FixDoubleRed(RBnode * up, RBnode * down)
{
	RBnode* p = up->parent;
	RBnode* gp = p->parent;
	RBnode* uncle = nullptr;
	COLOR uncleColor = black;

	if (p->right == up)	//right direction
	{
		uncle = p->left;
		if (uncle == nullptr)
			uncleColor = black;
		else
			uncleColor = uncle->color;

		//uncle == red
		if (uncleColor == red)
			Recoloring(p, uncle, up);
		else
		{
			//uncle == black(triangle)
			if (up->left == down)
			{
				//Make this state be a "uncle == black(line)"
				Handler::ChangeLeftSubTree(up, down->right);
				Handler::ChangeRightSubTree(p, down);
				Handler::ChangeRightSubTree(down, up);

				RBnode* temp = down;
				down = up;
				up = temp;
			}

			//uncle == black(line)
			RotateLeft(p);
		}
	}
	else		//left direction
	{
		uncle = p->right;
		if (uncle == nullptr)
			uncleColor = black;
		else
			uncleColor = uncle->color;

		//uncle == red
		if (uncleColor == red)
			Recoloring(p, uncle, up);
		else
		{
			//uncle == black(triangle)
			if (up->right == down)
			{
				//Make this state be a "uncle == black(line)"
				Handler::ChangeRightSubTree(up, down->left);
				Handler::ChangeLeftSubTree(p, down);
				Handler::ChangeLeftSubTree(down, up);

				RBnode* temp = down;
				down = up;
				up = temp;
			}

			//uncle == black(line)
			RotateRight(p);
		}
	}
}

void RBTree::Recoloring(RBnode * _node, RBnode * left, RBnode * right)
{
	if (root != _node)
		_node->color = red;
	_node->left->color = black;
	_node->right->color = black;

	//Double-red recheck.
	if (_node->parent->color == red)
		FixDoubleRed(_node->parent, _node);
}

void RBTree::RotateRight(RBnode * _node)
{
	RBnode* Z = _node->left->left;
	RBnode* A = _node->left;
	RBnode* B = _node;
	RBnode* C = _node->right;
	RBnode* temp = _node->left->right;
	RBnode* superNode = _node->parent;

	Handler::ChangeRightSubTree(A, B);
	Handler::ChangeLeftSubTree(B, temp);

	B->color = red;
	A->color = black;

	if (superNode->right == B)
		Handler::ChangeRightSubTree(superNode, A);
	else
		Handler::ChangeLeftSubTree(superNode, A);

	if (Vroot->right != root)
		root = Vroot->right;

	//Double-red check
	if (B->left != nullptr)
	{
		if (B->left->color == red)
			FixDoubleRed(B, B->left);
	}
}

void RBTree::RotateLeft(RBnode * _node)
{
	RBnode* Z = _node->right->right;
	RBnode* A = _node->right;
	RBnode* B = _node;
	RBnode* C = _node->left;
	RBnode* temp = _node->right->left;
	RBnode* superNode = _node->parent;

	Handler::ChangeLeftSubTree(A, B);
	Handler::ChangeRightSubTree(B, temp);

	B->color = red;
	A->color = black;

	if (superNode->right == B)
		Handler::ChangeRightSubTree(superNode, A);
	else
		Handler::ChangeLeftSubTree(superNode, A);

	if (Vroot->right != root)
		root = Vroot->right;

	//Double-red check
	if (B->right != nullptr)
	{
		if (B->right->color == red)
			FixDoubleRed(B, B->right);
	}
}

RBnode * RBTree::Find(TData _data)
{
	RBnode* cur = root;

	while (cur != nullptr)
	{
		if (cur->data < _data)
			cur = cur->right;
		else if (cur->data > _data)
			cur = cur->left;
		else
			return cur;
	}

	printf("Failed to find!\n");
	return nullptr;
}

bool RBTree::Delete(TData _data)
{
#pragma region findDelnode
	RBnode* cur = root;
	RBnode* delNode = nullptr;		//node that has _data

	while (cur->data != _data)
	{
		if (cur->data < _data)
		{
			if (cur->right != nullptr)
				cur = cur->right;
			else
			{
				printf("Failed to find!\n");
				cur = nullptr;
				return false;
			}
		}
		else
		{
			if (cur->left != nullptr)
				cur = cur->left;
			else
			{
				printf("Failed to find!\n");
				return false;
			}
		}
	}

	if (cur == nullptr)
		return false;

	delNode = cur;
#pragma endregion
#pragma region findTerminalnode
	RBnode* terminalNode = delNode;		//node to remove actually.
	//case 1. delNode has right sub tree
	if (delNode->right != nullptr)
	{
		while (terminalNode->right != nullptr)
		{
			//find node that has smallest data in the right sub tree.
			cur = cur->right;
			while (cur->left != nullptr)
			{
				cur = cur->left;
			}
			terminalNode->data = cur->data;
			terminalNode = cur;
		}
	}
	//case 2. delNode has left sub tree
	else if (delNode->left != nullptr)
	{
		while (terminalNode->left != nullptr)
		{
			//find node that has smallest data in the left sub tree.
			cur = cur->left;
			while (cur->right != nullptr)
			{
				cur = cur->right;
			}
			terminalNode->data = cur->data;
			terminalNode = cur;
		}
	}
	//case 3. delNode doesn't have subtree.

#pragma endregion
#pragma region Deletenode
	//case1. terminalNode is red node
	if (terminalNode->color == red)
	{
		if (terminalNode->parent->right == terminalNode)
		{
			terminalNode->parent->right = nullptr;
			free(terminalNode);
		}
		else
		{
			terminalNode->parent->left = nullptr;
			free(terminalNode);
		}
	}
	//case2. terminalNode is black node
	else if (terminalNode->color == black)
	{
		//case2-1. parent is red node.
		if (terminalNode->parent->color == red)
		{
			if (terminalNode->parent->right == terminalNode)
			{
				RBnode* parent = terminalNode->parent;
				parent->right = nullptr;
				free(terminalNode);

				parent->color = black;
				if (parent->left != nullptr)
				{
					parent->left->color = red;
					//Check double-red
					if (parent->left->left != nullptr)
					{
						if (parent->left->left->color == red)
							FixDoubleRed(parent->left, parent->left->left);
						else if (parent->left->right != nullptr)
						{
							if (parent->left->right->color == red)
								FixDoubleRed(parent->left, parent->left->right);
						}
					}
				}
			}
			else
			{
				RBnode* parent = terminalNode->parent;
				parent->left = nullptr;
				free(terminalNode);

				parent->color = black;
				if (parent->right != nullptr)
				{
					parent->right->color = red;
					//Check double-red
					if (parent->right->right != nullptr)
					{
						if (parent->right->right->color == red)
							FixDoubleRed(parent->right, parent->right->right);
						else if (parent->right->left != nullptr)
						{
							if(parent->right->left->color == red)
								FixDoubleRed(parent->right, parent->right->left);
						}
					}
				}
			}
		}
		//case2-2. parent is black node
		else if (terminalNode->parent->color == black)
		{
			RBnode* parent = terminalNode->parent;
			TData delNodedata = terminalNode->data;

			//adjust black-height
			if (parent->right == terminalNode)
			{
				RBnode* temp = parent;
				RBnode* prevnode = terminalNode;
				while (temp != nullptr)
				{
					if (temp->left == prevnode)
						DecreaseBH(temp->right);
					else
						DecreaseBH(temp->left);

					prevnode = temp;
					temp = temp->parent;
				}
				parent->right = nullptr;
			}
			else
			{
				RBnode* temp = parent;
				RBnode* prevnode = terminalNode;

				while (temp != nullptr)
				{
					if (temp->left == prevnode)
						DecreaseBH(temp->right);
					else
						DecreaseBH(temp->left);

					prevnode = temp;
					temp = temp->parent;
				}
				parent->left = nullptr;
			}
			if (terminalNode == root)
				root = nullptr;
			free(terminalNode);

			//Double-red check
			RBnode* temp = root;
			while (temp != nullptr)
			{
				if (temp->data > delNodedata)	//right direction
				{
					if (temp->color == red)
					{
						if (temp->right != nullptr)
						{
							if (temp->right->color == red)
							{
								RBnode* tempParent = temp->parent;
								FixDoubleRed(temp, temp->right);

								//fix location of temp
								temp = tempParent;		

								if (temp->data > delNodedata)
									temp = temp->left;
								else
									temp = temp->right;
							}
						}
					}
					else if (temp->right != nullptr)
					{
						bool leftcheck = true;
						if (temp->right->color == red)
						{
							if (temp->right->right != nullptr)
							{
								if (temp->right->right->color == red)
								{
									leftcheck = false;
									FixDoubleRed(temp->right, temp->right->right);
								}
							}
							else if (temp->right->left != nullptr && leftcheck == true)
							{
								if (temp->right->left->color == red)
									FixDoubleRed(temp->right, temp->right->left);
							}
						}
					}
				}
				else			//left direction
				{
					if (temp->color == red)
					{
						if (temp->left != nullptr)
						{
							if (temp->left->color == red)
							{
								RBnode* tempParent = temp->parent;
								FixDoubleRed(temp, temp->left);

								//fix location of temp
								temp = tempParent;

								if (temp->data > delNodedata)
									temp = temp->left;
								else
									temp = temp->right;
							}
						}
					}
					else if (temp->left != nullptr)
					{
						bool rightcheck = true;
						if (temp->left->color == red)
						{
							if (temp->left->right != nullptr)
							{
								if (temp->left->right->color == red)
								{
									FixDoubleRed(temp->left, temp->left->right);
									rightcheck = false;
								}
							}
							else if (temp->left->left != nullptr && rightcheck == true)
							{
								if (temp->left->left->color == red)
									FixDoubleRed(temp->left, temp->left->left);
							}
						}
					}
				}

				if (temp->data > delNodedata)
					temp = temp->left;
				else
					temp = temp->right;
			}
		}
	}
#pragma endregion

	return true;
}

void RBTree::DecreaseBH(RBnode * _node)
{
	if (_node == nullptr || _node == Vroot)
		return;

	if (_node->color == black)
		_node->color = red;
	else		//if _node is already red, make its child nodes red.
	{
		DecreaseBH(_node->left);
		DecreaseBH(_node->right);
	}
}

void RBTree::ShowTree()
{
	ShowTree(root, 1, 0, GetHeight(root));
}

void RBTree::ShowTree(RBnode * pNode, int width, int height, int maxheight)
{
	if (pNode == nullptr)
	{
		short x = 3 * (2 * width - 1)*pow(2, maxheight - height) - 2;
		short y = 3 * height;

		COORD pos = { x,y + 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		printf("( x)");
		return;
	}

	short x = 3 * (2 * width - 1)*pow(2, maxheight - height) - 2;
	short y = 3 * height;

	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	if(pNode->color == black)
		printf("____");

	pos = { x , y + 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("(%2d)", pNode->data);

	pos = { x , y + 2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("----");

	ShowTree(pNode->left, width * 2 - 1, height + 1, maxheight);
	ShowTree(pNode->right, width * 2, height + 1, maxheight);
}

int RBTree::GetHeight(RBnode * _node)
{
	if (_node == nullptr)
		return -1;

	int rheight = GetHeight(_node->right);
	int lheight = GetHeight(_node->left);

	if (rheight < lheight)
		return lheight + 1;
	else
		return rheight + 1;
}

RBTree::RBTree()
{
	Vroot = Handler::MakeRBTreeNode();
	Vroot->color = black;
	root = nullptr;
}

RBTree::~RBTree()
{
	free(Vroot);
	Handler::DeleteTree(root);
}