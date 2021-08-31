class List
{
public:
	ListNode * head, * tail; //head and tail pointers
	List()
	{
		/*create a dummy node and point both head and tail to it*/
		head = new ListNode(0);
		tail = head;
	}
	void addNode(TreeNode *); //function to add a new node at the end of the list
	void trim(); //function to delete the dummy node
};

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
	void push(TreeNode *); //function to push
	TreeNode * pop(); //function to pop
	bool isEmpty(); //function to check if the stack is empty
	int getSize(); //function to get the size of the stack
	TreeNode * viewTop(); //function to get the top
};

class AVLTree
{
public:
	TreeNode * root; //root pointer
	AVLTree()
	{
		root = new TreeNode(-1);
		//root->left = new TreeNode(0);
	}
	AVLTree(const AVLTree &avlt) //copy constructor
	{
		if (avlt.root->right == nullptr) //store null if root is null
			root = nullptr;
		unordered_map<TreeNode *, TreeNode *> treeNodeMap; //create a hashmap to map the nodes of two trees
		root = copyNodes(avlt.root,treeNodeMap); //call the copy nodes function
	}
	~AVLTree()
	{
		delete root;
	}
	void insert(int); //insert
	bool search(int); //search
	void print(); //print tree
	void deleteK(int); //delete

private:
	bool isLeaf(TreeNode *); //function to check whether a node is leaf or not
	TreeNode * copyNodes(TreeNode *, unordered_map<TreeNode *, TreeNode *> &); //function called by the copy constructor
	TreeNode * searchNode(int); // search a node
	TreeNode * deleteLeafNode(TreeNode *,TreeNode *); //function to delete the leaf node
	TreeNode * deleteNodeWithSingleChild(TreeNode *,TreeNode *); //function to delete a node with single child
	TreeNode * getParent(TreeNode *); //function to find the parent of a given node
	TreeNode * leftMost(TreeNode *); //function to find the leftmost or the smallest node
	TreeNode * rightMost(TreeNode *); //function to find the rightmost or the largest node
	/*void reduceSubtreeCount(TreeNode *); //function to reduce the subtree count during deletion
	bool isLeaf(TreeNode *); //function to check whether a node is leaf or not
	*/
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
	void enqueue(TreeNode *); //function to enqueue
	TreeNode * dequeue(); //function to dequeue
	bool isEmpty(); //function to check if the queue is empty
	int getSize(); //function to get the size of the queue
};