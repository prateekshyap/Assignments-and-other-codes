//#include "datastructures.h"
/*
* Node for Linked List
* Contains integer and a self reference
*/
class ListNode
{
public:
	int data;
	ListNode * next;
	ListNode(int x)
	{
		data = x;
		next = nullptr;
	}
};

/*
* Node for AVL Tree
* Contains integer data, two self references, balance factor
*/
class TreeNode
{
private:
	TreeNode * left;
	int data;
	int bF;
	TreeNode * right;

public:
	TreeNode(int x)
	{
		data = x;
		bF = 0;
		left = right = nullptr;
	}

	friend class AVLTree;
	friend class List;
};

/*
* Node for Queue
* Contains a reference to TreeNode, a self reference
*/
class QueueNode
{
private:
	TreeNode * treeNode;
	QueueNode * next;

public:
	QueueNode(TreeNode * node)
	{
		treeNode = node;
		next = nullptr;
	}

	friend class Queue;
};