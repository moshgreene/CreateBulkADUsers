#include <string>
#include <vector>
#include <array>


using namespace std;



std::vector<wstring>* GetCityStatesOUPathVector(wstring rootOU)
{
	std::array<const wstring, 50> States = { L"Alabama", L"Alaska", L"Arizona", L"Arkansas", L"California", L"Colorado", L"Connecticut", L"Delaware", L"Florida",
							L"Georgia", L"Hawaii", L"Idaho", L"Illinois", L"Indiana", L"Iowa", L"Kansas", L"Kentucky", L"Louisiana", L"Maine", L"Maryland",
							L"Massachusetts", L"Michigan", L"Minnesota", L"Mississippi", L"Missouri", L"Montana", L"Nebraska", L"Nevada", L"New Hampshire",
							L"New Jersey", L"New Mexico", L"New York", L"North Carolina", L"North Dakota", L"Ohio", L"Oklahoma", L"Oregon", L"Pennsylvania",
							L"Rhode Island", L"South Carolina", L"South Dakota", L"Tennessee", L"Texas", L"Utah", L"Vermont", L"Virginia", L"Washington",
							L"West Virginia", L"Wisconsin", L"Wyoming" };

	std::array<const wstring, 10> Cities = { L"Washington", L"Springfield", L"Lexington", L"Clinton", L"Greenville",L"Franklin", L"Madison", L"Salem", L"Georgetown",L"Jackson" };
	//std::vector<CComBSTR>*pStates = new std::vector<CComBSTR>(States.begin(), States.end());

	std::vector<wstring>* cityState = new std::vector<wstring>();
	for (const auto& state : States) {
		for (const auto& city : Cities) {
			wstring cityStateString{ L"LDAP://OU=" + city + L",OU=" + state + L"," + rootOU };
			cityState->push_back(cityStateString);
		}
	}

	return cityState;
}

