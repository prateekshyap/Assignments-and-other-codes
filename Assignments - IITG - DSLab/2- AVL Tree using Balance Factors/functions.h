void printMessage()
{
	/*The initial message printed just after starting the execution*/
	cout << endl << endl << "-----------------------------------------" << endl;
	cout << "           AVL TREE OPERATIONS" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "1- Insert k" << endl;
	cout << "2- Delete k" << endl;
	cout << "3- Search for k" << endl;
	cout << "4- Print tree" << endl;
	cout << "5- Quit" << endl;
	cout << endl << "-----------------------------------------" << endl;
	cout << "              INPUT FORMAT" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "4\nmeans print the tree\n\n1\n5\n4\nmeans insert 5 into tree and then print tree\n\n2\n4\nmeans delete 4 from tree" << endl;
	cout << endl << "-----------------------------------------" << endl;
	cout << "              INSTRUCTIONS" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "1. Write a .txt file in mentioned format\nand enter the file name below" << endl;
	cout << "2. You can check execution details\nin \"output.txt\"" << endl;
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

/*
2
8
2
20
2
16
2
30
2
2
4
2
4
2
21
2
26
2
14
4
2
3
2
5
4
2
18
2
9
4
1
2
4
1
10
4
1
4
1
8
1
16
1
26
1
20
1
30
4
*/