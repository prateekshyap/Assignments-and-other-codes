void Queue :: enqueue(TreeNode * node)
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

TreeNode * Queue :: dequeue()
{
	TreeNode * returnNode = front->treeNode; //hold the node to return
	if (front == rear) //if this is the last node, reset the queue
	{
		front = rear = nullptr;
		size = 0;
	}
	else //otherwise move front and reduce the size
	{
		front = front->next;
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