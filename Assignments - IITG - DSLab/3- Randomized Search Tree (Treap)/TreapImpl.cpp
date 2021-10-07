using namespace std;

//inbuilt header files
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<exception>
#include<unordered_map>
#include<ctime>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//header files created for various tasks
#include"nodes.h" // contains all the node structures
#include"datastructures.h" //contains all the data structures
#include"functions.h" //contains all functions

extern int fileCount, fileType, low, high, ratio; //external variables

int main()
{
	/*choice stores the choice of operation by the user
	x stores the data given by user
	os stores the type of os being used
	randomInputCount keeps track of the number of random input files generated
	i is a loop variable
	count, percentageBreak, nop are used for printing the progress bar*/
	int choice = 0, x = 0, os = -1, randomInputCount = 0, quitStatus = -1, i = 0, count = 0, percentageBreak = 0, nop = 0;
	Treap treap; //treap object
	/*inputFileName stores the input file name
	outputFileName stores the output file name
	printFileName takes the file name from user
	timestamp stores the current timestamp in string format
	inputString stores the string read from the input file
	evaluation file will store the commands to run BST and AVLT which will be executed at the end of this program*/
	string inputFileName = "", outputFileName = "", printFileName = "", fileSequence = "fileSequence.txt", timestamp = "", inputString = "", evaluationFile = "evaluate.";
	/*isXPresent indicates if x is present or not
	isBegin indicates whether the first run
	printStatus indicates whether intermediate print commands should be added or not*/
	bool isXPresent = false, isBegin = true, printStatus = true;
	time_t now; //stores the current time
	ifstream inputFile; //input file stream
	ofstream outputFile; //output file stream

	//deciding the type of os being used
	cout << "Enter a number(0 for Windows / 1 for Linux)-" << endl;
	cin >> os;
	if (os == 0)
	{
		//remove all existing graphviz and image files
		std :: system("del *.gv");
		std :: system("del *.png");
		evaluationFile.append("bat");
	}
	else if (os == 1)
	{
		//remove all existing graphviz and image files
		std :: system("rm *.gv");
		std :: system("rm *.png");
		evaluationFile.append("sh");
	}
	fileType = os; //initializing fileType
	fileCount = 0; //initializing fileCount
	//deciding the user given file name
	cout << "Enter universal file name to generate images(Don't write extension names)-" << endl;
	cin >> printFileName;
	//deciding the range of key values
	cout << "Enter the range of values to be inserted (first minimum then maximum)-" << endl;
	cin >> low >> high;
	//deciding the ratio of insertion and deletion for random input file generation
	cout << "How many insertions do you want for 100 operations? (Enter 0 if you want a random number)" << endl;
	cin >> ratio;

	outputFileName.append(printFileName);
	outputFileName.append("Output.txt");
	outputFile.open(outputFileName); //open the output file
	
	while (true) //run till it hits quit
	{	
		//take input for random input file or manual input file
		cout << endl << "Enter a number(0 for random input file / 1 for manual input file)-" << endl;
		cin >> choice;
		if (choice == 0) //if random
		{
			isBegin = false; //mark begin as false
			inputFileName = "randomInput";
			inputFileName.append(to_string(randomInputCount++));
			inputFileName.append(".txt");
			cout << "Enter number of operations-" << endl; //take the number of operations
			cin >> x;
			nop = x;
			/*if (nop > (high-low+1))
			{
				high = high+nop;
				if (high < 0)
					high = INT_MAX;
			}*/
			if (nop >= 1000) //for larger input files, confirm about intermediate print commands
			{
				cout << "Too big number! Still want to print intermediate tree images? (Y/N)" << endl;
				cin >> inputString;
				if (inputString.compare("N") == 0 || inputString.compare("n") == 0)
					printStatus = false;
			}
			percentageBreak = x/100; //find out the progress bar break point
			cout << "Enter 0 if you want to quit after this run, 1 if you want to give further inputs-" << endl;
			cin >> quitStatus;
			/*generate input files*/
			if (randomInputCount == 1)
			{
				generateInput(x,inputFileName,quitStatus,printStatus,0);
				writeFileSequence(fileSequence,inputFileName,0,x);
			}
			else
			{
				generateInput(x,inputFileName,quitStatus,printStatus,1);
				writeFileSequence(fileSequence,inputFileName,1,x);
			}
			inputFile.open(inputFileName);
		}
		else if (choice == 1) //if manual
		{
			percentageBreak = 0; //reset the progress bar breakpoint
			printMessage(outputFileName); //print the message
			cin >> inputFileName; //take file name from user
			if (strcasecmp(inputString.c_str(),"quit") == 0 || inputFileName.compare("exit") == 0 || inputFileName.compare("stop") == 0 || inputFileName.compare("return") == 0)
			{
				cout << "Quit" << endl;
				outputFile << "Quit" << endl;
				/*//store timestamp in output file*/
				now = time(0);
				timestamp = ctime(&now);
				outputFile << "Execution ended at: " << timestamp << endl;
				
				//performance evaluation part
				cout << endl << endl << "Want to evaluate performance with comparison to BST and AVLT? (Y/N)" << endl;
				cin >> inputString;
				if (inputString.compare("Y") == 0 || inputString.compare("y") == 0) //if yes
				{
					treap.evaluatePerformance();
					ofstream commands;
					commands.open(evaluationFile);
					/*add the required commands for BST and AVLT execution*/
					if (os == 1)
					{
						commands << "cd BST" << endl;
						commands << "g++ bst.cpp" << endl;
						commands << "./a.out " << fileType << " " << printFileName << " " << outputFileName << endl;
						commands << "cd .." << endl;
						commands << "cd AVLT" << endl;
						commands << "g++ avlt.cpp" << endl;
						commands << "./a.out " << fileType << " " << printFileName << " " << outputFileName << endl;
					}
					else if (os == 0)
					{
						commands << "cd BST" << endl;
						commands << "g++ bst.cpp" << endl;
						commands << "a.exe " << fileType << " " << printFileName << " " << outputFileName << endl;
						commands << "cd.." << endl;
						commands << "cd AVLT" << endl;
						commands << "g++ avlt.cpp" << endl;
						commands << "a.exe " << fileType << " " << printFileName << " " << outputFileName << endl;
					}
					commands.close();
				}
				else //if no
				{
					/*reset the evaluation file*/
					ofstream commands;
					commands.open(evaluationFile);
					commands << endl;
					commands.close();
					//treap.storeKeysInFile();
				}
				cout << endl <<  "Want to generate images? (Y/N)" << endl;
				cin >> inputString;
				if (inputString.compare("Y") == 0 || inputString.compare("y") == 0)
					generatePNG(os); //generate images

				/*Run performance evaluation before quit*/
				runEvaluationFile(os);

				outputFile.close();
				return 0;
			}
			else if (inputFileName.compare("image") == 0 || inputFileName.compare("view") == 0 || inputFileName.compare("print") == 0 || inputFileName.compare("visualize") == 0 || inputFileName.compare("run") == 0 || inputFileName.compare("picture") == 0)
			{
				generatePNG(os);
				cout << "Images generated" << endl;
				outputFile << "Images generated" << endl;
				continue;
			}
			if (isBegin)
			{
				isBegin = false;
				writeFileSequence(fileSequence,inputFileName,0,-1);
			}
			else writeFileSequence(fileSequence,inputFileName,1,-1);
			inputFile.open(inputFileName); //open input file
		}
		else
		{
			cout << "Try again!" << endl;
			continue;
		}

		//store timestamp in output file
		now = time(0);
		timestamp = ctime(&now);
		outputFile << "Execution started at: " << timestamp << endl;

		cout << endl << endl << "Executing" << endl;
		count = 0;

		while (inputFile >> inputString) //till the input file has more lines
		{
			outputFile << endl << inputString << endl;

			/*Progress bar implementation*/
			if (percentageBreak >= 10) //if more than 10 operations fall under 1% of execution
			{
				++count; //increment count
				if (count%percentageBreak == 0) //when reminder is 0
				{
					cout << "\r"; //move to the beginning of the line
					/*print the progress*/
					i = 0;
					cout << "[";
					for (i = percentageBreak; i <= count; i += percentageBreak)
						cout << "|";
					for (; i <= nop; i += percentageBreak)
						cout << " ";
					cout << "]" << (count/percentageBreak); //print the percentage
				}
			}

			/*execution*/
			//if (inputString.compare("insert") == 0)
			if(strcasecmp(inputString.c_str(),"insert") == 0)
			{
				inputFile >> inputString;
				x = stoi(inputString);
				outputFile << x << endl << "Inserting " << x << endl << endl; //write operation details to output file
				try {
				treap.insert(x); //call insert function
				}catch(char const * message) //catch the thrown exception and print into both console and output file
				{
					//cout << message << endl;
					outputFile << message << endl << endl;
				}
			}
			//else if (inputString.compare("delete") == 0)
			else if(strcasecmp(inputString.c_str(),"delete") == 0)
			{
				inputFile >> inputString;
				x = stoi(inputString);
				outputFile << x << endl << "Deleting " << x << endl << endl; //write operation details to output file
				try{
				treap.deleteX(x); //call delete function
				}catch(const char * message) //catch the thrown exception and print into both console and output file
				{
					//cout << message << endl;
					outputFile << message << endl << endl;
				}
			}
			//else if (inputString.compare("search") == 0)
			else if(strcasecmp(inputString.c_str(),"search") == 0)
			{
				inputFile >> inputString;
				x = stoi(inputString);
				outputFile << x << endl << "Searching " << x << endl; //write operation details to output file
				isXPresent = treap.search(x); //call search function
				if (!isXPresent) //if result is false print the same to both console and output file
				{
					cout << x << " is not present" << endl;
					outputFile << x << " is not present" << endl << endl;
				}
				else //otherwise also print to both console and output file
				{
					cout << x << " is present" << endl;
					outputFile << x << " is present" << endl << endl;
				}
			}
			else if (strcasecmp(inputString.c_str(),"print") == 0 || inputString.compare("image") == 0|| inputString.compare("view") == 0|| inputString.compare("run") == 0|| inputString.compare("visualize") == 0|| inputString.compare("picture") == 0)
			{
				outputFile << "Printing treap with file name- " << printFileName << fileCount << ".png" << endl;
				outputFile << "Graphviz file can be found with file name- " << printFileName << fileCount << ".gv" << endl << endl;
				treap.print(printFileName.c_str()); //call print tree function
			}
			else if (strcasecmp(inputString.c_str(),"quit") == 0 || inputString.compare("exit") == 0 || inputString.compare("stop") == 0 || inputString.compare("return") == 0)
			{
				//cout << "Quit" << endl; //print to console
				outputFile << endl << "Quit" << endl << endl; //print to output file

				/*//store timestamp in output file*/
				now = time(0);
				timestamp = ctime(&now);
				outputFile << "Execution ended at: " << timestamp << endl;

				//performance evaluation part
				cout << endl << endl << "Want to evaluate performance with comparison to BST and AVLT? (Y/N)" << endl;
				cin >> inputString;
				if (inputString.compare("Y") == 0 || inputString.compare("y") == 0) //if yes
				{
					treap.evaluatePerformance();
					ofstream commands;
					commands.open(evaluationFile);
					/*add required command for BST and AVLT execution*/
					if (os == 1)
					{
						commands << "cd BST" << endl;
						commands << "g++ bst.cpp" << endl;
						commands << "./a.out " << fileType << " " << printFileName << " " << outputFileName << endl;
						commands << "cd .." << endl;
						commands << "cd AVLT" << endl;
						commands << "g++ avlt.cpp" << endl;
						commands << "./a.out " << fileType << " " << printFileName << " " << outputFileName << endl;
					}
					else if (os == 0)
					{
						commands << "cd BST" << endl;
						commands << "g++ bst.cpp" << endl;
						commands << "a.exe " << fileType << " " << printFileName << " " << outputFileName << endl;
						commands << "cd.." << endl;
						commands << "cd AVLT" << endl;
						commands << "g++ avlt.cpp" << endl;
						commands << "a.exe " << fileType << " " << printFileName << " " << outputFileName << endl;
					}
					commands.close();
				}
				else //if no
				{
					/*reset the evaluation file*/
					ofstream commands;
					commands.open(evaluationFile);
					commands << endl;
					commands.close();
					//treap.storeKeysInFile();
				}
				cout << endl << "Want to generate images? (Y/N)" << endl;
				cin >> inputString;
				if (inputString.compare("Y") == 0 || inputString.compare("y") == 0)
					generatePNG(os); //generate images


				/*Run performance evaluation before quit*/
				runEvaluationFile(os);

				outputFile.close();
				return 0;
			}
			else
			{
				cout << "Invalid Input! Please try again!" << endl;
				outputFile << "Invalid Input! Please try again!" << endl;
			}
		}

		/*//store timestamp in output file*/
		now = time(0);
		timestamp = ctime(&now);
		outputFile << "Execution ended at: " << timestamp << endl << endl << endl << endl ;
		inputFile.close(); //close input file
	}
	outputFile.close(); //close output file
	return 0;
}