int fileCount = -1, fileType = -1, randomInputCount = 0, prime1 = 1103, prime2 = 1193;
int denseStart = 40, denseEnd = 60, midStart = 20, midEnd = 40, sparseStart = 10, sparseEnd = 20, weightLimit = 100;
string colors[] = {"red","blue","green","yellow","magenta","aqua","brown","crimson","coral","darkgoldenrod","darkgreen","darkkhaki","darkorange","gold","orange","lightblue","lightcoral","salmon","khaki","maroon","olive","purple","teal","darkred"};
int noc = 24;

string printFileName = "";
ofstream outputFile;
ifstream inputFile;
Graph graph;
unordered_map<int,int> edgeMap, dagEdgeMap, dagGraphMap;

//for Tarja's algo
int * discovery = nullptr, * low = nullptr, * startTimes = nullptr, * endTimes = nullptr, * dfsOrder = nullptr, * dfsParent = nullptr, * dfsChild = nullptr;
bool * added = nullptr, * visited = nullptr;
Stack vStack;
int timer = 1, dfsOrderIndex = 0, cycleIndex = 0;

void createGraph();
void generateInput(int, string, int, int);
int executeModification();
void performBulkModification(string);







/**************************************************************************************************************
 * Utility functions
 * ***********************************************************************************************************/

void printMessage(int level, string outputFileName)
{
	switch (level)
	{
		case 0:
			cout << endl ;
			cout << "----------------------------------------------------" << endl;
			cout << "                  Graph (Main Menu)                 " << endl;
			cout << "----------------------------------------------------" << endl << endl;
			cout << "1. Build mode" << endl;
			cout << "This mode supports graph creation, adding or removing" << endl;
			cout << "edges or vertices etc" << endl << endl;
			cout << "2. Operations mode" << endl;
			cout << "This mode supports other type of operations which" << endl;
			cout << "doesn't try to modify the original graph" << endl << endl;
			cout << "3. Generate images " << endl << endl;
			cout << "4. Quit" << endl << endl;
			cout << "Output is stored in " << outputFileName << endl << endl;
			cout << "Enter a number-" << endl;
			break;

		case 1:
			cout << endl << "1. Create a new Graph" << endl;
			cout << "2. Modify the existing Graph" << endl;
			cout << "3. Go back to main menu" << endl;
			cout << "Enter a number-" << endl;
			break;

		case 2:
			cout << endl << "1. Add a new edge" << endl;
			cout << "2. Remove an existing edge" << endl;
			cout << "3. Perform above operations in bulk" << endl;
			cout << "4. Print" << endl;
			cout << "5. Go back to previous menu" << endl;
			cout << "6. Go back to main menu" << endl;
			cout << "Enter a number-" << endl;
			break;

		case 3:
			cout << endl << "1. BFS traversal" << endl;
			cout << "2. DFS traversal" << endl;
			cout << "3. Find strongly connected components" << endl;
			cout << "4. Create minimal graph" << endl;
			cout << "5. Check if the graph is semiconnected" << endl;
			cout << "6. Find shortest path from a single source" << endl;
			cout << "7. Go back to main menu" << endl;
			cout << "Enter a number-" << endl;
			break;

		default:
			cout << "";
	}
}

void generatePNG(int os)
{
	/*if os is windows run the batch file*/
	if (os == 0)
		std :: system("commands.bat");
	/*if os is linux change the permission and run the shell script*/
	else if (os == 1)
	{
		std :: system("chmod +x commands.sh");
		std :: system("./commands.sh");
	}
}

void executeBuildMode()
{
	string inputFileName = "", inputString = "";
	int choice = 0, status = -1;
	ifstream inputFile;

	while (true)
	{
		printMessage(1,"");
		cin >> choice;

		switch(choice)
		{
			case 1: //create
				outputFile << "Creating new graph";
				createGraph();
				break;

			case 2: //modify
				status = executeModification();
				if (status == 0) return;
				break;

			case 3: //main menu
				return;

			default:
				cout << "Invalid input! Please try again!" << endl;
		}
	}
}

void createGraph()
{
	int choice = 0, V = 0, E = 0, src = 0, dest = 0, weight = 0;
	string inputFileName = "", inputString = "";
	bool printStatus = true;

	//take input for random input file or manual input file
	cout << "Enter a number(0 for random input file / 1 for manual input file)-" << endl;
	cin >> choice;

	if (choice == 0) //if random
	{
		inputFileName = "randomInput";
		inputFileName.append(to_string(randomInputCount++));
		inputFileName.append(".txt");
		cout << "Enter number of vertices-" << endl; //take the number of operations
		cin >> V;

		cout << "Which type of Graph do you want?\nEnter \"-1\" for dense\n\"-2\" for medium\n\"-3\" for sparse\nDon't include double quotes\nYou can enter the percentage of edges\nEntering 10 will add 10\% of the total possible edges)-" << endl;
		cin >> choice;

		if (randomInputCount == 1)
			generateInput(V,inputFileName,choice,0);
		else
			generateInput(V,inputFileName,choice,1);
	}
	else if (choice == 1) //if manual
	{
		cout << "Input format: (For a graph with 3 vertices and 2 edges" << endl;
		cout << "Where edges are from 0 to 2 with weight 6 and from 1 to 2 with weight 7)" << endl;
		cout << "3 2" << endl;
		cout << "0 2 6" << endl;
		cout << "1 2 7" << endl;
		cout << "Write the input in a .txt file and enter the name-" << endl;
		cin >> inputFileName; //take file name from user
	}
	else
	{
		cout << "Try again!" << endl;
		return;
	}
	outputFile << " (input file name- " << inputFileName << ")" << endl;
	inputFile.open(inputFileName);

	//reset the graph with new parameters
	graph.clear();
	inputFile >> V >> E;
	graph.set(V);

	//add the edges
	for (int i = 0; i < E; ++i)
	{
		inputFile >> src >> dest >> weight;
		graph.addEdge(src, dest, weight);
	}

	inputFile.close();
	outputFile << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
	outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
	graph.print(1,printFileName.c_str()); //print the graph
}

void generateInput(int V, string fileName, int edgeDensity, int beginStatus)
{
	cout << endl << "Generating input file" << endl;
	ofstream file;
	file.open(fileName);
	srand(time(0));
	int i = 0, src = 0, dest = 0, weight = 0;
	
	int possibleEdges = V*(V-1)/2; //total number of possible edges
	int E = 50;

	//calculate the required number of edges
	if (edgeDensity == -1)
		E = possibleEdges*(denseStart+rand()%(denseEnd-denseStart+1))/100;
	else if (edgeDensity == -2)
		E = possibleEdges*(midStart+rand()%(midEnd-midStart+1))/100;
	else if (edgeDensity == -3)
		E = possibleEdges*(sparseStart+rand()%(sparseEnd-sparseStart+1))/100;
	else
		E = possibleEdges*edgeDensity/100;

	//write to file
	file << V << " " << E << endl;
	for (i = 0; i < E; ++i)
	{
		src = rand()%V;
		dest = rand()%V;
		weight = 1+rand()%weightLimit;
		
		file << src << " " << dest << " " << weight << endl;
	}
	file.close();
}

int executeModification()
{
	int choice = 0, src = 0, dest = 0, weight = 0;
	string inputFileName = "";

	while (true)
	{
		printMessage(2,"");
		cin >> choice;

		switch(choice)
		{
			case 1: //add edge
				cout << "Enter source vertex" << endl;
				cin >> src;
				cout << "Enter destination vertex" << endl;
				cin >> dest;
				cout << "Enter weight" << endl;
				cin >> weight;
				outputFile << "Adding " << src << " to " << dest << " with weight " << weight << endl;
				graph.addEdge(src, dest, weight);
				break;

			case 2: //remove edge
				cout << "Enter source vertex" << endl;
				cin >> src;
				cout << "Enter destination vertex" << endl;
				cin >> dest;
				cout << "Enter weight" << endl;
				cin >> weight;
				outputFile << "Removing " << src << " to " << dest << " with weight " << weight << endl;
				graph.removeEdgeWithWeight(src, dest, weight);
				break;

			case 3: //bulk
				cout << "Input format: (Enter operation number followed by the parameter values)" << endl;
				cout << "1 2 6 19" << endl;
				cout << "2 2 7" << endl;
				cout << "The above sequence means there will be a new edge from 2 to 6 with weight 19" << endl;
				cout << "The edge from 2 to 7 will be removed" << endl;
				cout << "Write the input in a .txt file and enter the name-" << endl;
				cin >> inputFileName; //take file name from user
				outputFile << "Performing addition and removal of edges in bulk (input file name- " << inputFileName << ")" << endl;
				performBulkModification(inputFileName);
				outputFile << "Printing new graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(1,printFileName.c_str());
				break;

			case 4: //print
				outputFile << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(1,printFileName.c_str());
				break;

			case 5: //previous menu
				return 1;

			case 6: //main menu
				return 0;

			default:
				cout << "Invalid input! Please try again!" << endl;
		}
	}
}

