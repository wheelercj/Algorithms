#include <iostream>
#include "LinkedList.h"


void manual_linked_list_test()
{
	LinkedList<std::string> list;
	list.append("a");
	list.append("b");
	list.append("c");
	if (auto index = list.find("hey"))
		std::cout << "\n index: " << *index;
	else
		std::cout << "\n \"hey\" is not in the list";
}
