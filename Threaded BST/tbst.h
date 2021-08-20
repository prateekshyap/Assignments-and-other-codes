/*fileCount stores a number so that multiple files could be created easily*/
int fileCount = -1, fileType = -1;
string color = "black"; //stores the color names

void BinarySearchTree :: insert(int x)
{
	if (root == nullptr) //if root is null then create root
		root = new TreeNode(x);
	else if (root->data == x) //if x is equal to root, throw exception
		throw "Duplicate Value Exception";
	else //otherwise call recursive insertion
		insertIntoTree(root,x);
}

TreeNode * BinarySearchTree :: search(int x)
{
	TreeNode * returnNode = root; //point to root
	while (returnNode != nullptr && returnNode->data != x) //till the pointer is not null and its data is not equal to x
	{
		if (x < returnNode->data) //if x is smaller
			returnNode = returnNode->leftThread == true ? nullptr : returnNode->left; //if pointer points to leaf, make it null, otherwise, move left
		else //otherwise
			returnNode = returnNode->rightThread == true ? nullptr : returnNode->right; //if pointer points to leaf, make it null, otherwise, move right
	}
	return returnNode; //return the node
}

void BinarySearchTree :: deleteX(int x)
{
	TreeNode * curr = search(x); //search x
	TreeNode * parent = nullptr; //parent pointer
	if (curr == nullptr) //if x is not found throw exception
		throw "Missing Node Exception";
	else //otherwise find the parent
		parent = getParent(curr);
	if (isLeaf(curr) == true) //for leaf node
	{
		reduceSubtreeCount(curr); //reduce the subtree count till current node
		deleteLeafNode(curr,parent); //delete the leaf node
	}
	else if ((curr->left == nullptr || curr->leftThread == true) || (curr->right == nullptr || curr->rightThread == true)) //for single child
	{
		reduceSubtreeCount(curr); //reduce the subtree count till current node
		deleteNodeWithSingleChild(curr,parent); //delete the current node
	}
	//for double children, replacing with successor strategy
	else
	{
		TreeNode * succ = leftMost(curr->right); //find the successor of current node
		TreeNode * parentSucc = getParent(succ); //find the parent of the successor node
		TreeNode * newCurrNode = nullptr; //create another pointer
		if (isLeaf(succ) == true) //if successor is a leaf
		{
			reduceSubtreeCount(succ); //reduce the subtree count till successor
			newCurrNode = deleteLeafNode(succ,parentSucc); //detach the successor by calling leaf deletion function and store in the pointer
		}
		else //otherwise
		{
			reduceSubtreeCount(succ); //reduce the subtree count till successor
			newCurrNode = deleteNodeWithSingleChild(succ,parentSucc); //detach the successor by calling single child deletion function and store in the pointer
		}
		if (curr == root) //if current node is root
			root = newCurrNode; //point root to the new node
		else //otherwise attach the new node to the parent of current node
		{
			if (parent->left == curr)
				parent->left = newCurrNode;
			else
				parent->right = newCurrNode;
		}
		/*update the children of the new node*/
		newCurrNode->left = curr->left;
		newCurrNode->right = curr->right;
		/*update the subtree count of the new node*/
		newCurrNode->leftSubtreeCount = curr->leftSubtreeCount;
		newCurrNode->rightSubtreeCount = curr->rightSubtreeCount;
		/*update the threads if any, for safety*/
		TreeNode * predec = rightMost(newCurrNode->left);
		if (predec != nullptr && predec->rightThread == true)
		{
			predec->rightThread = true;
			predec->right = newCurrNode;
		}
		succ = leftMost(newCurrNode->right);
		if (succ != nullptr && succ->leftThread == true)
		{
			succ->leftThread = true;
			succ->left = newCurrNode;
		}
	}
	free(curr);
}

List BinarySearchTree :: reverseInOrder()
{
	List list;
	TreeNode * temp = rightMost(root); //find the rightmost node
	while (temp != nullptr) //till the pointer becomes null
	{
		list.addNode(temp); //add the node to linked list
		if (temp->leftThread == true) //if thread is present
			temp = temp->left; //move there
		else //otherwise
			temp = rightMost(temp->left); //move to the rightmost node of the left subtree
	}
	list.trim(); //trim the list
	return list;
}

int BinarySearchTree :: successor(TreeNode * xNode)
{
	if (xNode == nullptr) //if pointer is null throw exception
		throw "Missing Node Exception";
	else if (xNode->rightThread == true) //if right thread is present return it
		return xNode->right->data;
	else if (xNode->right == nullptr) //if right pointer is null then there is no successor
		throw "Largest Node Given";
	return leftMost(xNode->right)->data; //otherwise get the leftmost node of the right subtree
}