void performBulkModification(string fileName)
{
	int choice = 0, src = 0, dest = 0, weight = 0;
	ifstream inputFile;
	inputFile.open(fileName);

	while (inputFile >> choice)
	{
		switch(choice)
		{
			case 1: //add edge
				inputFile >> src;
				inputFile >> dest;
				inputFile >> weight;
				outputFile << "Adding " << src << " to " << dest << " with weight " << weight << endl;
				graph.addEdge(src, dest, weight);
				break;

			case 2: //remove edge
				inputFile >> src;
				inputFile >> dest;
				inputFile >> weight;
				outputFile << "Removing " << src << " to " << dest << " with weight " << weight << endl;
				graph.removeEdgeWithWeight(src, dest, weight);
				break;

			default:
				cout << "Invalid input! Please try again!" << endl;
		}
	}
}

void executeOperationsMode()
{
	int choice = 0, src = 0, dest = 0;
	bool result = false;
	int * costs = new int[graph.getVertex()], * topoSort = nullptr;
	ifstream inputFile;
	int ** adjMat = nullptr;
	string inputString = "";

	while (true)
	{
		printMessage(3,"");
		cin >> choice;
		vector<vector<int>> components;
		vector<EdgeType> edgeNames;
		Graph dag, minimalGraph;
		
		switch(choice)
		{
			case 1: //bfs
				outputFile << endl << "BFS" << endl;
				cout << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(2,printFileName.c_str(),3);
				break;

			case 2: //dfs
				outputFile << endl << "DFS" << endl;
				edgeNames = graph.runDFS(edgeNames,0);
				cout << "Order-" << endl;
				outputFile << "Order-" << endl;
				for (int i = 0; i < dfsOrderIndex; ++i)
				{
					cout << dfsOrder[i] << " ";
					outputFile << dfsOrder[i] << " ";
				}
				cout << endl; outputFile << endl << endl;
				for (EdgeType it : edgeNames)
				{
					cout << it.getSrc() << " -> " << it.getDest() << " ";
					outputFile << it.getSrc() << " -> " << it.getDest() << " ";
					if (it.getType() == 0) { cout << "Tree Edge" << endl; outputFile << "Tree Edge" << endl; }
					else if (it.getType() == 1)	{ cout << "Forward Edge" << endl; outputFile << "Forward Edge" << endl; }
					else if (it.getType() == 2) { cout << "Back Edge" << endl;  outputFile << "Back Edge" << endl; }
					else { cout << "Cross Edge" << endl;  outputFile << "Cross Edge" << endl; }
				}
				cout << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(3,printFileName.c_str(),4,edgeNames);
				break;

			case 3: //tarjan
				outputFile << endl << "Running Tarjan's Algorithm" << endl;
				components = graph.runTarjan(components);
				for (int i = 0; i < components.size(); ++i)
				{
			        for (int j = 0; j < components[i].size(); ++j)
			        {
			            cout << components[i][j] << " ";
			            outputFile << components[i][j] << " ";
			        }
			        cout << endl;
			        outputFile << endl;
			    }
				cout << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(3,printFileName.c_str(),2,components);
			    break;

			case 4: //minimal graph
				outputFile << endl << "Finding minimal graph" << endl;
				//DFS
				edgeNames = graph.runDFS(edgeNames,0);
				outputFile << "Order-" << endl;
				for (int i = 0; i < dfsOrderIndex; ++i)
					outputFile << dfsOrder[i] << " ";
				outputFile << endl << endl;
				for (EdgeType it : edgeNames)
				{
					outputFile << it.getSrc() << " -> " << it.getDest() << " ";
					if (it.getType() == 0) outputFile << "Tree Edge" << endl;
					else if (it.getType() == 1)	outputFile << "Forward Edge" << endl;
					else if (it.getType() == 2) outputFile << "Back Edge" << endl;
					else outputFile << "Cross Edge" << endl;
				}
				cout << "Printing graph of edge classifications with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing graph of edge classifications with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(3,printFileName.c_str(),4,edgeNames);
				//Tarjan
				components = graph.runTarjan(components);
				for (int i = 0; i < components.size(); ++i)
				{
			        for (int j = 0; j < components[i].size(); ++j)
			            outputFile << components[i][j] << " ";
			        outputFile << endl;
			    }
				cout << "Printing strongly connected components graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing strongly connected components graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(3,printFileName.c_str(),2,components);
				//DAG (component graph)
				dag.buildDAG(components,graph);
				cout << "Printing directed acyclic graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing directed acyclic graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				dag.print(1,printFileName.c_str());
				//build minimal graph
				minimalGraph.set(graph.getVertex());
				graph.getEdgeMap(0);
				minimalGraph.addEdgesWithinSCC(graph,components,edgeNames);
				minimalGraph.addEdgesInterSCC(graph,dag,components,edgeNames);
				edgeNames.clear();
				edgeNames = minimalGraph.runDFS(edgeNames,0);
				minimalGraph.getEdgeMap(0);
				minimalGraph.removeExtraEdges(edgeNames);
				cout << "Printing minimal graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing minimal graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				minimalGraph.print(1,printFileName.c_str());
				cout << "Do you want to replace the current graph with the minimal graph? (Enter Y/N)" << endl;
				cin >> inputString;
				if (inputString.compare("Y") == 0 || inputString.compare("y") == 0)
				{
					graph = minimalGraph;
					cout << "Replaced original graph with minimal graph" << endl;
					outputFile << "Replaced original graph with minimal graph" << endl;
				}
				break;

			case 5: //semi connected
				outputFile << endl << "Checking whether the graph is semiconnected" << endl;
				components = graph.runTarjan(components);
				cout << "Printing strongly connected components graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing strongly connected components graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(3,printFileName.c_str(),2,components);
				dag.buildDAG(components,graph);
				cout << "Printing directed acyclic graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing directed acyclic graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				dag.print(1,printFileName.c_str());
				topoSort = dag.runTopologicalSort();
				result = dag.checkSemiConnected(topoSort);
				if (result)
				{
					cout << "Semi connected" << endl;
					outputFile << "Semi connected" << endl;
				}
				else
				{
					cout << "Not semi connected" << endl;
					outputFile << "Not semi connected" << endl;
				}
				break;

			case 6: //dijkstra
				cout << "Enter source vertex" << endl;
				cin >> src;
				outputFile << endl << "Running Dijkstra's Algorithm with source " << src << endl;
				costs = graph.runDijkstra(src);
				cout << "Costs-" << endl; outputFile << "Costs-" << endl;
				for (int i = 0; i < graph.getVertex(); ++i)
				{
					cout << costs[i] << " ";
					outputFile << costs[i] << " ";
				}
				outputFile << endl << "Parents-" << endl;
				for (int i = graph.getVertex(); i < graph.getVertex()*2; ++i)
					outputFile << costs[i] << " ";
				cout << endl;
				outputFile << endl;
				cout << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Printing graph with file Name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl;
				graph.print(3,printFileName.c_str(),1,costs);
				break;

			case 7: //main menu
				return;

			default:
				cout << "Invalid input! Please try again!" << endl;
		}
	}
}








/**************************************************************************************************************
 * Node functions
 * ***********************************************************************************************************/

void Node :: setCost(int c) { cost = c; }
int Node :: getCost() { return cost; }
int Node :: getVertex() { return vertex; }
void Node :: setIndex(int i){ index = i; }
int Node :: getIndex() { return index; }








/**************************************************************************************************************
 * Edge Classification functions
 * ***********************************************************************************************************/

int EdgeType :: getSrc() { return src; }
int EdgeType :: getDest() { return dest; }
int EdgeType :: getType() { return type; }
void EdgeType :: setType(int t) { type = t; }








/**************************************************************************************************************
 * Queue functions
 * ***********************************************************************************************************/
void Queue :: enqueue(int vertex)
{
	QueueNode * newNode = new QueueNode(vertex); //create a new node
	if (front == nullptr && rear == nullptr) //if front and rear are null, make both point to the new node
	{
		front = newNode;
		rear = newNode;
	}
	else //otherwise store the new node in the next of rear and move rear
	{
		rear->next = newNode;
		rear = rear->next;
	}
	++size; //increase queue size
}

