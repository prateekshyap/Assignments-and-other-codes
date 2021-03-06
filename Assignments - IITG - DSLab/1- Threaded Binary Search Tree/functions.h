void printMessage()
{
	/*The initial message printed just after starting the execution*/
	cout << "1- Insert x" << endl;
	cout << "2- Search x" << endl;
	cout << "3- Delete x" << endl;
	cout << "4- Reverse Inorder Traversal" << endl;
	cout << "5- Successor of x" << endl;
	cout << "6- Split the tree around k" << endl;
	cout << "7- Elements between k1 and k2" << endl;
	cout << "8- kth largest element" << endl;
	cout << "9- Print tree" << endl;
	cout << "10- Quit" << endl;
	cout << "Input Format-\n9\nmeans print the tree\n1\n5\n9\nmeans insert 5 into tree and then print tree\n7\n9\n14\nmeans find elements between 9 to 14" << endl;
	cout << "Write a .txt file in mentioned format and give the file name-" << endl;
	cout << "You can check execution details in output.txt" << endl;
}

void printLinkedList(List list, ofstream &file)
{
	ListNode * temp = list.head; //make temp to point head
	while (temp != nullptr) //till temp is not null
	{
		cout << temp->data << "->"; //print the value to console
		file << temp->data << "->"; //print the value to file
		temp = temp->next; //move temp to next node
	}
	cout << "X" << endl; //print end of list to console
	file << "X" << endl; //print end of list to file
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