TreeNode * BinarySearchTree :: split(int k)
{
	TreeNode * returnNode = new TreeNode(0); //create a dummy node
	/*first and second are two pointers between whom cuts will be made
	prevCut holds the node from which last cut was made*/
	TreeNode * first = root, *second = root, * prevCut = nullptr;
	/*point the first root to original root because this is not going to be changed
	second root should be null initially*/
	TreeNode * root1 = root, * root2 = nullptr;
	/*have two pointers for successros and predecessors*/
	TreeNode * succ = nullptr, * predec = nullptr;
	if (k >= root->data) //if k is greater than or equal to root
		second = root->right; //move second pointer to right
	else //otherwise
		second = root->left; //move second pointer to left
	while (!isLeaf(first) && second != nullptr) //till the first pointer is not leaf and second pointer is not null
	{
		if (k >= first->data) //if k is greater than equal to first
		{
			if (k < second->data) //and less than second, we need to put a cut there
			{
				if (root2 == nullptr) //update second root if it is null
					root2 = second;
				first->right = nullptr; //make the right pointer of first null
				first->rightSubtreeCount = 0; //make the right subtree count 0
				if (prevCut != nullptr) //if prevCut is not null
				{
					prevCut->left = second; //point its left pointer to the second node
					prevCut->leftSubtreeCount += (second->leftSubtreeCount+second->rightSubtreeCount+1); //update its subtree count
				}
				prevCut = first; //update prevCut
				succ = leftMost(second); //find the successor of first
				if (succ->left == first && succ->data > k) //if the successor's left thread is first node and value is greater than k, delete the thread
				{
					succ->leftThread = false;
					succ->left = nullptr;
				}
			}
			first = second; //move first to second and update the second
			if (k >= second->data) //if k is greater than or equal to second
				second = second->right; //move second pointer right
			else //otherwise
				second = second->left; //move second pointer left
		}
		else //if k is less than first
		{
			if (k >= second->data) //and greater than equal to second, we need to put a cut there
			{
				if (root2 == nullptr) //update second root if it is null
					root2 = second;
				first->left = nullptr; //make the left pointer of first null
				first->leftSubtreeCount = 0; //make the left subtree count 0
				if (prevCut != nullptr) //if prevCut is not null
				{
					prevCut->right = second; //point its right pointer to the second node
					prevCut->rightSubtreeCount += (second->leftSubtreeCount+second->rightSubtreeCount+1); //update its subtree count
				}
				prevCut = first; //update prevCut
				predec = rightMost(second); //find the predecessor of first
				if (predec->right == first && predec->data <= k) //if the predecessor's right thread is first node and value is less then equal to k, delete the thread
				{
					predec->rightThread = false;
					predec->right = nullptr;
				}
			}
			first = second; //move first to second and update the second
			if (k >= second->data) //if k is greater than or equal to second
				second = second->right; //move second pointer right
			else //otherwise
				second = second->left; //move second pointer left
		}
	}
	TreeNode * temp = root; //store current root in temp
	root = root1; //store root1 in root
	color = "blue"; //set color to blue
	printTree(); //print the tree
	root = root2; //store root2 in root
	color = "green"; //set color to green
	printTree(); //print the tree
	root = temp; //restore root
	color = "black"; //reset color
	returnNode->left = root1; //attach root1 to the left child of dummy node
	returnNode->right = root2; //attach root2 to the right child of dummy node
	return returnNode; //return dummy node
}

List BinarySearchTree :: inOrder()
{
	List list;
	TreeNode * temp = leftMost(root); //find the leftmost node
	while (temp != nullptr) //till the pointer becomes null
	{
		list.addNode(temp); //add the node to linked list
		if (temp->rightThread == true) //if thread is present
			temp = temp->right; //move there
		else //otherwise
			temp = leftMost(temp->right); //move to the leftmost node of the right subtree
	}
	list.trim(); //trim the list
	return list;
}

