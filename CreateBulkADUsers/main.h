#pragma once


#pragma comment(lib, "ActiveDS.lib")
#pragma comment(lib, "Adsiid.lib")

std::array<const std::wstring, 50> g_States = { L"Alabama", L"Alaska", L"Arizona", L"Arkansas", L"California", L"Colorado", L"Connecticut", L"Delaware", L"Florida",
                        L"Georgia", L"Hawaii", L"Idaho", L"Illinois", L"Indiana", L"Iowa", L"Kansas", L"Kentucky", L"Louisiana", L"Maine", L"Maryland",
                        L"Massachusetts", L"Michigan", L"Minnesota", L"Mississippi", L"Missouri", L"Montana", L"Nebraska", L"Nevada", L"New Hampshire",
                        L"New Jersey", L"New Mexico", L"New York", L"North Carolina", L"North Dakota", L"Ohio", L"Oklahoma", L"Oregon", L"Pennsylvania",
                        L"Rhode Island", L"South Carolina", L"South Dakota", L"Tennessee", L"Texas", L"Utah", L"Vermont", L"Virginia", L"Washington",
                        L"West Virginia", L"Wisconsin", L"Wyoming" };
std::array<const std::wstring, 10> g_Cities = { L"Washington", L"Springfield", L"Lexington", L"Clinton", L"Greenville",L"Franklin", L"Madison", L"Salem", L"Georgetown",L"Jackson" };

std::vector<CComBSTR>* GetTextVectorFromFile(std::wstring fileName);
//std::vector<CComBSTR>* GetStatesVector();
//std::vector<CComBSTR>* GetSurnameVector();
int GetRandomVectorIndex(int size);

bool GetDefaultNamingContext(std::wstring& dnc);
bool CreateOrgUnitSubtree(std::wstring defaultNamingContext, std::wstring rootOrgUnitName = L"GiganticDIT");
bool CreateUser(std::wstring organizationalUnit, BSTR firstName, BSTR lastName);
std::vector<std::wstring>* GetCityStatesOUPathVector(std::wstring rootOU);
std::wstring CreateOrgUnit(std::wstring name, std::wstring parent);
bool OUExists(const std::wstring& ouPath);
