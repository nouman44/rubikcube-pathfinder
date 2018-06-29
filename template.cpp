#include <iostream>
#include "template.h"

using namespace std;

void Menu::RunProgram()
{
	int choice;
	char *filename = new char[50];
	cout << "DEPTH FIRST SEARCH ALGORITHM PROGRAM" << endl << endl;

	cout << "1: To read a board of characters" << endl;
	cout << "2: To read a board of integers" << endl;
	cout << "3: To read a board of floating numbers" << endl;
	cout << "Enter choice: ";
	cin >> choice;
	cout << endl;

	switch (choice)
	{
		case 1:
			cout << "Enter filename to read character initial and goal states (charfile.txt): ";
			cin >> filename;
			Gchar.ReadStatesFromFile(filename);
			cout << endl;
			Gchar.DepthFirstSearchAlgo();
			break;
		case 2:
			cout << "Enter filename to read integer initial and goal states (intfile.txt): ";
			cin >> filename;
			Gint.ReadStatesFromFile(filename);
			cout << endl;
			Gint.DepthFirstSearchAlgo();
			break;
		case 3:
			cout << "Enter filename to read float initial and goal states (floatfile.txt): ";
			cin >> filename;
			Gfloat.ReadStatesFromFile(filename);
			cout << endl;
			Gfloat.DepthFirstSearchAlgo();
			break;
		default:
			cout << "Please enter correct choice!";
	}
}
