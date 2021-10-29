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
#include<cstdarg>
#include<bits/stdc++.h>

//header files created for various tasks
#include"datastructures.h" //contains all the data structures
#include"functions.h" //contains all functions

extern int fileCount, fileType;//, low, high, ratio; //external variables
extern ofstream outputFile;
extern string printFileName;

int main()
{
	/*modeChoice stores the choice of mode by the user
	os stores the type of os being used*/
	int modeChoice = 0, os = -1;
	string timestamp = "", outputFileName = "", inputString = "";
	time_t now; //stores the current time

	//deciding the type of os being used
	cout << "Enter a number(0 for Windows / 1 for Linux)-" << endl;
	cin >> os;
	if (os == 0)
	{
		//remove all existing graphviz and image files
		std :: system("del *.gv");
		std :: system("del *.png");
	}
	else if (os == 1)
	{
		//remove all existing graphviz and image files
		std :: system("rm *.gv");
		std :: system("rm *.png");
	}
	fileType = os; //initializing fileType
	fileCount = 0; //initializing fileCount
	//deciding the user given file name
	cout << "Enter universal file name to generate images(Don't write extension names)-" << endl;
	cin >> printFileName;

	outputFileName.append(printFileName);
	outputFileName.append("Output.txt");
	outputFile.open(outputFileName); //open the output file

	now = time(0);
	timestamp = ctime(&now);
	outputFile << "Execution started at: " << timestamp << endl;

	while (true) //run till it hits quit
	{
		outputFile << "Mode selection" << endl << endl;
		printMessage(0,outputFileName); //choosing mode
		cin >> modeChoice;

		switch (modeChoice)
		{
			case 1: //build
				outputFile << "Entered Build mode" << endl << endl;
				executeBuildMode();
				outputFile << endl << "Exited Build mode" << endl << endl;
				break;

			case 2: //operations
				outputFile << "Entered Operations mode" << endl << endl;
				executeOperationsMode();
				outputFile << endl << "Exited Operations mode" << endl << endl;
				break;

			case 3: //generate images
				generatePNG(os);
				break;

			case 4: //quit
				cout << "Quit" << endl; //print to console
				outputFile << endl << "Quit" << endl << endl; //print to output file

				//store timestamp in output file
				now = time(0);
				timestamp = ctime(&now);
				outputFile << "Execution ended at: " << timestamp << endl;

				//image generation part
				cout << endl << "Want to generate images? (Y/N)" << endl;
				cin >> inputString;
				if (inputString.compare("Y") == 0 || inputString.compare("y") == 0)
					generatePNG(os); //generate images

				//quit
				outputFile.close();
				return 0;

			default:
				cout << "Invalid input! Please try again!" << endl;
		}
	}


	outputFile.close(); //close output file
	return 0;
}