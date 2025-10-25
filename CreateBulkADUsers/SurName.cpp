
#include <fstream>
#include <iostream>
#include <atlbase.h>
#include <vector>
#include <array>
#include <string>

using namespace std;
std::vector<CComBSTR>* GetSurnameVector() {
	ifstream file("SurNames.txt");
	vector<CComBSTR>* surnameVector = new std::vector<CComBSTR>();
	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			surnameVector->push_back(CComBSTR(line.c_str()));
		}
		file.close();
	}

	//std::vector<CComBSTR>* surnameVector = new std::vector<CComBSTR>(SurNames.begin(), SurNames.end());
	return surnameVector;
}