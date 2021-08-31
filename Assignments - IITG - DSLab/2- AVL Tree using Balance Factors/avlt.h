/*fileCount stores a number so that multiple files could be created easily*/
int fileCount = -1, fileType = -1;
string color = "black"; //stores the color names
Stack stack;

void AVLTree :: insert(int x)
{
	TreeNode * tree = root; //tree stores the reference to the node under which rotation will happen
	/*start stores the balance point
	temp moves from root to leaf for inserting end node*/
	TreeNode * start = root->right, * temp = root->right;
	/*end points to the new node which is being inserted
	rotate points to the node where first potential rotation happens
	for single rotation, that is the first rotation itself
	for double rotation, the first rotation happens at rotate*/
	TreeNode * end = nullptr, * rotate = nullptr;
	int newBF = -2; //it stores the new balance factor
 
	TreeNode * newNode = new TreeNode(x); //create a new node for x
	if (temp == nullptr) //if this is the first node being inserted, insert and return
	{
		root->right = newNode;
		return;
	}
	if (temp->data == x) //if the value is already present in root, throw exception
		throw "Duplicate Value Exception";

	/*Search for the location of the new node to be inserted*/
	while (true) //run an infinite loop
	{
		if (x < temp->data) //if the new value is less than current node
		{
			end = temp->left; //move the end pointer to left
			if (end == nullptr) //if end becomes null
			{
				temp->left = newNode; //insert the node there
				end = temp->left; //point end to the new node
				break; //break from loop
			}
			else //if end is not null
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
		return;
	}
	else if (start->bF == -1*newBF)
	{
		start->bF = 0;
		return;
	}
	else
	{
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

void AVLTree :: deleteK(int x)
{
	TreeNode * tree = root; //tree stores the reference to the node under which rotation will happen
	TreeNode * start = root->right;
	TreeNode * node = nullptr, * parent = nullptr;

	node = searchNode(x);
	if (node == nullptr)
		throw "Missing Node Exception";
	parent = getParent(node);
	if (isLeaf(node))
		deleteLeafNode(node,parent);
	else if (node->left == nullptr || node->right == nullptr)
		deleteNodeWithSingleChild(node,parent);
	else
	{
		TreeNode * succ = leftMost(node->right); //find the successor of current node
		searchNode(succ->data);
		TreeNode * parentSucc = getParent(succ); //find the parent of the successor node
		TreeNode * newCurrNode = nullptr; //create another pointer
		if (isLeaf(succ)) //if successor is a leaf
			newCurrNode = deleteLeafNode(succ,parentSucc); //detach the successor by calling leaf deletion function and store in the pointer
		else //otherwise
			newCurrNode = deleteNodeWithSingleChild(succ,parentSucc); //detach the successor by calling single child deletion function and store in the pointer

	}
}

bool AVLTree :: isLeaf(TreeNode * node)
{
	if (node->left == nullptr && node->right == nullptr)
		return true;
	return false;
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

TreeNode * AVLTree :: searchNode(int x)
{
	while (!stack.isEmpty())
		stack.pop();
	stack.push(root);
	TreeNode * returnNode = root->right; //point to root
	while (returnNode != nullptr && returnNode->data != x) //till the pointer is not null and its data is not equal to x
	{
		if (returnNode != nullptr)
			stack.push(returnNode);
		if (x < returnNode->data) //if x is smaller
			returnNode = returnNode->left != nullptr ? returnNode->left : nullptr; //if pointer points to leaf, make it null, otherwise, move left
		else //otherwise
			returnNode = returnNode->right != nullptr ? returnNode->right : nullptr; //if pointer points to leaf, make it null, otherwise, move right
	}
	return returnNode; //return the node
}

TreeNode * AVLTree :: deleteLeafNode(TreeNode * node, TreeNode * parent)
{
	TreeNode * rotate = nullptr, * temp = nullptr;
	if (parent == root) //if parent is root
		root->right = nullptr;
	else if (parent->left == node) //if node is left child
		parent->left = nullptr;
	else //if node is right child
		parent->right = nullptr;
	while (stack.viewTop() != root)
	{
		TreeNode * ancestor = stack.pop();
		TreeNode * tree = stack.viewTop();
		int newBF = node->data < ancestor->data ? 1 : -1;
		if (ancestor->bF == newBF)
		{
			ancestor->bF = 0;
			continue;
		}
		else if (ancestor->bF == 0)
		{
			ancestor->bF = -1*newBF;
			node->left = node->right = nullptr;
			return node;
		}
		else //if (ancestor->bF == -1*newBF)
		{
			rotate = ancestor->bF == 1 ? ancestor->left : ancestor->right;
			if (rotate->bF == -1*newBF)
			{
				if (newBF == -1)
				{
					temp = rotate;
					ancestor->left = rotate->right;
					rotate->right = ancestor;
					ancestor->bF = 0;
					rotate->bF = 0;
				}
				else //if (newBF == 1)
				{
					temp = rotate;
					ancestor->right = rotate->left;
					rotate->left = ancestor;
					ancestor->bF = 0;
					rotate->bF = 0;
				}
			}
			else if (rotate->bF == newBF)
			{
				if (newBF == -1)
				{
					temp = rotate->right;
					rotate->right = temp->left;
					temp->left = rotate;
					ancestor->left = temp->right;
					temp->right = ancestor;
					ancestor->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? 0 : newBF;
					rotate->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? -1*newBF : 0;
					temp->bF = 0;
				}
				else //if (newBF == 1)
				{
					temp = rotate->left;
					rotate->left = temp->right;
					temp->right = rotate;
					ancestor->right = temp->left;
					temp->left = ancestor;
					ancestor->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? 0 : newBF;
					rotate->bF = temp->bF == 0 ? 0 : temp->bF == newBF ? -1*newBF : 0;
					temp->bF = 0;
				}
			}
		}
		if (ancestor == tree->right)
			tree->right = temp;
		else
			tree->left = temp;
	}
	/*reset the node and return*/
	node->left = node->right = nullptr;
	return node;
}

TreeNode * AVLTree :: deleteNodeWithSingleChild(TreeNode * node, TreeNode * parent)
{
	/*if (node->left == nullptr || node->leftThread == true) //if right child is present
	{
		if (parent == nullptr) //if parent is null
		{
			TreeNode * succ = leftMost(node->right); //find the successor of node
			if (succ->leftThread == true) //if its left thread is present, delete it
			{
				succ->leftThread = false;
				succ->left = nullptr;
			}
			root = root->right; //move root
		}
		else if (parent->right == node) //if node is right child
		{
			parent->right = node->right; //store node's right in parent's right
			TreeNode * succ = leftMost(parent->right); //find the successor of node
			if (succ->leftThread == true) succ->left = parent; //if its left thread is present then point it to parent
		}
		else //if node is left child
		{
			parent->left = node->right; //store node's right in parent's left
			TreeNode * succ = leftMost(parent->left); //find the successor of node
			succ->left = node->left; //store node's left in successor's left
			succ->leftThread = node->leftThread; //store node's left thread in successor's left thread
		}			
	}
	else if (node->right == nullptr || node->rightThread == true) //if left child is present
	{
		if (parent == nullptr) //if parent is null
		{
			TreeNode * predec = rightMost(node->left); //find the successor of node
			if (predec->rightThread == true) //if its right thread is present, delete it
			{
				predec->rightThread = false;
				predec->right = nullptr;
			}
			root = root->left; //move root
		}
		else if (parent->left == node) //if node is left child
		{
			parent->left = node->left; //store node's left in parent's left
			TreeNode * predec = rightMost(parent->left); //find the predecessor of node
			if (predec->rightThread == true) predec->right = parent; //if its right thread is present then point it to parent
		}
		else //if node is right child
		{
			parent->right = node->left; //store node's left in parent's right
			TreeNode * predec = rightMost(parent->right); //find the predecessor of node
			predec->right = node->right; //store node's right in successor's right
			predec->rightThread = node->rightThread; //store node's right thread in successor's right thread
		}
	}
	node->left = node->right = nullptr;
	node->leftThread = node->rightThread = false;
	return node;*/
	return nullptr;
}

TreeNode * AVLTree :: leftMost(TreeNode * node)
{
	if (node == nullptr) //if node is null return null
		return nullptr;
	TreeNode * temp = node; //start from node
	while (temp->left != nullptr) //move left till there is no more left child
		temp = temp->left;
	return temp;
}

TreeNode * AVLTree :: rightMost(TreeNode * node)
{
	if (node == nullptr) //if node is null return null
		return nullptr;
	TreeNode * temp = node; //start from node
	while (temp->right != nullptr) //move right till there is no more right child
		temp = temp->right;
	return temp;
}

TreeNode * AVLTree :: getParent(TreeNode * node)
{
	/*start from root*/
	TreeNode * temp = root->right;
	TreeNode * parent = root;
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