int Queue :: dequeue()
{
	int returnNode = front->vertex; //hold the node to return
	if (front == rear) //if this is the last node, reset the queue
	{
		delete(front);
		front = rear = nullptr;
		size = 0;
	}
	else //otherwise move front and reduce the size
	{
		QueueNode * temp = front;
		front = front->next;
		delete(temp);
		--size;
	}
	return returnNode;
}

bool Queue :: isEmpty() //check for emptiness
{

	return size == 0 ? true : false;
}

int Queue :: getSize() //return the size
{

	return size;
}

int Queue :: viewFront()
{

	return front->vertex;
}








/**************************************************************************************************************
 * Stack functions
 * ***********************************************************************************************************/

void Stack :: push(int vertex)
{
	StackNode * newNode = new StackNode(vertex); //create a new node
	if (top == nullptr) //if top is null, make it point to the new node
		top = newNode;
	else //otherwise store the new node before top and move top
	{
		newNode->next = top;
		top = newNode;
	}
	++size; //increase stack size
}

int Stack :: pop()
{
	int returnNode = top->vertex; //hold the node to return
	if (top->next == nullptr) //if this is the last node, reset the stack
	{
		delete(top);
		top = nullptr;
		size = 0;
	}
	else //otherwise move top and reduce size
	{
		StackNode * temp = top;
		top = top->next;
		delete(temp);
		--size;
	}
	return returnNode;
}

bool Stack :: isEmpty() //check for emptiness
{

	return size == 0 ? true : false;
}

int Stack :: getSize() //return the size
{

	return size;
}

int Stack :: viewTop()
{

	return top->vertex;
}









/**************************************************************************************************************
 * Heap functions
 * ***********************************************************************************************************/

int Heap :: left(int root) { return (2*root)+1; }
int Heap :: right(int root) { return (2*root)+2; }
int Heap :: parent(int root) { return (root-1)/2; }

void Heap :: heapify(int root)
{
	//update min
	int min = root;
    if (left(root) < heapSize && pathCosts[left(root)].getCost() < pathCosts[min].getCost())
        min = left(root);
    if (right(root) < heapSize && pathCosts[right(root)].getCost() < pathCosts[min].getCost())
        min = right(root);

    //if min is not root, then we need to swap and recur on the child node
    if (min != root)
    {
        Node temp = pathCosts[min];
        pathCosts[min] = pathCosts[root];
        pathCosts[root] = temp;

        //set information properly
        pointers[pathCosts[min].getVertex()].self = &pathCosts[min];
        pointers[pathCosts[root].getVertex()].self = &pathCosts[root];
        pathCosts[min].setIndex(min);
        pathCosts[root].setIndex(root);

        //recur
        heapify(min);
    }
}

void Heap :: buildHeap(int V, int S)
{
	pointers = (Node *)malloc(sizeof(Node)*V);
	pathCosts = (Node *)malloc(sizeof(Node)*V);
	heapSize = V;

	//store 0 in source, and a maximum value in others
	for (int i = 0; i < V; ++i)
	{
		if (i != S)
		{
			pathCosts[i] = Node(i, 1000000000, i);
			pointers[i].self = &pathCosts[i];
		}
		else
		{
			pathCosts[i] = Node(i, 0, i);
			pointers[i].self = &pathCosts[i];
		}
	}

	//call heapify for each non leaf node in reverse order
	for (int i = (heapSize/2)-1; i >= 0; --i)
		heapify(i);
}

Node Heap :: extractRoot()
{
	//swap root with the last node
	Node temp = pathCosts[0];
    pathCosts[0] = pathCosts[heapSize-1];

    //set the informations properly
    pathCosts[0].setIndex(0);
    pointers[pathCosts[0].getVertex()].self = &pathCosts[0];

    //reduce heap size
    --heapSize;

    //heapify root
    heapify(0);

    return temp;
}

void Heap :: decreaseKey(int i, int newCost)
{
	//get the index of the i vertex and set its new cost
	int index = pointers[i].self->getIndex();
	pathCosts[index].setCost(newCost);
    
    //get its parent
    int par = parent(index);

    //till index has parent
    while (index != 0)
    {
    	//swap if it violates heap property
        if (pathCosts[index].getCost() < pathCosts[par].getCost())
        {
            Node temp = pathCosts[index];
            pathCosts[index] = pathCosts[par];
            pathCosts[par] = temp;

            //set the informations properly
            pointers[pathCosts[index].getVertex()].self = &pathCosts[index];
            pointers[pathCosts[par].getVertex()].self = &pathCosts[par];
            pathCosts[index].setIndex(index);
            pathCosts[par].setIndex(par);

            //move up
            index = par;
            par = parent(par);
        }
        //break otherwise
        else break;
    }
}









/**************************************************************************************************************
 * Graph functions
 * ***********************************************************************************************************/

void Graph :: set(int v)
{
	V = v;
	graph = new vector<pair<int,int>>[v];
}

int Graph :: getVertex() { return V; }
void Graph :: setVertex(int v) { V = v; }

void Graph :: addEdge(int src, int dest, int weight)
{

	graph[src].push_back(make_pair(dest,weight));
}

void Graph :: removeEdgeWithWeight(int src, int dest, int weight)
{
	for (auto it = graph[src].begin(); it != graph[src].end(); ++it)
    {
    	if (it->first == dest && it->second == weight)
    	{
    		graph[src].erase(it);
    		return;
    	}
    }
}

void Graph :: removeEdge(int src, int dest)
{
	for (auto it = graph[src].begin(); it != graph[src].end(); ++it)
    {
    	if (it->first == dest)
    	{
    		graph[src].erase(it);
    		return;
    	}
    }
}

