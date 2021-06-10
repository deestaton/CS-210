#include <string>
#include <iostream>
#include "Menu.h"

using namespace std;

Menu::Menu() {}

void Menu::PrintMenu() {
	cout << string(31, '*') << endl;
	cout << string(7, '*') << "                 " << string(7, '*') << endl;
	cout << string(7, '*') << "  Corner Grocer  " << string(7, '*') << endl;
	cout << string(7, '*') << "                 " << string(7, '*') << endl;
	cout << string(31, '*') << endl;
	cout << "  What Would You Like To Do?" << endl;
	cout << string(31, '=') << endl;
	cout << "[1] - View All Items Purchased" << endl;
	cout << "[2] - Search Item" << endl;
	cout << "[3] - Purchase Statistics" << endl;
	cout << "[4] - Exit Program" << endl;
	cout << endl;
}