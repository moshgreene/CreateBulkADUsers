
#include <fstream>
#include <iostream>
#include <atlbase.h>
#include <vector>
#include <array>
#include <string>

using namespace std;

std::vector<CComBSTR>* GetFirstNameVector()
{
	ifstream file("firstNames.txt");
	vector<CComBSTR>* firstNameVector = new std::vector<CComBSTR>();
	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			firstNameVector->push_back(CComBSTR(line.c_str()));
		}
		file.close();
	}


	return firstNameVector;
}