void Graph :: print(int numArgs, ...)
{
	int * dijkstraPaths = nullptr;
	vector<vector<int>> components;
	vector<EdgeType> edgeNames;
	unordered_map<int, int> edgeMap;
	string * tarjanNodeColors = nullptr;
	int level = -1;

	//get all the arguments
	va_list argsList;
	va_start(argsList, numArgs);
	const char * fileName = va_arg(argsList,const char *);
	int type = -1;
	if (numArgs > 1)
		type = va_arg(argsList,int);
	if (type == 1) //dijstra
		dijkstraPaths = va_arg(argsList,int *);
	else if (type == 2) //tarjan
		components = va_arg(argsList,vector<vector<int>>);
	else if (type == 4) //dfs
	{
		edgeNames = va_arg(argsList,vector<EdgeType>);
		for (EdgeType it : edgeNames)
		{
			int key = (prime1*it.getSrc())+(prime2*it.getDest());
			edgeMap.insert({key,it.getType()});
		}
	}

	string rankOrder = ""; //stores the printing order of vertices
	string graphStructure = ""; //stores the edges
	string nodeColors = ""; //stores the colors
	ofstream graphViz; //.gv file in output mode
	ofstream commands; //commands file in output mode

	string graphFileName = "";
	graphFileName.append(fileName);
	graphFileName.append(to_string(fileCount)); //along with a number that is file count
	graphFileName.append(".gv"); //adding extension name
	graphViz.open(graphFileName); //opening the file

	if (fileType == 0) //if os is windows
	{
		fileCount == 0 ? commands.open("commands.bat") : commands.open("commands.bat",std::ios_base::app); //open a batch file, first time in write mode and then in append mode
		commands << "dot -Tpng " << graphFileName << " -o "<< fileName << to_string(fileCount++) << ".png" << endl; //add the .gv to .png conversion command to batch file
	}
	else if (fileType == 1) //if os is linux
	{
		fileCount == 0 ? commands.open("commands.sh") : commands.open("commands.sh",std::ios_base::app); //open a shell script, first time in write mode and then in append mode
		commands << "dot -Tpng " << graphFileName << " -o "<< fileName << to_string(fileCount++) << ".png" << endl; //add the .gv to .png conversion command to shell script
	}

	commands.close(); //close the commands file

	if (type == 2) //for tarjan
	{
		tarjanNodeColors = new string[V];
		for (int i = 0; i < components.size(); i++)
		{
	        for (int j = 0; j < components[i].size(); j++)
	        {
	        	nodeColors.append(to_string(components[i][j]));
	        	nodeColors.append(" [color = \"");
	        	nodeColors.append(colors[i%noc]);
	        	nodeColors.append("\"];\n");
	        	tarjanNodeColors[components[i][j]] = colors[i%noc];
	        }
	    }
	}

	//perform bfs
	Queue queue;
	bool * visited = new bool[V];
	for (int i = 0; i < V; ++i)
		visited[i] = false;
	for (int i = 0; i < V; ++i) //for each vertex
	{
		if (!visited[i]) //enqueue if not yet visited
			queue.enqueue(i);

		while (!queue.isEmpty()) //till queue is not empty
		{
			int levelSize = queue.getSize(); //get the size of the queue
			++level;
			rankOrder.append("{rank = same; ");
			for (int i = 0; i < levelSize; ++i) //for all vertices at the current level
			{
				int vertex = queue.dequeue(); //dequeue
				if (!visited[vertex]) //if it is not yet visited
				{
					visited[vertex] = true; //mark as visited
					if (type == 1) //for dijkstra
						rankOrder.append("\"(");
					if (type == 4) //for dfs
						rankOrder.append("\"");
					rankOrder.append(to_string(vertex));
					if (type == 1) //for dijkstra
					{
						rankOrder.append(",");
						dijkstraPaths[vertex] == 1000000000 ?
							rankOrder.append("inf") :
							rankOrder.append(to_string(dijkstraPaths[vertex]));
						rankOrder.append(")\"");
					}
					if (type == 4) //for dfs
					{
						rankOrder.append("\n(");
						rankOrder.append(to_string(startTimes[vertex]));
						rankOrder.append(",");
						rankOrder.append(to_string(endTimes[vertex]));
						rankOrder.append(")\"");
					}
					rankOrder.append("; ");
					bool isLoop = false;
			        for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it)
			        {
			        	isLoop = true;
			        	if (type == 1) //for dijkstra
			        		graphStructure.append("\"(");
			        	if (type == 4) //for dfs
							graphStructure.append("\"");
			        	graphStructure.append(to_string(vertex));
			        	if (type == 1) //for dijkstra
			        	{
							graphStructure.append(",");
							dijkstraPaths[vertex] == 1000000000 ?
								graphStructure.append("inf") :
								graphStructure.append(to_string(dijkstraPaths[vertex]));
							graphStructure.append(")\"");
			        	}
						if (type == 4) //for dfs
						{
							graphStructure.append("\n(");
							graphStructure.append(to_string(startTimes[vertex]));
							graphStructure.append(",");
							graphStructure.append(to_string(endTimes[vertex]));
							graphStructure.append(")\"");
						}
			        	graphStructure.append("->");
			        	if (type == 1) //for dijkstra
			        		graphStructure.append("\"(");
			        	if (type == 4) //for dfs
							graphStructure.append("\"");
			        	graphStructure.append(to_string(it->first));
			        	if (type == 1) //for dijkstra
			        	{
							graphStructure.append(",");
							dijkstraPaths[it->first] == 1000000000 ?
								graphStructure.append("inf") :
								graphStructure.append(to_string(dijkstraPaths[it->first]));
							graphStructure.append(")\"");
			        	}
						if (type == 4) //for dfs
						{
							graphStructure.append("\n(");
							graphStructure.append(to_string(startTimes[it->first]));
							graphStructure.append(",");
							graphStructure.append(to_string(endTimes[it->first]));
							graphStructure.append(")\"");
						}
			        	graphStructure.append("[label=\"");
			        	graphStructure.append(to_string(it->second));
			        	graphStructure.append("\"");

			        	if (type == 1) //for dijkstra
			        	{
			        		if (dijkstraPaths[V+it->first] == vertex)
			        			graphStructure.append(" color = \"blue\"");
			        		else
			        			graphStructure.append(" color = \"red\" style = \"dashed\" ");
			        	}
			        	else if (type == 2) //for tarjan
			        	{
			        		if (tarjanNodeColors[vertex].compare(tarjanNodeColors[it->first]) == 0)
			        		{
			        			graphStructure.append(" color = \"");
			        			graphStructure.append(tarjanNodeColors[vertex]);
			        			graphStructure.append("\"");
			        		}
			        		else
			        			graphStructure.append(" color = \"grey\" style = \"dashed\"");
			        	}
			        	else if (type == 3) //for bfs
			        	{
			        		nodeColors.append(to_string(vertex));
				        	nodeColors.append(" [color = \"");
				        	nodeColors.append(colors[level%noc]);
				        	nodeColors.append("\"];\n");

			        		graphStructure.append(" color = \"");
			        		graphStructure.append(colors[level%noc]);
			        		graphStructure.append("\"");
			        	}
			        	else if (type == 4) //for dfs
			        	{
			        		int key = (prime1*vertex)+(prime2*it->first);
			        		if (edgeMap.at(key) == 0) graphStructure.append(" color = \"green\"");
			        		else if (edgeMap.at(key) == 1) graphStructure.append(" color = \"blue\" style = \"dashed\"");
			        		else if (edgeMap.at(key) == 2) graphStructure.append(" color = \"red\" style = \"dashed\"");
			        		else graphStructure.append(" color = \"orange\" style = \"dashed\"");
			        	}

			        	graphStructure.append("];\n");
			        	queue.enqueue(it->first);
			        }
			        if (!isLoop)
			        {
			        	if (type == 3) //for bfs
			        	{
			        		nodeColors.append(to_string(vertex));
				        	nodeColors.append(" [color = \"");
				        	nodeColors.append(colors[level%noc]);
				        	nodeColors.append("\"];\n");
			        	}
			        	else
			        	{
				        	if (type == 1) //for dijkstra
				        		graphStructure.append("\"(");
				        	if (type == 4) //for dfs
								graphStructure.append("\"");
				        	graphStructure.append(to_string(vertex));
				        	if (type == 1) //for dijkstra
				        	{
								graphStructure.append(",");
								dijkstraPaths[vertex] == 1000000000 ?
									graphStructure.append("inf") :
									graphStructure.append(to_string(dijkstraPaths[vertex]));
								graphStructure.append(")\"");
				        	}
							if (type == 4) //for dfs
							{
								graphStructure.append("\n(");
								graphStructure.append(to_string(startTimes[vertex]));
								graphStructure.append(",");
								graphStructure.append(to_string(endTimes[vertex]));
								graphStructure.append(")\"");
							}
				        	graphStructure.append("\n");
			        	}
			        }
				}
			}
			rankOrder.append("};\n");
		}
	}
	
	graphViz << "digraph G {" << endl;
	graphViz << "ranksep = \"equally\";" << endl;
	graphViz << "rankdir = LR;" << endl;
	graphViz << rankOrder;
	graphViz << nodeColors;
	graphViz << graphStructure;
	graphViz << "}" << endl;
	graphViz.close();
}

void Graph :: clear()
{
	delete(graph);
	graph = new vector<pair<int,int>>[10];
}

/*DFS*/

vector<EdgeType> Graph :: traverseDFS(int src, vector<EdgeType> edgeNames)
{
	added[src] = true; //mark src as visited
	startTimes[src] = timer++; //store start time
	dfsOrder[dfsOrderIndex++] = src; //store src in dfs order
	for (auto it = graph[src].begin(); it != graph[src].end(); ++it) //for all adjacent nodes
	{
		EdgeType et = EdgeType(src,it->first); //create an edge type
		if (!added[it->first]) //if adjacent node is not yert visited
		{
			et.setType(0); //TREE EDGE
			edgeNames.push_back(et); //add to result
			dfsParent[it->first] = src; //store parent
			dfsChild[src] = it->first; //store child
			edgeNames = traverseDFS(it->first,edgeNames); //recur
		}
		else //if already visited
		{
			if (endTimes[it->first] == 0) //if end time is not yet calculated
				et.setType(2); //BACK EDGE
			else if (startTimes[src] < startTimes[it->first]) //if start time of src is smaller
				et.setType(1); //FORWARDE EDGE
			else //otherwise
				et.setType(3); //CROSS EDGE
			edgeNames.push_back(et); //add to result
		}
	}
	endTimes[src] = timer++; //store end time
	return edgeNames;
}

vector<EdgeType> Graph :: runDFS(vector<EdgeType> edgeNames, int status)
{
	timer = 1; //reset the timer
	dfsOrderIndex = 0; //reset the index
	added = new bool[V];
	startTimes = new int[V];
	endTimes = new int[V];
	dfsOrder = new int[V];
	dfsParent = new int[V];
	dfsChild = new int[V];

	for (int i = 0; i < V; ++i)
	{
		dfsOrder[i] = -1;
		startTimes[i] = endTimes[i] = 0;
		added[i] = false;
		dfsParent[i] = dfsChild[i] = -1;
	}

	if (status == 0) //for graph
	{
		for (int i = 0; i < V; ++i) //for each vertex
			if (!added[i]) //if vertex is not visited
				edgeNames = traverseDFS(i,edgeNames); //call dfs
	}
	else if (status == 1) //for dag
	{
		for (int i = V-1; i >= 0; --i) //for each vertex in reverse order
			if (!added[i]) //if vertex is not visited
				edgeNames = traverseDFS(i,edgeNames); //call dfs
	}
	
	return edgeNames;
}

