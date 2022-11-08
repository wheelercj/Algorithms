#include <string>
#include <iostream>
#include "sorting.h"
using namespace std;


int main()
{
	string choice = "";
	while (choice != "2")
	{
		cout << "\n"
			"\n main menu"
			"\n ---------"
			"\n 1. sorting"
			"\n 2. exit"
			"\n> ";
		cin >> choice;
		if (choice == "1")
			manual_sorting_test();
	}
	cout << endl;
	system("pause");
	return 0;
}
