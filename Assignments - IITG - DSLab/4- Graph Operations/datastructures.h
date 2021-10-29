//used for heap node
class Node
{
private:
	int vertex, cost, index;
	Node * self;

public:
	Node(){}
	Node(int v, int c, int i)
	{
		vertex = v;
		cost = c;
		index = i;
	}
	void setCost(int);
    int getCost();
    int getVertex();
    void setIndex(int);
    int getIndex();

    friend class Heap;
};



//used for storing edge classifications of DFS
class EdgeType
{
private:
	int src, dest;
	int type; //0->tree, 1->forward, 2->back, 3->cross
	
public:
	EdgeType(int s, int d)
	{
		src = s;
		dest = d;
	}
	int getSrc();
	int getDest();
	int getType();
	void setType(int);
};



//node for queue
class QueueNode
{
private:
	int vertex;
	QueueNode * next;

public:
	QueueNode(int v)
	{
		vertex = v;
		next = nullptr;
	}

	friend class Queue;
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
	void enqueue(int); //function to enqueue
	int dequeue(); //function to dequeue
	bool isEmpty(); //function to check if the queue is empty
	int getSize(); //function to get the size of the queue
	int viewFront(); //function to get the front
};



//node for stack
class StackNode
{
private:
	int vertex;
	StackNode * next;

public:
	StackNode(int v)
	{
		vertex = v;
		next = nullptr;
	}

	friend class Stack;
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
	void push(int); //function to push
	int pop(); //function to pop
	bool isEmpty(); //function to check if the stack is empty
	int getSize(); //function to get the size of the stack
	int viewTop(); //function to get the top
};



class Heap
{
private:
	Node * pointers, * pathCosts;
	int heapSize;

	int left(int);
	int right(int);
	int parent(int);
	void heapify(int);

public:
	void buildHeap(int, int);
	Node extractRoot();
	void decreaseKey(int, int);
};



class Graph
{
private:
	vector<pair<int,int>> * graph;
	int V;

public:
	//utility functions
	void set(int);
	int getVertex();
	void setVertex(int);
	void addEdge(int, int, int);
	void removeEdge(int, int);
	void removeEdgeWithWeight(int, int, int);
	void print(int, ...);
	void clear();

	//DFS traversal
	vector<EdgeType> traverseDFS(int, vector<EdgeType>);
	vector<EdgeType> runDFS(vector<EdgeType>, int);
	
	//Tarjan's Algo
	vector<vector<int>> runDFSForTarjan(int, vector<vector<int>>);
	vector<vector<int>> runTarjan(vector<vector<int>>);
	
	//Minimal Graph Finding
	void getEdgeMap(int);
	void addEdgesWithinSCC(Graph, vector<vector<int>>, vector<EdgeType>);
	int * isSubset(vector<EdgeType>, int, int, int);
	void addEdgesInterSCC(Graph, Graph, vector<vector<int>>, vector<EdgeType>);
	bool removeExtraEdges(vector<EdgeType>);

	//Semiconnected check
	void buildDAG (vector<vector<int>>, Graph);
	int * runTopologicalSort();
	bool checkSemiConnected(int *);

	//Dijkstra's Algo
	int * relaxEdge(Heap, int *, int, int, int);
	int * runDijkstra(int);
};