List BinarySearchTree :: allElementsBetween(int k1, int k2)
{
	List list;
	/*temp points to root
	k1Node and k2Node are initially null*/
	TreeNode * temp = root, * k1Node = nullptr, * k2Node = nullptr;
	while (temp != nullptr && temp->data != k1) //till temp is not null and the data is not equal to k1
	{
		if (k1 < temp->data) //if k1 is less than temp
		{
			if (k1Node == nullptr || (k1Node->data >= temp->data && temp->data >= k1)) k1Node = temp; //update k1node
			temp = temp->leftThread == true ? nullptr : temp->left; //mode temp to left
		}
		else //otherwise
		{
			if (k1Node == nullptr || (k1Node->data >= temp->data && temp->data >= k1)) k1Node = temp; //update k1node
			temp = temp->rightThread == true ? nullptr : temp->right; //move temp to right
		}
	}
	temp = root; //reset temp
	while (temp != nullptr && temp->data != k2) //till temp is not null and the data is not equal to k2
	{
		if (k2 < temp->data) //if k2 is less than temp
		{
			if (k2Node == nullptr || (k2Node->data <= temp->data && temp->data <= k2)) k2Node = temp; //update k2node
			temp = temp->leftThread == true ? nullptr : temp->left; //mode temp to left
		}
		else //otherwise
		{
			if (k2Node == nullptr || (k2Node->data <= temp->data && temp->data <= k2)) k2Node = temp; //update k2node
			temp = temp->rightThread == true ? nullptr : temp->right; //move temp to right
		}
	} 

	temp = k1Node; //start from k1node
	while (temp != k2Node) //till temp is not equal to k2 node
	{
		list.addNode(temp); //add the node to the list
		if (temp->rightThread == true) //if right thread is present
			temp = temp->right; //move there
		else //otherwise
			temp = leftMost(temp->right); //move to the successor
	}
	list.addNode(temp); //add k2node to list
	list.trim(); //trim the list
	return list;
}

int BinarySearchTree :: kthElement(int k)
{
	if (root->leftSubtreeCount+root->rightSubtreeCount+1 < k) //if the total number of nodes is less than k, throw exception
		throw "Out of range";
	TreeNode * temp = root; //start from root
	while (true)
	{
		int discardCount = temp->rightSubtreeCount+1; //find out the number of nodes to be discarded
		if (discardCount == k) //if this count is equal to k
			return temp->data; //return the current node data
		else if (discardCount > k) //if count is greater
			temp = temp->right; //move to right
		else //otherwise
		{
			temp = temp->left; //move left
			k -= discardCount; //subtract the count, that means discard the right subtree along with current node
		}
	}
}

