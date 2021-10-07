/*
* Node for Treap
* Contains integer data, two self references, priority
*/
class TreapNode
{
private:
	TreapNode * left;
	int data;
	int priority;
	TreapNode * right;

public:
	TreapNode(int x, int p)
	{
		data = x;
		priority = p;
		left = right = nullptr;
	}
	
	friend class Treap;
};

/*
* Node for Queue
* Contains a reference to TreapNode, a self reference
*/
class QueueNode
{
private:
	TreapNode * treapNode;
	QueueNode * next;

public:
	QueueNode(TreapNode * node)
	{
		treapNode = node;
		next = nullptr;
	}

	friend class Queue;
};

/*
* Node for Stack
* Contains a reference to TreapNode, a self reference
*/
class StackNode
{
private:
	TreapNode * treapNode;
	StackNode * next;

public:
	StackNode(TreapNode * node)
	{
		treapNode = node;
		next = nullptr;
	}

	friend class Stack;
};