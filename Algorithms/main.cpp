#include <string>
#include <iostream>
#include "LinkedList.h"
#include "sorting.h"
using namespace std;


int main()
{
	string choice = "";
	while (choice != "3")
	{
		cout << "\n"
			"\n main menu"
			"\n ---------"
			"\n 1. sorting and searching"
			"\n 2. linked lists"
			"\n 3. exit"
			"\n> ";
		cin >> choice;
		if (choice == "1")
			manual_sorting_test();
		else if (choice == "2")
			manual_linked_list_test();
	}
	cout << endl;
	system("pause");
	return 0;
}