void BinarySearchTree :: printTree()
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
		if (currNode->left != nullptr && currNode->leftThread == false) //if left thread is false
			queue.enqueue(currNode->left); //add left child to queue
		if (currNode->right != nullptr && currNode->rightThread == false) //if right thread is false
			queue.enqueue(currNode->right); //add right child to queue

		/*appending the node structure to nodeStructure*/
		nodeStructure.append(to_string(currNode->data));
		nodeStructure.append("[label = \"<L> |<D> ");
		nodeStructure.append(to_string(currNode->data));
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
			if (currNode->leftThread == true)
				linkStructure.append("[style=dashed]");
			linkStructure.append(";\n");
		}

		if (currNode->right != nullptr)
		{
			linkStructure.append("\"");
			linkStructure.append(to_string(currNode->data));
			linkStructure.append("\":R -> \"");
			linkStructure.append(to_string(currNode->right->data));
			linkStructure.append("\":D");
			if (currNode->rightThread == true)
				linkStructure.append("[style=dashed]");
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

void BinarySearchTree :: insertIntoTree(TreeNode * root, int x)
{
	if (x < root->data) //if x is less than root
	{
		if (root->left == nullptr || root->leftThread == true) //if left is null or left thread is present
		{
			TreeNode * newNode = new TreeNode(x); //create a new node

			newNode->rightThread = true; //mark its right thread to be true
			newNode->right = root; //point the right thread to root

			if (root->leftThread == true) //if root has a left thread
			{
				newNode->left = root->left; //update the left child of new node
				root->left = newNode; //store new node in root's left
				root->leftThread = false; //mark root's left thread false
				if (newNode->left != nullptr) newNode->leftThread = true; //if new node's left is not null, mark thread true
			}
			else //otherwise
				root->left = newNode; //store new node in root's left
			++root->leftSubtreeCount; //increase the left subtree count
		}
		else if (root->left->data == x) //if x is already present in left
			throw "Duplicate Value Exception"; //throw exception
		else //otherwise
		{
			insertIntoTree(root->left, x); //recur
			++root->leftSubtreeCount; //increase the left subtree count
		}
	}
	if (x > root->data) //if x is greater than root
	{
		if (root->right == nullptr || root->rightThread) //if right is null or right thread is present
		{
			TreeNode * newNode = new TreeNode(x); //create a new node

			newNode->leftThread = true; //mark its left thread to be true
			newNode->left = root; //point the left thread to root

			if (root->rightThread == true) //if root has a right thread
			{
				newNode->right = root->right; //update the right child of new node
				root->right = newNode; //store new node in root's right
				root->rightThread = false; //mark root's right thread false
				if (newNode->right != nullptr) newNode->rightThread = true; //if new node's right is not null, mark thread true
			}
			else //otherwise
				root->right = newNode; //store new node in root's right
			++root->rightSubtreeCount; //increase the right subtree count
		}
		else if (root->right->data == x) //if x is already present in right
			throw "Duplicate Value Exception"; //throw exception
		else //otherwise
		{
			insertIntoTree(root->right, x); //recur
			++root->rightSubtreeCount; //increase the right subtree count
		}
	}
}

void BinarySearchTree :: reduceSubtreeCount(TreeNode * node)
{
	TreeNode * temp = root; //start from root
	while (temp != node) //till temp is not equal to node
	{
		if (node->data < temp->data) //if node is less than temp
		{
			--temp->leftSubtreeCount; //reduce left subtree count
			temp = temp->left; //move left
		}
		else //otherwise
		{
			--temp->rightSubtreeCount; //reduce right subtree count
			temp = temp->right; //move right
		}
	}
}

bool BinarySearchTree :: isLeaf(TreeNode * node)
{
	if ((node->left == nullptr || node->leftThread == true) && (node->right == nullptr || node->rightThread == true))
		return true;
	return false;
}

TreeNode * BinarySearchTree :: deleteLeafNode(TreeNode * node, TreeNode * parent)
{
	if (parent == nullptr) //if parent is null store null in root
		root = nullptr; //store null in root
	else if (parent->left == node) //if node is left child
	{
		parent->left = node->left; //store node's left in parent's left
		if (parent->left != nullptr) //update thread
			parent->leftThread = true;
	}
	else //if node is right child
	{
		parent->right = node->right; //store node's right in parent's right
		if (parent->right != nullptr) //update thread
			parent->rightThread = true;
	}
	/*reset the node and return*/
	node->left = node->right = nullptr;
	node->leftThread = node->rightThread = false;
	return node;
}

TreeNode * BinarySearchTree :: deleteNodeWithSingleChild(TreeNode * node, TreeNode * parent)
{
	if (node->left == nullptr || node->leftThread == true) //if right child is present
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
	/*reset the node and return*/
	node->left = node->right = nullptr;
	node->leftThread = node->rightThread = false;
	return node;
}

TreeNode * BinarySearchTree :: leftMost(TreeNode * node)
{
	if (node == nullptr) //if node is null return null
		return nullptr;
	TreeNode * temp = node; //start from node
	while (temp->left != nullptr && temp->leftThread == false) //move left till there is no more left child
		temp = temp->left;
	return temp;
}

TreeNode * BinarySearchTree :: rightMost(TreeNode * node)
{
	if (node == nullptr) //if node is null return null
		return nullptr;
	TreeNode * temp = node; //start from node
	while (temp->right != nullptr && temp->rightThread == false) //move right till there is no more right child
		temp = temp->right;
	return temp;
}

TreeNode * BinarySearchTree :: getParent(TreeNode * node)
{
	/*start from root*/
	TreeNode * temp = root;
	TreeNode * parent = root;
	while (temp != node) //till temp not equals to node
	{
		parent = temp; //move parent to temp
		if (node->data < temp->data) //if node is less than temp
			temp = temp->left; //move left
		else //otherwise
			temp = temp->right; //move right
	}
	if (temp == parent) //if temp and parent are still equal
		return nullptr; //return null
	return parent; //return parent otherwise
}

TreeNode * BinarySearchTree :: copyNodes(TreeNode * root, unordered_map<TreeNode *, TreeNode *> &map)
{
	TreeNode * newNode = new TreeNode(root->data); //create a new node having same data as root
	/*copy the subtree counts*/
	newNode->leftSubtreeCount = root->leftSubtreeCount;
	newNode->rightSubtreeCount = root->rightSubtreeCount;
	map[root] = newNode; //store it in map
	/*copy thread details*/
	if (root->leftThread == true)
	{
		newNode->left = map[root->left];
		newNode->leftThread = true;
	}
	if (root->rightThread == true)
	{
		newNode->right = map[root->right];
		newNode->rightThread = true;
	}
	if (root->left != nullptr && root->leftThread == false) //if root has a left child
		newNode->left = copyNodes(root->left,map); //recur on left child
	if (root->right != nullptr && root->rightThread == false) //if root has a right child
		newNode->right = copyNodes(root->right,map); //recur on right child
	return newNode;
}