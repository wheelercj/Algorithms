#include <string>
#include <iostream>
#include "sorting.h"
using namespace std;


int main()
{
	string choice = "";
	while (choice != "3")
	{
		cout << "\n"
			"\n 1. run algorithms once"
			"\n 2. run a sorting algorithm many times"
			"\n 3. exit"
			"\n> ";
		cin >> choice;
		if (choice == "1")
			manual_test();
		else if (choice == "2")
			automatic_test();
	}
	cout << endl;
	system("pause");
	return 0;
}