/*Strongly Connected Components*/

vector<vector<int>> Graph :: runDFSForTarjan(int i, vector<vector<int>> components)
{
	discovery[i] = timer++; //store the discovery time
	low[i] = discovery[i]; //store low
	added[i] = true; //mark as visited
	vStack.push(i); //push into stack

	for (auto it = graph[i].begin(); it != graph[i].end(); ++it) //for each adjacent vertex
	{
		if (discovery[it->first] == 0) //if its discovery is 0
		{
			components = runDFSForTarjan(it->first,components); //recur
			low[i] = low[i] <= low[it->first] ? low[i] : low[it->first]; //update low to the minimum of low of i and adjancent node
		}
		else if (added[it->first]) //if discovery is non zero and the node is already visited
			low[i] = low[i] <= discovery[it->first] ? low[i] : discovery[it->first]; //update low to the minimum of low of i and discovery of adjacent node
	}

	int popped = -1;
	vector<int> component;
	if (low[i] == discovery[i]) //if low and discovery are same
	{
		while (popped != i) //till i is popped
		{
			popped = vStack.pop(); //pop from stack
			component.push_back(popped); //add to current component
			added[popped] = false; //mark not visited
		}
		components.push_back(component); //add the current component to the result
	}
	return components;
}

vector<vector<int>> Graph :: runTarjan(vector<vector<int>> components)
{
	timer = 1; //reset the timer
	discovery = new int[V];
	low = new int[V];
	added = new bool[V];

	for (int i = 0; i < V; ++i)
		added[i] = false;

	for (int i = 0; i < V; ++i)
		discovery[i] = 0;

	for (int i = 0; i < V; ++i) //for each vertex
		if (discovery[i] == 0) //if discovery is 0
			components = runDFSForTarjan(i,components); //run dfs

	return components;
}

/*Build minimal graph*/

void Graph :: getEdgeMap(int type)
{
	if (type == 0) edgeMap.clear();
	else if (type == 1)	dagEdgeMap.clear();
	for (int i = 0; i < V; ++i)
	{
		for (auto it = graph[i].begin(); it != graph[i].end(); ++it)
		{
			int key = (prime1*i)+(prime2*it->first);
			if (type == 0)
			{
				if (edgeMap.find(key) == edgeMap.end()) edgeMap.insert({key,it->second});
				else
				{
					int prevWeight = edgeMap[key];
					if (it->second < prevWeight)
						edgeMap.insert({key,it->second});
				}
			}
			else if (type == 1)
			{
				if (dagEdgeMap.find(key) == dagEdgeMap.end()) dagEdgeMap.insert({key,it->second});
				else
				{
					int prevWeight = dagEdgeMap[key];
					if (it->second < prevWeight)
						dagEdgeMap.insert({key,it->second});
				}
			}
		}
	}
}

void Graph :: addEdgesWithinSCC(Graph graph, vector<vector<int>> components, vector<EdgeType> edgeNames)
{
	unordered_map<int,int> currComp; //stores the vertices of the current strongly connected component
	for (int i = 0; i < components.size(); ++i) //for each component
	{
		if (components[i].size() == 1) //if it's size is 1
			continue; //nothing to do
		if (components[i].size() == 2) //if it's size is 2, only one type of simple cycle is possible, so add it
		{
			//get the source and destination
			int src = components[i][0];
			int dest = components[i][1];
			int key1 = (prime1*src)+(prime2*dest), key2 = (prime1*dest)+(prime2*src); //find out the keys of two edges
			//add them to graph
			addEdge(src,dest,edgeMap.at(key1));
			addEdge(dest,src,edgeMap.at(key2));
			continue;
		}
		currComp.clear(); //clear the current component for all other cases
		//add all the vertices of the current component
		for (int j = 0; j < components[i].size(); ++j)
			currComp.insert({components[i][j],1});
		//add required edges of the current component
		unordered_map<int,int> crossEdges;
		unordered_map<int,pair<int,int>> treeEdges;
		vector<int> * backEdges = new vector<int>[V];
		for (int k = 0; k < edgeNames.size(); ++k) //for each edge
		{
			EdgeType temp = edgeNames[k]; //get the current edge
			int src = temp.getSrc(), dest = temp.getDest(); //get source and destination from the other map
			if (currComp.find(src) != currComp.end() && currComp.find(dest) != currComp.end()) //if both are present in current component
			{
				if (temp.getType() == 0) //for tree edge
				{
					int key = (prime1*src)+(prime2*dest); //get the key
					if (treeEdges.find(key) == treeEdges.end()) //if not already present
						treeEdges.insert({key,make_pair(src,dest)}); //add it to map
					/*int key = (prime1*src)+(prime2*dest); //get the key
					addEdge(src,dest,edgeMap.at(key)); //add edge*/
				}
				else if (temp.getType() == 3) //for cross edge
				{
					if (crossEdges.find(src) == crossEdges.end()) //if not already present
						crossEdges.insert({src,dest}); //add it to map
					else //if already present
					{
						int min = crossEdges.at(src); //get the destination vertex
						if (startTimes[dest] < startTimes[min] && endTimes[dest] > endTimes[min]) //if the new destination is above the old one in the tree
							crossEdges.insert({src,dest}); //update the destination
					}
				}
				else if (temp.getType() == 2) //for back edge
					backEdges[src].push_back(dest);
			}
		}

		//add tree edges from map to graph
		for (auto it = treeEdges.begin(); it != treeEdges.end(); ++it) //for each tree edge
		{
			int key = it->first; //get the key
			auto it2 = it->second;
			addEdge(it2.first,it2.second,edgeMap.at(key)); //add it
		}

		//add cross edges from map to graph
		for (auto it = crossEdges.begin(); it != crossEdges.end(); ++it) //for each cross edge
		{
			int key = (prime1*it->first)+(prime2*it->second); //get the key
			addEdge(it->first,it->second,edgeMap.at(key)); //add it
		}

		//add back edges from map to graph
		Queue backEdgesQueue, currQueue;
		int rootOfComponent = -1;
		for (int j = 0; j < components[i].size(); ++j) //for each vertex in current component
		{
			if (dfsChild[components[i][j]] == -1 || currComp.find(dfsChild[components[i][j]]) == currComp.end()) //if its child is null or not present in current component
				backEdgesQueue.enqueue(components[i][j]); //enqueue vertex
			if (dfsParent[components[i][j]] == -1 || currComp.find(dfsParent[components[i][j]]) == currComp.end()) //if its parent is null or not present in the current component
				rootOfComponent = components[i][j]; //mark root
		}

		bool * backEdgeAdded = new bool[V];
		bool * reachable = new bool[V];
		vector<EdgeType> backEdgeReachability;
		for (int k = 0; k < V; ++k)
			backEdgeAdded[k] = reachable[k] = false;
		while (!backEdgesQueue.isEmpty()) //till the queue is having more elements
		{
			currQueue.enqueue(backEdgesQueue.dequeue()); //dequeue the current source and add it to current queue
			for (int k = 0; k < V; ++k)
				reachable[k] = false;
			while (!currQueue.isEmpty())
			{
				int currSrc = currQueue.dequeue(); //dequeue the current source from current queue
				if (backEdges[currSrc].size() != 0) //if current source has back edges
				{
					for (int pp = 0; pp < backEdges[currSrc].size(); ++pp) //for each back edge starting from current source
					{
						int currDest = backEdges[currSrc][pp]; //get the current destination
						int key = (prime1*currSrc)+(prime2*currDest); //get the key
						if ((!reachable[currDest] || !reachable[currSrc]) && currSrc != currDest) //if the current source or destination are not reachable and the current source doesn't have a cross edge
						{
							if (crossEdges.find(currSrc) != crossEdges.end()) //if it has a cross edge
							{
								int currentNode = currSrc;
								int parentNode = dfsParent[currentNode];
								if (abs(startTimes[parentNode]-startTimes[currSrc]) == abs(endTimes[parentNode]-endTimes[currSrc]) || currDest != parentNode)
								{
									bool isWithinSubtree = false;
									while (abs(startTimes[parentNode]-startTimes[currSrc]) == abs(endTimes[parentNode]-endTimes[currSrc]))
									{
										currentNode = parentNode;
										parentNode = dfsParent[currentNode];
										if (parentNode == currDest)
										{
											isWithinSubtree = true;
											break;
										}
									}
									if (!isWithinSubtree) // || dfsParent[currSrc] != currDest
									{
										addEdge(currSrc,currDest,edgeMap.at(key)); //add the edge to the graph if it doesn't have a cross edge
										//mark all nodes on the path as reachable
										reachable[currSrc] = reachable[currDest] = true;
										int pathSize = 2;
										int parentNode = dfsParent[currSrc];
										while (parentNode != currDest)
										{
											++pathSize;
											reachable[parentNode] = true;
											parentNode = dfsParent[parentNode];
										}
										int * subsetStatus = isSubset(backEdgeReachability,currSrc,currDest,pathSize); //check if one is subset of another, keep the super set
										if (subsetStatus[0] == 0) //if nothing to ignore
										{
											EdgeType et = EdgeType(currSrc,currDest);
											et.setType(pathSize);
											backEdgeReachability.push_back(et); //add to reachability
										}
										else if (subsetStatus[0] == 1) //if current backedge is to be ignored
											removeEdge(currSrc,currDest);
										else if (subsetStatus[0] == -1) //f previous back edge is to be ignored
										{
											removeEdge(subsetStatus[1],subsetStatus[2]);
											EdgeType et = EdgeType(currSrc,currDest);
											et.setType(pathSize);
											backEdgeReachability.push_back(et); //add to reachability
										}
									}
								}
							}
							else if (currSrc != currDest)
							{
								addEdge(currSrc,currDest,edgeMap.at(key)); //add the edge to the graph if it doesn't have a cross edge
								//mark all nodes on the path as reachable
								reachable[currSrc] = reachable[currDest] = true;
								int pathSize = 2;
								int parentNode = dfsParent[currSrc];
								while (parentNode != currDest)
								{
									++pathSize;
									reachable[parentNode] = true;
									parentNode = dfsParent[parentNode];
								}
								int * subsetStatus = isSubset(backEdgeReachability,currSrc,currDest,pathSize); //check if one is subset of another, keep the super set
								if (subsetStatus[0] == 0) //if nothing to ignore
								{
									EdgeType et = EdgeType(currSrc,currDest);
									et.setType(pathSize);
									backEdgeReachability.push_back(et); //add to reachability
								}
								else if (subsetStatus[0] == 1) //if current backedge is to be ignored
									removeEdge(currSrc,currDest);
								else if (subsetStatus[0] == -1) //f previous back edge is to be ignored
								{
									removeEdge(subsetStatus[1],subsetStatus[2]);
									EdgeType et = EdgeType(currSrc,currDest);
									et.setType(pathSize);
									backEdgeReachability.push_back(et); //add to reachability
								}
							}
						}
						if (currDest != rootOfComponent && currComp.find(currDest) != currComp.end()) currQueue.enqueue(currDest); //enqueue the current destination, if it is not the root of DFS tree (because it will be a source in the next iteration)
					}
					backEdges[currSrc].clear();
				}
				if (dfsParent[currSrc] != -1 && currComp.find(dfsParent[currSrc]) != currComp.end() && !backEdgeAdded[dfsParent[currSrc]])
					currQueue.enqueue(dfsParent[currSrc]);
				backEdgeAdded[currSrc] = true; //mark the backedges starting from current source as added
			}
		}
	}
}

