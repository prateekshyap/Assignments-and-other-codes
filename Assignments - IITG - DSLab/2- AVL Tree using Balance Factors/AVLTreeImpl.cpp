using namespace std;

//inbuilt header files
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<exception>
#include<unordered_map>
#include<ctime>

//header files created for various tasks
#include"nodes.h" // contains all the node structures
#include"datastructures.h" //contains all the data structures
/*next 3 contain the functions for respective data structures*/
#include"queue.h"
#include"stack.h"
#include"avlt.h"
#include"functions.h" //contains other functions

extern int fileCount, fileType; //external variables
extern string color; //external variable

int main()
{
	/*choice stores the choice of operation by the user
	x stores the data given by user
	os stores the type of os being used*/
	int choice = 0, x = 0, os = -1;
	AVLTree tree; //tree contains the main tree
	bool isXPresent = false; //stores whether a searched value is present or not
	/*inputFileName stores the input file name
	outputFileName stores the output file name
	timestamp stores the current timestamp in string format*/
	string inputFileName = "", outputFileName = "output.txt", timestamp = "";
	time_t now; //stores the current time
	ifstream inputFile; //input file stream
	ofstream outputFile; //output file stream

	//deciding the type of os being used
	cout << "Enter a number(0 for Windows /1 for Linux)-" << endl;
	cin >> os;
	fileType = os;
	fileCount = 0; //initializing fileCount

	outputFile.open(outputFileName); //open the output file

	while (true) //run till it hits quit (option 5)
	{		
		printMessage(); //print the message
		cin >> inputFileName; //take file name from user
		if (inputFileName.compare("quit") == 0 || inputFileName.compare("exit") == 0 || inputFileName.compare("stop") == 0 || inputFileName.compare("return") == 0) return 0;

		inputFile.open(inputFileName); //open input file

		//store timestamp in output file
		now = time(0);
		timestamp = ctime(&now);
		outputFile << "Execution started at: " << timestamp << endl;

		while (inputFile >> choice) //till input file has more lines
		{
			outputFile << endl << choice << endl; //write user's choice to the output file
			switch (choice) //switch choice
			{
				case 1: //insertion
					inputFile >> x; //read x value from input file
					outputFile << x << endl << "Inserting " << x << endl << endl; //write operation details to output file
					try {
					tree.insert(x); //call insert function
					}catch(char const * message) //catch the thrown exception and print into both console and output file
					{
						cout << message << endl;
						outputFile << message << endl << endl;
					}
					break;

				case 2: //delete
					inputFile >> x; //read x value from input file
					outputFile << x << endl << "Deleting " << x << endl << endl; //write operation details to output file
					try{
					tree.deleteK(x); //call delete function
					}catch(const char * message) //catch the thrown exception and print into both console and output file
					{
						cout << message << endl;
						outputFile << message << endl << endl;
					}
					break;

				case 3: //searching
					inputFile >> x; //read x value from input file
					outputFile << x << endl << "Searching " << x << endl; //write operation details to output file
					isXPresent = tree.search(x); //call search function
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
					break;

				case 4: //print tree
					/*print file details into output file*/
					outputFile << "Printing tree with file name- struct" << fileCount << ".png" << endl;
					outputFile << "Graphviz file can be found with file name- bstStructure" << fileCount << ".gv" << endl << endl;
					tree.print(); //call print tree function
					generatePNG(os); //generate images
					break;

				case 5: //quit from execution
					cout << "Quit" << endl; //print to console
					outputFile << "Quit" << endl << endl; //print to output file
					/*//store timestamp in output file*/
					now = time(0);
					timestamp = ctime(&now);
					outputFile << "Execution ended at: " << timestamp << endl;
					return 0;

				default: //default case
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