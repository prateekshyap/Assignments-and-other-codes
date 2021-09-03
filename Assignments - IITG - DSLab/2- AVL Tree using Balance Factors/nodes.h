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
	~TreeNode()
	{
		delete left;
		delete right;
	}
	friend class AVLTree;
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

/*
* Node for Stack
* Contains a reference to TreeNode, a self reference
*/
class StackNode
{
private:
	TreeNode * treeNode;
	StackNode * next;

public:
	StackNode(TreeNode * node)
	{
		treeNode = node;
		next = nullptr;
	}

	friend class Stack;
};