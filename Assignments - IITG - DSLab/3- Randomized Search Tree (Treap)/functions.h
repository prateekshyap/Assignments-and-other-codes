/*fileCount stores a number so that multiple files could be created easily
fileType stores a number to indicate the type of file to be generated based on OS type*/
int fileCount = -1, fileType = -1;
string color = "black"; //stores the color
int * elements, * window = new int[5]; //elements
int full = 0, iter = 0, ratio = -1, nop = 0; //to store the elements
Stack stack; //used for deletion
int low, high; //range of the values
int insertKeyComparisons = 0, deleteKeyComparisons = 0; //total key comparisons
int insertRotateCount = 0, deleteRotateCount = 0; //total number of rotations
int insertCount = 0, deleteCount = 0; //total number of insertions and deletions
int tempCount = 0, maxHeight = -1;
long nodeCount = 0, totalHeight = 0, totalDepth = 0;
unordered_map<int,bool> hashTable;


/**************************************************************************************************************
 * Utility functions
 * ***********************************************************************************************************/

void printMessage(string outputFileName)
{
	/*The initial message printed just after starting the execution*/
	cout << endl << endl << "-----------------------------------------" << endl;
	cout << "           TREAP OPERATIONS" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "1- Insert" << endl;
	cout << "2- Delete" << endl;
	cout << "3- Search" << endl;
	cout << "4- Print tree" << endl;
	cout << "5- Quit" << endl;
	cout << endl << "-----------------------------------------" << endl;
	cout << "              INPUT FORMAT" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "insert 5" << endl << "insert 14" << endl << "insert 20" << endl << "delete 14" << endl << "print" << endl << "quit" << endl;
	cout << endl << "-----------------------------------------" << endl;
	cout << "              INSTRUCTIONS" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "1. Write a .txt file in mentioned format\nand enter the file name below" << endl;
	cout << "2. You can write any number of operations\nyou want" << endl;
	cout << "3. You can check execution details\nin \""<< outputFileName <<"\"" << endl;
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

void runEvaluationFile(int os)
{
	/*if os is windows run the batch file*/
	if (os == 0)
		std :: system("evaluate.bat");
	/*if os is linux change the permission and run the shell script*/
	else if (os == 1)
	{
		std :: system("chmod +x evaluate.sh");
		std :: system("./evaluate.sh");
	}
}

void generateInput(int x, string fileName, int quitStatus, bool printStatus, int beginStatus)
{
	cout << endl << "Generating input file" << endl;
	//open output file stream and files
	ofstream file;
	file.open(fileName);
	bool flag = true; //keep a flag to indicate where print command should be used
	srand(time(0));
	/*i is loop variable
	value stores the random value generated
	operation indicates which operation to be performed
	index stores the index of the element to be deleted*/
	int i = 0, j = 0, value = 0, operation = -1, index = 0, windowIndex = 0, count = 0, percentageBreak = 0;
	nop = x;
	percentageBreak = x/100;
	if (beginStatus == 0) //for the first time initialize and perform 10% insertions
	{
		elements = new int[200000]; //initialize elements
		//store random numbers in the array
		for (j = 0; j < 200000; ++j)
			elements[j] = rand()%10000000;
		//generate a random number for insert : delete ratio
		if (ratio == 0) ratio = 55+(rand()%31);
		/*some operations will be pure insertions initially, either 10% of the total operations or 50 operations, whichever is smaller*/
		int initialInsertions = x*0.1;
		if (initialInsertions > 20)
			initialInsertions = 20;
		while (i < initialInsertions) //for all the initial iterations
		{
			/*Progress bar implementation*/
			if (percentageBreak >= 10) //if more than 10 operations fall under 1% of execution
			{
				++count; //increment count
				if (count%percentageBreak == 0) //when reminder is 0
				{
					cout << "\r"; //move to the beginning of the line
					/*print the progress*/
					j = 0;
					for (j = percentageBreak; j <= count; j += percentageBreak)
						cout << "|";
					for (; j <= x; j += percentageBreak)
						cout << " ";
					cout << "|" << (count/percentageBreak); //print the percentage
				}
			}
			value = (low)+(rand()%(high-low+1)); //generate a value
			if (hashTable.find(value) == hashTable.end()) //if the value is not present in hashTable
			{
				hashTable[value] = true; //add the value to hashTable
				elements[iter] = value; //store it in elements
				if (iter == 99999) full = 1; //if array is full, indicate it
				iter = (iter+1)%100000; //increment iter in circular manner
			}
			file << "insert " << value << endl; //write command
			window[windowIndex] = 0; //indicate print or not
			windowIndex = (windowIndex+1)%5;
			++insertCount; ++i; //increment loop variable
		}
		if (printStatus)
		{
			file << "print" << endl; //print once after all the initial insertions
			window[windowIndex] = 1; //indicate print or not
		}
		else
			window[windowIndex] = 0;
		windowIndex = (windowIndex+1)%5;
	}
	
	//if (quitStatus == 0) --x; //if quit is also an operation, decrement x
	flag = false; //set flag to false

	while (i < x) //for rest of the operations
	{
		/*Progress bar implementation*/
		if (percentageBreak >= 10) //if more than 10 operations fall under 1% of execution
		{
			++count; //increment count
			if (count%percentageBreak == 0) //when reminder is 0
			{
				cout << "\r"; //move to the beginning of the line
				/*print the progress*/
				j = 0;
				cout << "[";
				for (j = percentageBreak; j <= count; j += percentageBreak)
					cout << "|";
				for (; j <= x; j += percentageBreak)
					cout << " ";
				cout << "]" << (count/percentageBreak); //print the percentage
			}
		}
		operation = (rand()%100)+1; //generate a random operation number
		if (operation <= ratio) //from 0 to ratio, insertions
		{
			value = (low)+(((rand()*rand()*2)-1)%(high-low+1)); //generate a value
			flag = true; //set flag to true, indicating that insertion sequence has started
			if (hashTable.find(value) == hashTable.end()) //if the value is not present in the hashTable
			{
				hashTable[value] = true; //add the value to hashTable
				elements[iter] = value; //store the element in the elements pile
				if (iter == 99999) full = 1; //if array is full, indicate it
				iter = (iter+1)%100000; //increment iter in circular manner
			}
			file << "insert " << value << endl; //write command
			window[windowIndex] = 0; //indicate print or not
			windowIndex = (windowIndex+1)%5;
			++insertCount;
		}
		else //from ratio+1 to 100, deletions
		{
			if (flag) //if flag is true, it means for a few previous commands, no printing has been done
			{
				flag = false; //set flag to false
				//check if the last five instructions contain print command or not
				bool check = true;
				for (int c = 0; c < 5; ++c)
				{
					if (window[c] == 1)
						check = false;
				}
				if (check) //if the last five instructions do not contain print
				{
					if (printStatus)
					{
						file << "print" << endl; //add print command
						window[windowIndex] = 1; //indicate print or not
					}
					else
						window[windowIndex] = 0;
					windowIndex = (windowIndex+1)%5;
				}
			}
			index = full == 0 ? rand()%(int(iter*1.25)) : rand()%(int(100000*1.25)); //generate a random index, 25% extra to have a mix of present and absent elements
			if (hashTable.find(elements[index]) != hashTable.end()) //remove the value from hashTable, if present
				hashTable.erase(elements[index]);
			file << "delete " << elements[index] << endl; //delete the element present at the generated index of elements pile
			window[windowIndex] = 0; //indicate print or not
			windowIndex = (windowIndex+1)%5;
			++deleteCount;
		}
		++i; //increment loop variable
	}
	if (quitStatus == 0)
	{
		file << "print" << endl << "quit" << endl; //add quit command at the iter
	}
	file.close();
}

void writeFileSequence(string fileSequence, string inputFileName, int beginStatus, int x)
{
	ofstream file;
	beginStatus == 0 ? file.open(fileSequence) : file.open(fileSequence,std::ios_base::app);
	file << inputFileName << endl << x << endl;
	file.close();
}

/**************************************************************************************************************
 * Functions for Stack
 * ***********************************************************************************************************/
void Stack :: push(TreapNode * node)
{
	StackNode * newNode = new StackNode(node); //create a new node
	if (top == nullptr) //if top is null, make it point to the new node
		top = newNode;
	else //otherwise store the new node before top and move top
	{
		newNode->next = top;
		top = newNode;
	}
	++size; //increase stack size
}

TreapNode * Stack :: pop()
{
	TreapNode * returnNode = top->treapNode; //hold the node to return
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

TreapNode * Stack :: viewTop()
{
	return top->treapNode;
}



/**************************************************************************************************************
 * Functions for Queue
 * ***********************************************************************************************************/
void Queue :: enqueue(TreapNode * node)
{
	QueueNode * newNode = new QueueNode(node); //create a new node
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

TreapNode * Queue :: dequeue()
{
	TreapNode * returnNode = front->treapNode; //hold the node to return
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



/**************************************************************************************************************
 * Functions for Treap
 * ***********************************************************************************************************/
void Treap :: insert(int x)
{
	TreapNode * tree = root; //tree stores the reference to the node under which rotation will happen
	/*parent moves from root to leaf for inserting current node
	current points to the new node which is being inserted
	ancestor points to the ancestor nodes
	node will point to the child of ancestor*/
	TreapNode * parent = nullptr, * current = nullptr, * ancestor = nullptr, * node = nullptr;
	int priority = 1+(((rand()*rand()*2)-1)%(1000000000)); //generate a random priority

	if (root->right == nullptr) //if this is the first node being inserted, insert and return
	{
		root->right = new TreapNode(x,priority);
		return;
	}

	++insertKeyComparisons;
	if (root->right->data == x) //if the value is already present in root, throw exception
		throw "Duplicate Value Exception";

	//remove everything from stack and push the dummy node
	while (!stack.isEmpty())
		stack.pop();
	stack.push(root);

	/*Search for the location of the new node to be inserted*/
	parent = root->right; //start from the root of the treap
	while (true) //run an infinite loop
	{
		stack.push(parent); //push the parent into stack
		if (x == parent->data) //if the value already exists, throw an exception
			throw "Duplicate Value Exception";
		current = x < parent->data ? parent->left : parent->right; //move current point appropriately
		++insertKeyComparisons;
		if (current == nullptr) //if current becomes null
		{
			if (x < parent->data) //if x is less than parent
			{
				parent->left = new TreapNode(x,priority); //add x to left of parent
				current = parent->left; //point current to the newly added node
			}
			else //if x is greater than parent
			{
				parent->right = new TreapNode(x,priority); //add x to right of parent
				current = parent->right; //point current to the newly added node
			}
			node = current; //store the newly added node in node and break from loop
			break;
		}
		else //if current is not null
		{
			parent = current; //move parent
		}
	}

	while (stack.viewTop() != root) //till all the ancestors are checked
	{
		ancestor = stack.pop(); //pop the ancestor from stack
		tree = stack.viewTop(); //next top element will be the parent tree of ancestor
		if (ancestor->priority >= node->priority) //if the priorities do not maintain the order
		{
			++insertRotateCount;
			if (tree->left == ancestor) //if ancestor is on the left
			{
				tree->left = ancestor->left == node ? rightRotate(ancestor,node) : leftRotate(ancestor,node); //rotate and attach to left
				node = tree->left; //update node
			}
			else //otherwise
			{
				tree->right = ancestor->left == node ? rightRotate(ancestor,node) : leftRotate(ancestor,node); //rotate and attach to right
				node = tree->right; //update node
			}
		}
	}
}

bool Treap :: search(int x)
{
	TreapNode * returnNode = root->right; //point to root
	while (returnNode != nullptr && returnNode->data != x) //till the pointer is not null and its data is not equal to x
	{
		if (x < returnNode->data) //if x is smaller
			returnNode = returnNode->left != nullptr ? returnNode->left : nullptr; //if pointer points to leaf, make it null, otherwise, move left
		else //if x is greater
			returnNode = returnNode->right != nullptr ? returnNode->right : nullptr; //if pointer points to leaf, make it null, otherwise, move right
	}
	return (returnNode == nullptr ? false : true); //return a boolean value
}

void Treap :: deleteX(int x)
{
	tempCount = 0;
	TreapNode * node = searchNode(x); //search the node
	deleteKeyComparisons += tempCount;
	if (node == nullptr) //if not found
		throw "Missing Node Exception"; //throw an exception
	TreapNode * parent = getParent(node); //get its parent
	while (!isLeaf(node)) //till node becomes leaf
	{
		++deleteRotateCount;
		if (parent->left == node) //if node is a left child
		{
			parent->left = (node->left == nullptr ? leftRotate(node,node->right) :
								(node->right == nullptr ? rightRotate(node,node->left) :
									(node->left->priority < node->right->priority ? rightRotate(node,node->left) :
										leftRotate(node,node->right)))); //do proper rotation
			parent = parent->left; //update parent
		}
		else
		{
			parent->right = (node->left == nullptr ? leftRotate(node,node->right) :
								(node->right == nullptr ? rightRotate(node,node->left) :
									(node->left->priority < node->right->priority ? rightRotate(node,node->left) :
										leftRotate(node,node->right)))); //do proper rotation
			parent = parent->right; //update parent
		}
	}

	//delete node
	if (parent->left == node)
		parent->left = nullptr;
	else
		parent->right = nullptr;
	delete(node);
}

void Treap :: print(const char * fileName)
{
	string nodeStructure = ""; //stores the node structure
	string linkStructure = ""; //stores the pointer structure
	ofstream graphViz; //.gv file in output mode
	ofstream commands; //commands file in output mode

	string treapFileName = "";
	treapFileName.append(fileName);
	treapFileName.append(to_string(fileCount)); //along with a number that is file count
	treapFileName.append(".gv"); //adding extension name
	graphViz.open(treapFileName); //opening the file

	if (fileType == 0) //if os is windows
	{
		fileCount == 0 ? commands.open("commands.bat") : commands.open("commands.bat",std::ios_base::app); //open a batch file, first time in write mode and then in append mode
		commands << "dot -Tpng " << treapFileName << " -o "<< fileName << to_string(fileCount++) << ".png" << endl; //add the .gv to .png conversion command to batch file
	}
	else if (fileType == 1) //if os is linux
	{
		fileCount == 0 ? commands.open("commands.sh") : commands.open("commands.sh",std::ios_base::app); //open a shell script, first time in write mode and then in append mode
		commands << "dot -Tpng " << treapFileName << " -o "<< fileName << to_string(fileCount++) << ".png" << endl; //add the .gv to .png conversion command to shell script
	}

	commands.close(); //close the commands file

	if (root == nullptr) //if root is null
	{
		/*write a blank tree template and return*/
		graphViz << "digraph G {" << endl;
		graphViz << "node [shape = record, height = .1];" << endl;
		graphViz << "}" << endl;
		graphViz.close();
		return;
	}

	/*adding the root node to queue*/
	Queue queue;
	queue.enqueue(root);
	while (queue.isEmpty() == false) //till queue has more nodes
	{
		TreapNode * currNode = queue.dequeue(); //dequeue from the queue
		if (currNode->left != nullptr) //if left child is not null
			queue.enqueue(currNode->left); //add left child to queue
		if (currNode->right != nullptr) //if right child is not null
			queue.enqueue(currNode->right); //add right child to queue

		/*appending the node structure to nodeStructure*/
		nodeStructure.append(to_string(currNode->data));
		nodeStructure.append("[label = \"<L> |<D> ");
		nodeStructure.append(to_string(currNode->data));
		nodeStructure.append("(");
		nodeStructure.append(to_string(currNode->priority));
		nodeStructure.append(")");
		nodeStructure.append("|<R> \"");
		if (isLeaf(currNode))
			nodeStructure.append(",fontcolor=\"red\"");
		nodeStructure.append("];\n");

		/*appending pointer structure to linkStructure*/
		if (currNode->left != nullptr)
		{
			linkStructure.append("\"");
			linkStructure.append(to_string(currNode->data));
			linkStructure.append("\":L -> \"");
			linkStructure.append(to_string(currNode->left->data));
			linkStructure.append("\":D");
			linkStructure.append(";\n");
		}

		if (currNode->right != nullptr)
		{
			linkStructure.append("\"");
			linkStructure.append(to_string(currNode->data));
			linkStructure.append("\":R -> \"");
			linkStructure.append(to_string(currNode->right->data));
			linkStructure.append("\":D");
			linkStructure.append(";\n");
		}
	}
	//delete &queue;
	
	/*writing to .gv file and closing it*/
	graphViz << "digraph G {" << endl;
	graphViz << "node [shape = record, height = .1, color = \""<< color <<"\"];" << endl;

	graphViz << nodeStructure;
	graphViz << linkStructure;

	graphViz << "}" << endl;
	
	graphViz.close();
}

void Treap :: evaluatePerformance()
{
	ofstream evaluation;
	evaluation.open("evaluation.txt");
	evaluation << "Total: " << nop << endl;
	evaluation << "Insertions: " << insertCount << endl;
	evaluation << "Deletions: " << deleteCount << endl << endl << endl;
	evaluation << "Treap performance:" << endl;

	//height from root
	Queue queue;
	queue.enqueue(root->right);
	while (queue.isEmpty() == false) //till queue has more nodes
	{
		int currQueueSize = queue.getSize();
		int currLevelNodeCount = 0;
		++maxHeight;
		for (int i = 0; i < currQueueSize; ++i)
		{
			TreapNode * currNode = queue.dequeue(); //dequeue from the queue
			++currLevelNodeCount;
			++nodeCount;
			if (currNode->left != nullptr) //if left child is not null
				queue.enqueue(currNode->left); //add left child to queue
			if (currNode->right != nullptr) //if right child is not null
				queue.enqueue(currNode->right); //add right child to queue
		}
		totalHeight += (maxHeight*currLevelNodeCount);
	}

	//height from the reverse direction
	getTotalDepth(root->right);

	double avgHeight = double(totalHeight)/double(nodeCount);
	double avgDepth = double(totalDepth)/double(nodeCount);

	cout << "Total Key Comparisons: " << (insertKeyComparisons+deleteKeyComparisons) << endl;
	cout << "Total Rotations: " << (insertRotateCount+deleteRotateCount) << endl;
	cout << "Height of Tree: " << maxHeight << endl;
	cout << "Average height of nodes (from root to node): " << avgHeight << endl;
	cout << "Average height of nodes (from bottom): " << avgDepth << endl;
	cout << "Total number of Nodes: " << nodeCount << endl;
	evaluation << "Total Key Comparisons: " << (insertKeyComparisons+deleteKeyComparisons) << endl;
	evaluation << "Total Rotations: " << (insertRotateCount+deleteRotateCount) << endl;
	evaluation << "Height of Tree: " << maxHeight << endl;
	evaluation << "Average height of nodes (from root to node): " << avgHeight << endl;
	evaluation << "Average height of nodes (from bottom): " << avgDepth << endl;
	evaluation << "Total number of Nodes: " << nodeCount << endl << endl;
	evaluation.close();
	delete(elements);
	delete(window);
	/*delete &stack;
	delete &queue;*/
}

void Treap :: storeKeysInFile()
{
	ofstream file;
	file.open("keys.txt");

	Queue queue;
	queue.enqueue(root);
	while (queue.isEmpty() == false) //till queue has more nodes
	{
		TreapNode * currNode = queue.dequeue(); //dequeue from the queue
		if (currNode->left != nullptr) //if left child is not null
			queue.enqueue(currNode->left); //add left child to queue
		if (currNode->right != nullptr) //if right child is not null
			queue.enqueue(currNode->right); //add right child to queue
		file << currNode->data << endl;
	}

	file.close();
}

TreapNode * Treap :: leftRotate(TreapNode * oldRoot, TreapNode * rotate)
{
	TreapNode * newRoot = rotate;
	oldRoot->right = rotate->left;
	rotate->left = oldRoot;
	return newRoot;
}

TreapNode * Treap :: rightRotate(TreapNode * oldRoot, TreapNode * rotate)
{
	TreapNode * newRoot = rotate;
	oldRoot->left = rotate->right;
	rotate->right = oldRoot;
	return newRoot;
}

bool Treap :: isLeaf(TreapNode * node)
{
	if (node->left == nullptr && node->right == nullptr) //if both the children are null
		return true; //return true
	return false; //return false
}

TreapNode * Treap :: getParent(TreapNode * node)
{
	/*start from root*/
	TreapNode * temp = root->right;
	TreapNode * parent = root;
	while (temp != node) //till temp not equals to node
	{
		parent = temp; //move parent to temp
		if (node->data < temp->data) //if node is less than temp
			temp = temp->left; //move left
		else //otherwise
			temp = temp->right; //move right
	}
	return parent; //return parent otherwise
}

TreapNode * Treap :: searchNode(int x)
{
	TreapNode * returnNode = root->right; //point to root of tree
	while (returnNode != nullptr && returnNode->data != x) //till the pointer is not null and its data is not equal to x
	{
		++tempCount;
		if (x < returnNode->data) //if x is smaller
			returnNode = returnNode->left != nullptr ? returnNode->left : nullptr; //if pointer points to leaf, make it null, otherwise, move left
		else //if x is greater
			returnNode = returnNode->right != nullptr ? returnNode->right : nullptr; //if pointer points to leaf, make it null, otherwise, move right
	}
	return returnNode; //return the node
}

int Treap :: getTotalDepth(TreapNode * root)
{
	if (root == nullptr) return 0;
	int leftDepth = getTotalDepth(root->left);
	int rightDepth = getTotalDepth(root->right);
	int currentDepth = max(leftDepth,rightDepth)+1;
	totalDepth += currentDepth;
	return currentDepth;
}




/*


		else if (operation == 1) //if the number is 3, we have to search
		{
			if (flag) //if flag is true
			{
				flag = false; //set flag to false
				bool check = true;
				for (int c = 0; c < 5; ++c)
				{
					if (window[c] == 1)
						check = false;
				}
				if (check)
				{
					file << "print" << endl; //add print command
					window[windowIndex] = 1; //indicate print or not
					++windowIndex; windowIndex %= 5;
				}
			}
			index = rand()%(int(size*1.25)); //generate a random index
			file << "search " << elements[index] << endl; //search for the element present at the generated index of elements pile
			window[windowIndex] = 0; //indicate print or not
			++windowIndex; windowIndex %= 5;
		}

*/