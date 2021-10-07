class Stack
{
private:
	int size; //size of the stack

public:
	StackNode * top; //top pointer of stack
	Stack()
	{
		top = nullptr; //initialize to null
		size = 0; //initialize to 0
	}
	void push(TreapNode *); //function to push
	TreapNode * pop(); //function to pop
	bool isEmpty(); //function to check if the stack is empty
	int getSize(); //function to get the size of the stack
	TreapNode * viewTop(); //function to get the top
};

class Treap
{
public:
	TreapNode * root; //root pointer
	Treap()
	{
		root = new TreapNode(-20000,-20000);
	}
	Treap(const Treap &treap) //copy constructor
	{
		if (treap.root->right == nullptr) //store null if root is null
			root->right = nullptr;
		unordered_map<TreapNode *, TreapNode *> TreapNodeMap; //create a hashmap to map the nodes of two trees
		//root->right = copyNodes(treap.root->right,TreapNodeMap); //call the copy nodes function
	}
	void insert(int); //insert
	void deleteX(int); //delete
	bool search(int); //search
	//void split(); //split
	void print(const char *); //print tree
	void evaluatePerformance();
	void storeKeysInFile();

private:
	bool isLeaf(TreapNode *); //function to check whether a node is leaf or not
	TreapNode * searchNode(int); //search a node
	TreapNode * getParent(TreapNode *); //function to find the parent of a given node
	TreapNode * leftRotate(TreapNode *, TreapNode *); //function for LL rotation
	TreapNode * rightRotate(TreapNode *, TreapNode *); //function for RR rotation
	void transplant(TreapNode *, TreapNode *, TreapNode *); //function to attach a subtree to main tree
	TreapNode * copyNodes(TreapNode *, unordered_map<TreapNode *, TreapNode *> &); //function called by the copy constructor
	int getTotalDepth(TreapNode *); //find the total depth of the tree
};

class Queue
{
private:
	int size; //size of the queue

public:
	QueueNode * front, * rear; //front and rear pointer
	Queue()
	{
		front = rear = nullptr; //initialize both the pointers to null
		size = 0; //initialize size to 0
	}
	void enqueue(TreapNode *); //function to enqueue
	TreapNode * dequeue(); //function to dequeue
	bool isEmpty(); //function to check if the queue is empty
	int getSize(); //function to get the size of the queue
};