int * Graph :: isSubset(vector<EdgeType> reach, int src, int dest, int pathSize)
{
	int * result = new int[3];
	result[0] = result[1] = result[2] = 0;
	for (EdgeType it : reach)
	{
		unordered_map<int,bool> longerPath;
		if (pathSize == it.getType()) //if both the path sizes are same
		{
			if (src == it.getSrc() && dest == it.getDest()) //if source and destinations are same
			{
				result[0] = 1; //1 indicates to ignore the current backedge
				result[1] = it.getSrc();
				result[2] = it.getDest();
				break;
			}
		}
		else if (pathSize > it.getType()) //if current back edge has larger reachability
		{
			//push all nodes on path to map
			int currNode = src;
			while (currNode != dest)
			{
				longerPath.insert({currNode,true});
				currNode = dfsParent[currNode];
			}
			longerPath.insert({currNode,true});
			if (longerPath.find(it.getSrc()) != longerPath.end() && longerPath.find(it.getDest()) != longerPath.end()) //if both the source and destination of the already added back edge are present in map
			{
				result[0] = -1; //-1 indicates to ignore the previous backedge
				result[1] = it.getSrc();
				result[2] = it.getDest();
				break;
			}
		}
		else
		{
			//push all nodes on path to map
			int currNode = it.getSrc();
			while (currNode != it.getDest())
			{
				longerPath.insert({currNode,true});
				currNode = dfsParent[currNode];
			}
			longerPath.insert({currNode,true});
			if (longerPath.find(src) != longerPath.end() && longerPath.find(dest) != longerPath.end()) //if both the source and destination of the current back edge are present in map
			{
				result[0] = 1; //1 indicates to ignore the current backedge
				result[1] = it.getSrc();
				result[2] = it.getDest();
				break;
			}
		}
	}
	return result; //0 indicates not to ignore any of them
}

void Graph :: addEdgesInterSCC(Graph graph, Graph dag, vector<vector<int>> components, vector<EdgeType> edgeNames)
{	
	dag.getEdgeMap(1);
	//hash the components for each vertex
	int * componentMap = new int[graph.getVertex()];
	for (int i = 0; i < components.size(); ++i)
		for (int j = 0; j < components[i].size(); ++j)
			componentMap[components[i][j]] = i;

	int src = -1, dest = -1, weight = -1;
	for (int i = 0; i < graph.getVertex(); ++i) //for each vertex
	{
		for (auto it = graph.graph[i].begin(); it != graph.graph[i].end(); ++it) //for each adjacent node of the vertex
		{
			//get data
			src = i;
			dest = it->first;
			weight = it->second;
			if (componentMap[src] != componentMap[dest]) //if source and destination don't belong to the same component
			{
				int key = (prime1*componentMap[src])+(prime2*componentMap[dest]); //get the key at dag edge map
				if (dagEdgeMap.find(key) != dagEdgeMap.end()) //if the key is present, means edge is present
				{
					addEdge(src,dest,dagEdgeMap.at(key)); //add the edge to minimal graph only if it is present in the dag edge map
					dagEdgeMap.erase(key); //remove the edge from dag edge map
				}
			}
		}
	}
}

bool Graph :: removeExtraEdges(vector<EdgeType> edgeNames)
{
	bool isRemoved = false;
	unordered_map<int,int> crossEdges;
	vector<EdgeType> reach;
	//removing forward edges
	for (auto it = edgeNames.begin(); it != edgeNames.end(); ++it)
	{
		int src = it->getSrc();
		int dest = it->getDest();
		//removing forward edges
		if (it->getType() == 1)
		{
			isRemoved = true;
			int key = (prime1*src)+(prime2*dest);
			removeEdgeWithWeight(src,dest,edgeMap.at(key));
		}
		//removing cross edges
		else if (it->getType() == 3) //for cross edge
		{
			if (crossEdges.find(src) == crossEdges.end()) //if not already present
				crossEdges.insert({src,dest}); //add it to map
			else //if already present
			{
				int min = crossEdges.at(src); //get the destination vertex
				if (startTimes[dest] < startTimes[min] && endTimes[dest] > endTimes[min]) //if the new destination is above the old one in the tree
				{
					isRemoved = true;
					removeEdge(src,min); //remove the previous cross edge
					crossEdges.insert({src,dest}); //update the destination
				}
			}
		}
		//removing back edges
		else if (it->getType() == 2) //for back edge
		{
			int pathSize = 2;
			int parentNode = dfsParent[src];
			while (parentNode != dest)
			{
				++pathSize;
				parentNode = dfsParent[parentNode];
			}
			int * subsetStatus = isSubset(reach,src,dest,pathSize); //check if one is subset of another, keep the super set
			if (subsetStatus[0] == 0) //if nothing to ignore
			{
				EdgeType et = EdgeType(src,dest);
				et.setType(pathSize);
				reach.push_back(et); //add to reachability
			}
			else if (subsetStatus[0] == 1) //if current backedge is to be ignored
			{
				isRemoved = true;
				removeEdge(src,dest);
			}
			else if (subsetStatus[0] == -1) //f previous back edge is to be ignored
			{
				isRemoved = true;
				removeEdge(subsetStatus[1],subsetStatus[2]);
				EdgeType et = EdgeType(src,dest);
				et.setType(pathSize);
				reach.push_back(et); //add to reachability
			}
		}
	}
	return isRemoved;
}

