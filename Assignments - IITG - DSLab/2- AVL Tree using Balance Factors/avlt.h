/*fileCount stores a number so that multiple files could be created easily*/
int fileCount = -1, fileType = -1;
string color = "black"; //stores the color names

void AVLTree :: insert(int x)
{
	TreeNode *tree = root;
	TreeNode *start = root->right;
	TreeNode *temp = root->right;
	TreeNode *end = nullptr, *rotate = nullptr;
	int newBF = -2;
 
	TreeNode *newNode = new TreeNode(x);

	if (temp == nullptr)
	{
		root->right = newNode;
		return;
	}

	if (temp->data == x)
		throw "Duplicate Value Exception";
 
	while (true)
	{
		if (x < temp->data)
		{
			end = temp->left;
			if (end == nullptr)
			{
				temp->left = newNode;
				end = temp->left;
				break;
			}
			else
			{
				if (end->bF != 0)
				{
					tree = temp;
					start = end;
				}
				temp = end;
			}
		}
		else if (x > temp->data)
		{
			end = temp->right;
			if (end == nullptr)
			{
				temp->right = newNode;
				end = temp->right;
				break;
			}
			else
			{
				if(end->bF != 0)
				{
					tree = temp;
					start = end;
				}
				temp = end;
			}
		}
		else
			throw "Duplicate Value Exception";
	}

	newBF = x < start->data ? 1 : -1;
 
	rotate = newBF == 1 ? start->left : start->right;
	temp = newBF == 1 ? start->left : start->right;
	
	while (temp != end)
	{
		if (x < temp->data)
		{
			temp->bF = 1;
			temp = temp->left;
		}
		else if (x > temp->data)
		{
			temp->bF = -1;
			temp = temp->right;
		}
	}

	if (start->bF == 0)
	{
		start->bF = newBF;
		//++root->left->data;
		return;
	}
	else if (start->bF == -1*newBF)
	{
		start->bF = 0;
		return;
	}
	else
	{
		//single rotation
		if (rotate->bF == newBF)
		{
			if (newBF == 1)
			{
				temp = rotate;
				start->left = rotate->right;
				rotate->right = start;
				start->bF = 0;
				rotate->bF = 0; 
			}
			else if(newBF == -1)
			{
				temp = rotate;
				start->right = rotate->left;
				rotate->left = start;
				start->bF = 0;
				rotate->bF = 0;
			}
		}
		//double rotation
		else if (rotate->bF == -1*newBF)
		{
			if (newBF == 1)
			{
				temp = rotate->right;
				rotate->right = temp->left;
				temp->left = rotate;
				start->left = temp->right;
				temp->right = start;
				start->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? -1*newBF : 0;
				rotate->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? 0 : newBF;
				temp->bF = 0;
			}
			else if (newBF == -1)
			{
				temp = rotate->left;
				rotate->left = temp->right;
				temp->right = rotate;
				start->right = temp->left;
				temp->left = start;
				start->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? -1*newBF : 0;
				rotate->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? 0 : newBF;
				temp->bF = 0;
			}
		}
	}
 
	if (start == tree->right)
		tree->right = temp;
	else tree->left = temp;
}

TreeNode * AVLTree :: searchNode(int x)
{
	TreeNode * returnNode = root->right; //point to root
	while (returnNode != nullptr && returnNode->data != x) //till the pointer is not null and its data is not equal to x
	{
		if (x < returnNode->data) //if x is smaller
			returnNode = returnNode->left != nullptr ? returnNode->left : nullptr; //if pointer points to leaf, make it null, otherwise, move left
		else //otherwise
			returnNode = returnNode->right != nullptr ? returnNode->right : nullptr; //if pointer points to leaf, make it null, otherwise, move right
	}
	return returnNode; //return the node
}

bool AVLTree :: search(int x)
{
	TreeNode * returnNode = root->right; //point to root
	while (returnNode != nullptr && returnNode->data != x) //till the pointer is not null and its data is not equal to x
	{
		if (x < returnNode->data) //if x is smaller
			returnNode = returnNode->left != nullptr ? returnNode->left : nullptr; //if pointer points to leaf, make it null, otherwise, move left
		else //otherwise
			returnNode = returnNode->right != nullptr ? returnNode->right : nullptr; //if pointer points to leaf, make it null, otherwise, move right
	}
	return (returnNode == nullptr ? false : true); //return the node
}

void AVLTree :: print()
{
	string nodeStructure = ""; //stores the node structure
	string linkStructure = ""; //stores the pointer structure
	ofstream graphViz; //.gv file in output mode
	ofstream commands; //commands file in output mode

	string treeFileName = "bstStructure"; //giving a distinguishable file name
	treeFileName.append(to_string(fileCount)); //along with a number that is file count
	treeFileName.append(".gv"); //adding extension name
	graphViz.open(treeFileName); //opening the file

	if (fileType == 0) //if os is windows
	{
		fileCount == 0 ? commands.open("commands.bat") : commands.open("commands.bat",std::ios_base::app); //open a batch file, first time in write mode and then in append mode
		commands << "dot -Tpng " << treeFileName << " -o struct" << to_string(fileCount++) << ".png" << endl; //add the .gv to .png conversion command to batch file
	}
	else if (fileType == 1) //if os is linux
	{
		fileCount == 0 ? commands.open("commands.sh") : commands.open("commands.sh",std::ios_base::app); //open a shell script, first time in write mode and then in append mode
		commands << "dot -Tpng " << treeFileName << " -o struct" << to_string(fileCount++) << ".png" << endl; //add the .gv to .png conversion command to shell script
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
		TreeNode * currNode = queue.dequeue(); //dequeue from the queue
		if (currNode->left != nullptr) //if left child is not null
			queue.enqueue(currNode->left); //add left child to queue
		if (currNode->right != nullptr) //if right child is not null
			queue.enqueue(currNode->right); //add right child to queue

		/*appending the node structure to nodeStructure*/
		nodeStructure.append(to_string(currNode->data));
		nodeStructure.append("[label = \"<L> |<D> ");
		nodeStructure.append(to_string(currNode->data));
		nodeStructure.append(",");
		nodeStructure.append(to_string(currNode->bF));
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
	
	/*writing to .gv file and closing it*/
	graphViz << "digraph G {" << endl;
	graphViz << "node [shape = record, height = .1, color = \""<< color <<"\"];" << endl;

	graphViz << nodeStructure;
	graphViz << linkStructure;

	graphViz << "}" << endl;
	
	graphViz.close();					
}

TreeNode * AVLTree :: copyNodes(TreeNode * root, unordered_map<TreeNode *, TreeNode *> &map)
{
	TreeNode * newNode = new TreeNode(root->data); //create a new node having same data as root
	map[root] = newNode; //store it in map
	if (root->left != nullptr) //if root has a left child
		newNode->left = copyNodes(root->left,map); //recur on left child
	if (root->right != nullptr) //if root has a right child
		newNode->right = copyNodes(root->right,map); //recur on right child
	return newNode;
}

bool AVLTree :: isLeaf(TreeNode * node)
{
	if (node->left == nullptr && node->right == nullptr)
		return true;
	return false;
}