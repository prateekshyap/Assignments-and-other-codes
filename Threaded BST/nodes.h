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
Node for Binary Search Tree
Contains integer data, subtree counts, two self references, two boolean threads
*/
class TreeNode
{
public:
	TreeNode * left;
	bool leftThread;
	int leftSubtreeCount;
	int data;
	int rightSubtreeCount;
	bool rightThread;
	TreeNode * right;
	TreeNode(int x)
	{
		data = x;
		leftThread = rightThread = false;
		left = right = nullptr;
		leftSubtreeCount = rightSubtreeCount = 0;
	}
};

/*
Node for Queue
Contains a reference to TreeNode, a self reference
*/
class QueueNode
{
public:
	TreeNode * treeNode;
	QueueNode * next;
	QueueNode(TreeNode * node)
	{
		treeNode = node;
		next = nullptr;
	}
};