/*Check for semiconnected*/

void Graph :: buildDAG(vector<vector<int>> components, Graph g)
{
	//hash component numbers for each vertex
	set(components.size());
	int * componentMap = new int[g.getVertex()];
	for (int i = 0; i < components.size(); ++i)
		for (int j = 0; j < components[i].size(); ++j)
			componentMap[components[i][j]] = i;

	int src = -1, dest = -1, weight = -1;
	vector<pair<int, int>> * adj = g.graph;
	for (int i = 0; i < g.getVertex(); ++i) //for each vertex
	{
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it) //for each adjacent node of the vertex
		{
			//get data
			src = i;
			dest = it->first;
			weight = it->second;
			if (componentMap[src] != componentMap[dest]) //if source and destination don't belong to the same component
				addEdge(componentMap[src],componentMap[dest],weight); //add edge to dag
		}
	}
}

int * Graph :: runTopologicalSort()
{
	Queue queue;
	int * hash = new int[V];
	int * result = new int[V];
	int index = 0;

	for (int i = 0; i < V; ++i)
		hash[i] = 0;

	//count the indegree of each vertex
	for (int i = 0; i < V; ++i)
		for (auto it = graph[i].begin(); it != graph[i].end(); ++it)
			++hash[it->first];

	//add all nodes with indegree 0 to the queue
	for (int i = 0; i < V; ++i)
		if (hash[i] == 0)
			queue.enqueue(i);
	
	//till queue is non empty
	while (!queue.isEmpty())
	{
		result[index] = queue.dequeue(); //dequeue
		for (auto it = graph[result[index]].begin(); it != graph[result[index]].end(); ++it) //for each adjacent node
		{
			--hash[it->first]; //decrease indegree
			if (hash[it->first] == 0) //if count becomes 0
				queue.enqueue(it->first); //enqueue
		}
		++index;
	}

	//store the sequence to output file
	for (int i = 0; i < V; ++i)
		outputFile << result[i] << " ";
	outputFile << endl;

	return result;
}

bool Graph :: checkSemiConnected(int * result)
{
	bool isNextNodeConnected = false;
	for (int i = 1; i < V; ++i)
	{
		isNextNodeConnected = false;
		for (auto it = graph[result[i-1]].begin(); it != graph[result[i-1]].end(); ++it)
			if (it->first == result[i])
				isNextNodeConnected = true;
		if (!isNextNodeConnected) return false;
	}

	return true;
}

/*Dijsktra's Algorithm*/

int * Graph :: relaxEdge(Heap heap, int * costs, int src, int dest, int weight)
{
	//update the path cost
	if (costs[dest] > costs[src]+weight)
	{
		costs[dest] = costs[src]+weight;
		costs[dest+V] = src;
		heap.decreaseKey(dest, costs[dest]);
	}
	return costs;
}

int * Graph :: runDijkstra(int src)
{
	int * costs = new int[V*2];
	Heap heap;
	heap.buildHeap(V,src);

	//store 0 in source and maximum value in others
	for (int i = 0; i < V; ++i)
	{
		if (i != src)
			costs[i] = 1000000000;
		else
			costs[i] = 0;
	}

	//set parents to -1
	for (int i = V; i < V*2; ++i)
		costs[i] = -1;

	for (int count = 1; count < V; ++count)
	{
		//extract minimum from the unchecked vertices and mark it checked
		Node minVertex = heap.extractRoot();

		//relax all the adjacent edges
		for (auto it = graph[minVertex.getVertex()].begin(); it != graph[minVertex.getVertex()].end(); ++it)
			costs = relaxEdge(heap,costs,minVertex.getVertex(),it->first,it->second);
	}

	return costs;
}






