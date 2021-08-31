void Stack :: push(TreeNode * node)
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

TreeNode * Stack :: pop()
{
	TreeNode * returnNode = top->treeNode; //hold the node to return
	if (top->next == nullptr) //if this is the last node, reset the stack
	{
		top = nullptr;
		size = 0;
	}
	else //otherwise move top and reduce size
	{
		top = top->next;
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

TreeNode * Stack :: viewTop()
{
	return top->treeNode;
}