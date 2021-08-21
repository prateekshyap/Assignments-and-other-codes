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

class BinarySearchTree
{
public:
	TreeNode * root; //root pointer
	BinarySearchTree()
	{
		root = nullptr;
	}
	BinarySearchTree(const BinarySearchTree &bst) //copy constructor
	{
		if (bst.root == nullptr) //store null if root is null
			root = nullptr;
		unordered_map<TreeNode *, TreeNode *> treeNodeMap; //create a hashmap to map the nodes of two trees
		root = copyNodes(bst.root,treeNodeMap); //call the copy nodes function
	}
	void insert(int); //insert
	TreeNode * search(int); //search
	void deleteX(int); //delete
	List reverseInOrder(); //reverse inorder
	int successor(TreeNode *); //successor
	TreeNode * split(int); //split
	List inOrder(); //inorder
	List allElementsBetween(int, int); //all elements between k1 and k2
	int kthElement(int); //kth largest element
	void printTree(); //print tree

private:
	void insertIntoTree(TreeNode *,int); //recursive insertion function
	void reduceSubtreeCount(TreeNode *); //function to reduce the subtree count during deletion
	bool isLeaf(TreeNode *); //function to check whether a node is leaf or not
	TreeNode * deleteLeafNode(TreeNode *,TreeNode *); //function to delete the leaf node
	TreeNode * deleteNodeWithSingleChild(TreeNode *,TreeNode *); //function to delete a node with single child
	TreeNode * leftMost(TreeNode *); //function to find the leftmost or the smallest node
	TreeNode * rightMost(TreeNode *); //function to find the rightmost or the largest node
	TreeNode * getParent(TreeNode *); //function to find the parent of a given node
	TreeNode * copyNodes(TreeNode *, unordered_map<TreeNode *, TreeNode *> &); //function called by the copy constructor
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