/*
void Graph :: addEdgesWithinSCC(Graph graph, vector<vector<int>> components, vector<EdgeType> edgeNames)
{
	unordered_map<int,int> currComp; //stores the vertices of the current strongly connected component
	for (int i = 0; i < components.size(); ++i) //for each component
	{
		if (components[i].size() == 1) //if it's size is 1
			continue; //nothing to do
		if (components[i].size() == 2) //if it's size is 2, only one type of simple cycle is possible, so add it
		{
			//get the source and destination
			int src = components[i][0];
			int dest = components[i][1];
			int key1 = (prime1*src)+(prime2*dest), key2 = (prime1*dest)+(prime2*src); //find out the keys of two edges
			//add them to graph
			addEdge(src,dest,edgeMap.at(key1));
			addEdge(dest,src,edgeMap.at(key2));
			continue;
		}
		currComp.clear(); //clear the current component for all other cases
		//add all the vertices of the current component
		for (int j = 0; j < components[i].size(); ++j)
			currComp.insert({components[i][j],1});
		//add required edges of the current component
		unordered_map<int,int> crossEdges;
		vector<int> * backEdges = new vector<int>[V];
		for (int k = 0; k < edgeNames.size(); ++k) //for each edge
		{
			EdgeType temp = edgeNames[k]; //get the current edge
			int src = temp.getSrc(), dest = temp.getDest(); //get source and destination from the other map
			if (currComp.find(src) != currComp.end() && currComp.find(dest) != currComp.end()) //if both are present in current component
			{
				if (temp.getType() == 0) //for tree edge
				{
					int key = (prime1*src)+(prime2*dest); //get the key
					addEdge(src,dest,edgeMap.at(key)); //add edge
				}
				else if (temp.getType() == 3) //for cross edge
				{
					if (crossEdges.find(src) == crossEdges.end()) //if not already present
						crossEdges.insert({src,dest}); //add it to map
					else //if already present
					{
						int min = crossEdges.at(src); //get the destination vertex
						if (startTimes[dest] < startTimes[min] && endTimes[dest] > endTimes[min]) //if the new destination is above the old one in the tree
							crossEdges.insert({src,dest}); //update the destination
					}
				}
				else if (temp.getType() == 2) //for back edge
					backEdges[src].push_back(dest);
			}
		}

		//add cross edges from map to graph
		bool * refReachable = new bool[V];
		for (int k = 0; k < V; ++k)
			refReachable[k] = false;
		for (auto it = crossEdges.begin(); it != crossEdges.end(); ++it) //for each cross edge
		{
			int key = (prime1*it->first)+(prime2*it->second); //get the key
			addEdge(it->first,it->second,edgeMap.at(key)); //add it
			int currentNode = it->first; refReachable[currentNode] = true;
			int parentNode = dfsParent[currentNode]; refReachable[parentNode] = true;
			while (abs(startTimes[parentNode]-startTimes[currentNode]) == abs(endTimes[parentNode]-endTimes[currentNode]))
			{
				currentNode = parentNode;
				parentNode = dfsParent[currentNode];
				refReachable[parentNode] = true;
			}
		}

		//add back edges from map to graph
		Queue backEdgesQueue, currQueue;
		int rootOfComponent = -1;
		for (int j = 0; j < components[i].size(); ++j) //for each vertex in current component
		{
			if (dfsChild[components[i][j]] == -1 || currComp.find(dfsChild[components[i][j]]) == currComp.end()) //if its child is null or not present in current component
				backEdgesQueue.enqueue(components[i][j]); //enqueue vertex
			if (dfsParent[components[i][j]] == -1 || currComp.find(dfsParent[components[i][j]]) == currComp.end()) //if its parent is null or not present in the current component
				rootOfComponent = components[i][j]; //mark root
		}

		bool * backEdgeAdded = new bool[V];
		bool * reachable = new bool[V];
		for (int k = 0; k < V; ++k)
		{
			backEdgeAdded[k] = false;
			reachable[k] = refReachable[k];
		}
		while (!backEdgesQueue.isEmpty()) //till the queue is having more elements
		{
			currQueue.enqueue(backEdgesQueue.dequeue()); //dequeue the current source and add it to current queue
			for (int k = 0; k < V; ++k)
				reachable[k] = refReachable[k];
			while (!currQueue.isEmpty())
			{
				int currSrc = currQueue.dequeue(); //dequeue the current source from current queue
				if (backEdges[currSrc].size() != 0) //if current source has back edges
				{
					for (int pp = 0; pp < backEdges[currSrc].size(); ++pp) //for each back edge starting from current source
					{
						int currDest = backEdges[currSrc][pp]; //get the current destination
						int key = (prime1*currSrc)+(prime2*currDest); //get the key
						if ((!reachable[currDest] || !reachable[currSrc]) && currSrc != currDest) //if the current source or destination are not reachable and the current source doesn't have a cross edge
						{
							if (crossEdges.find(currSrc) != crossEdges.end()) //if it has a cross edge
							{
								int currentNode = currSrc;
								int parentNode = dfsParent[currentNode];
								if (abs(startTimes[parentNode]-startTimes[currSrc]) == abs(endTimes[parentNode]-endTimes[currSrc]) || currDest != parentNode)
								{
									bool isWithinSubtree = false;
									while (abs(startTimes[parentNode]-startTimes[currSrc]) == abs(endTimes[parentNode]-endTimes[currSrc]))
									{
										currentNode = parentNode;
										parentNode = dfsParent[currentNode];
										if (parentNode == currDest)
										{
											isWithinSubtree = true;
											break;
										}
									}
									if (!isWithinSubtree) addEdge(currSrc,currDest,edgeMap.at(key)); //add the edge to the graph if it goes beyond the current subtree
								}
							}
							else if (currSrc != currDest)
								addEdge(currSrc,currDest,edgeMap.at(key)); //add the edge to the graph if it doesn't have a cross edge
						}
						//mark all nodes on the path as reachable
						reachable[currSrc] = reachable[currDest] = true;
						if (currSrc != currDest)
						{
							int parentNode = dfsParent[currSrc];
							while (parentNode != currDest)
							{
								reachable[parentNode] = true;
								parentNode = dfsParent[parentNode];
							}
						}
						if (currDest != rootOfComponent && currComp.find(currDest) != currComp.end()) currQueue.enqueue(currDest); //enqueue the current destination, if it is not the root of DFS tree (because it will be a source in the next iteration)
					}
					backEdges[currSrc].clear();
				}
				else //if current source is not having a back edge
				{
					for (int k = 0; k < V; ++k) //for each vertex
						if (dfsParent[k] == currSrc && currComp.find(k) != currComp.end() && !backEdgeAdded[k]) //if current source is a parent of kth vertex and kth vertex is inside the current component and the backedge starting from that vertex is not already checked
							currQueue.enqueue(k); //enqueue k
				}
				backEdgeAdded[currSrc] = true; //mark the backedges starting from current source as added
			}
		}
	}
}


if (crossEdges.find(currSrc) != crossEdges.end()) //if it has a cross edge
							{
								int currentNode = currSrc;
								int parentNode = dfsParent[currentNode];
								if (abs(startTimes[parentNode]-startTimes[currSrc]) == abs(endTimes[parentNode]-endTimes[currSrc]) || currDest != parentNode)
								{
									bool isWithinSubtree = false;
									while (abs(startTimes[parentNode]-startTimes[currSrc]) == abs(endTimes[parentNode]-endTimes[currSrc]))
									{
										currentNode = parentNode;
										parentNode = dfsParent[currentNode];
										if (parentNode == currDest)
										{
											isWithinSubtree = true;
											break;
										}
									}
									if (!isWithinSubtree)
									{
										addEdge(currSrc,currDest,edgeMap.at(key)); //add the edge to the graph if it doesn't have a cross edge
										//mark all nodes on the path as reachable
										reachable[currSrc] = reachable[currDest] = true;
										int pathSize = 2;
										int parentNode = dfsParent[currSrc];
										while (parentNode != currDest)
										{
											++pathSize;
											reachable[parentNode] = true;
											parentNode = dfsParent[parentNode];
										}
										int * subsetStatus = isSubset(backEdgeReachability,currSrc,currDest,pathSize); //check if one is subset of another, keep the super set
										if (subsetStatus[0] == 0) //if nothing to ignore
										{
											EdgeType et = EdgeType(currSrc,currDest);
											et.setType(pathSize);
											backEdgeReachability.push_back(et); //add to reachability
										}
										else if (subsetStatus[0] == 1) //if current backedge is to be ignored
											removeEdge(currSrc,currDest);
										else if (subsetStatus[0] == -1) //f previous back edge is to be ignored
										{
											removeEdge(subsetStatus[1],subsetStatus[2]);
											EdgeType et = EdgeType(currSrc,currDest);
											et.setType(pathSize);
											backEdgeReachability.push_back(et); //add to reachability
										}
									}
								}
							}
							else if (currSrc != currDest)
							{
								addEdge(currSrc,currDest,edgeMap.at(key)); //add the edge to the graph if it doesn't have a cross edge
								//mark all nodes on the path as reachable
								reachable[currSrc] = reachable[currDest] = true;
								int pathSize = 2;
								int parentNode = dfsParent[currSrc];
								while (parentNode != currDest)
								{
									++pathSize;
									reachable[parentNode] = true;
									parentNode = dfsParent[parentNode];
								}
								int * subsetStatus = isSubset(backEdgeReachability,currSrc,currDest,pathSize); //check if one is subset of another, keep the super set
								if (subsetStatus[0] == 0) //if nothing to ignore
								{
									EdgeType et = EdgeType(currSrc,currDest);
									et.setType(pathSize);
									backEdgeReachability.push_back(et); //add to reachability
								}
								else if (subsetStatus[0] == 1) //if current backedge is to be ignored
									removeEdge(currSrc,currDest);
								else if (subsetStatus[0] == -1) //f previous back edge is to be ignored
								{
									removeEdge(subsetStatus[1],subsetStatus[2]);
									EdgeType et = EdgeType(currSrc,currDest);
									et.setType(pathSize);
									backEdgeReachability.push_back(et); //add to reachability
								}
							}





	//minimize the cross and forward edges of dag
	vector<pair<int,int>> * dagEdges = new vector<pair<int,int>>[dag.getVertex()];

	//add required edges of the current component
	unordered_map<int,int> crossEdges;
	for (int k = 0; k < edgeNames.size(); ++k) //for each edge
	{
		EdgeType temp = edgeNames[k]; //get the current edge
		int src = temp.getSrc(), dest = temp.getDest(); //get source and destination from the other map
		if (temp.getType() == 0) //for tree edge
		{
			int key = (prime1*src)+(prime2*dest); //get the key
			dagEdges[src].push_back(make_pair(dest,dagEdgeMap.at(key)));
		}
		else if (temp.getType() == 3) //for cross edge
		{
			if (crossEdges.find(src) == crossEdges.end()) //if not already present
				crossEdges.insert({src,dest}); //add it to map
			else //if already present
			{
				int min = crossEdges.at(src); //get the destination vertex
				if (startTimes[dest] < startTimes[min] && endTimes[dest] > endTimes[min]) //if the new destination is above the old one in the tree
					crossEdges.insert({src,dest}); //update the destination
			}
		}
	}

	//add cross edges from map to graph
	for (auto it = crossEdges.begin(); it != crossEdges.end(); ++it) //for each cross edge
	{
		int key = (prime1*it->first)+(prime2*it->second); //get the key
		dagEdges[it->first].push_back(make_pair(it->second,dagEdgeMap.at(key)));
	}

	dagEdgeMap.clear();
	for (int i = 0; i < dag.getVertex(); ++i)
	{
		for (auto it = dagEdges[i].begin(); it != dagEdges[i].end(); ++it)
		{
			int key = (prime1*i)+(prime2*it->first);
			if (dagEdgeMap.find(key) == dagEdgeMap.end()) dagEdgeMap.insert({key,it->second});
			else
			{
				int prevWeight = dagEdgeMap[key];
				if (it->second < prevWeight)
					dagEdgeMap.insert({key,it->second});
			}
		}
	}


	addEdge(currSrc,currDest,edgeMap.at(key)); //add the edge to the graph if it doesn't have a cross edge
								//mark all nodes on the path as reachable
								reachable[currSrc] = reachable[currDest] = true;
								int pathSize = 2;
								int parentNode = dfsParent[currSrc];
								while (parentNode != currDest)
								{
									++pathSize;
									reachable[parentNode] = true;
									parentNode = dfsParent[parentNode];
								}
								int * subsetStatus = isSubset(backEdgeReachability,currSrc,currDest,pathSize); //check if one is subset of another, keep the super set
								if (subsetStatus[0] == 0) //if nothing to ignore
								{
									EdgeType et = EdgeType(currSrc,currDest);
									et.setType(pathSize);
									backEdgeReachability.push_back(et); //add to reachability
								}
								else if (subsetStatus[0] == 1) //if current backedge is to be ignored
									removeEdge(currSrc,currDest);
								else if (subsetStatus[0] == -1) //f previous back edge is to be ignored
								{
									removeEdge(subsetStatus[1],subsetStatus[2]);
									EdgeType et = EdgeType(currSrc,currDest);
									et.setType(pathSize);
									backEdgeReachability.push_back(et); //add to reachability
								}

*/