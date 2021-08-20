void List :: addNode(TreeNode * treeNode)
{
	tail->next = new ListNode(treeNode->data); //add a node to the next of tail
	tail = tail->next; //move tail
}

void List :: trim()
{
	head = head->next; //move head
}