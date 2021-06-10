#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <stdexcept>
#include "Menu.h"
#include <fstream>

using namespace std;

PyObject* pName = NULL;
PyObject* pModule = NULL;
PyObject* pFunc = NULL;
PyObject* presult = NULL;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);

}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", 2);
	cout << callIntFunc("SquareValue", 5);
	int argc, char* argv[] <-- goes in main()
*/


int main() {
	int menuChoice = 0;
	char quitCmd = 'p';
	string searchItem;
	ifstream inFS; // Input file stream

	// Create a Menu object then call the menu function
	Menu menu;
	
	while (quitCmd != 'q') {
		try {
			menu.PrintMenu();
			
			// Get user input
			cin >> menuChoice;

			switch (menuChoice) {
			case 1:
				CallProcedure("ViewAllItems");
				cout << endl;
				break;

			case 2:
				cout << "Look Up Item: " << endl;
				cin >> searchItem;
				cout << endl;
				cout << callIntFunc("ViewSingleItem", searchItem) << endl;
				cout << endl;
				break;

			case 3:
				cout << "Opening file frequency.dat" << endl << endl;

				inFS.open("frequency.dat");

				if (!inFS.is_open()) {
					throw runtime_error("Could not open file frequency.dat");
				}

				CallProcedure("ViewHistogram");
				inFS.close();
				cout << endl;
				break;

			case 4:
				// Exit program
				cout << "Exiting program, goodbye." << endl;
				quitCmd = 'q';
				break;
			
			default:
				// If user input is invalid, throw runtime error
				if (menuChoice < 1 || menuChoice > 4) {
					throw runtime_error("You must select an option 1, 2, 3, or 4 from the list.");
				}
				break;
			}
		}
		catch (runtime_error& excpt) {
			// Prints the error message passed by throw statement
			cout << excpt.what() << endl;
			cout << "Please try again." << endl;
		}
	}
  
	return 0;
}