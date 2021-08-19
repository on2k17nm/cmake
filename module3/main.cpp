#include <iostream>

#include "add.h"
#include "divide.h"
#include "print.h"

using namespace std;

int main(int argc, char *argv[]) {
	double first_no, second_no, res; 

	cout << "Enter first positive number : ";
	cin >> first_no; 
	cout << "Enter second positive number : ";
	cin >> second_no; 
	
	res = add (first_no, second_no); 
	print("addition", res); 
	
	res = divide(first_no, second_no); 
	if (res != -1) 
		print("division", res); 
	else
		cout << "Error : Divide by Zero !" << endl;

	return 0;
}
