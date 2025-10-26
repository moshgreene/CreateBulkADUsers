// CreateBulkADUsers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "framework.h"
#include "main.h"

using namespace std;

int wmain(int argc, wchar_t* argv[])
{
    std::wcout << L"CreateBulkADUsers\n";

    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::cerr << "COM initialization failed." << std::endl;
        return 1;
    }

    wstring defaultNamingContext;
    if (!GetDefaultNamingContext(defaultNamingContext)) {
        CoUninitialize();
        return 1;
    }

    wstring rootOrgUnitName{ L"GiganticDIT" };

    CreateOrgUnitSubtree(defaultNamingContext, rootOrgUnitName);

    std::vector<CComBSTR>* FirstNameVector = GetTextVectorFromFile(L"firstNames.txt");
    //std::vector<CComBSTR>* StateVector = GetStatesVector();
    std::vector<CComBSTR>* SurnameVector = GetTextVectorFromFile(L"surnames.txt");

    wstring rootOrgUnit{ L"OU=" + rootOrgUnitName + L"," + defaultNamingContext};
    std::vector<wstring>* cityStatesCollection = GetCityStatesOUPathVector(rootOrgUnit);

    for (int i = 0;;i++) {
        int randomStateIndex = GetRandomVectorIndex(static_cast<int>(g_States.size()));
        int randomFirstNameIndex = GetRandomVectorIndex(static_cast<int>(FirstNameVector->size()));
        int randomSurnamIndex = GetRandomVectorIndex(static_cast<int>(SurnameVector->size()));
        int randomCityStateIndex = GetRandomVectorIndex(static_cast<int>(cityStatesCollection->size()));

        if (!CreateUser(cityStatesCollection->at(randomCityStateIndex),
            FirstNameVector->at(randomFirstNameIndex),
            SurnameVector->at(randomSurnamIndex))) {
            break;
        }
    }
}

std::wstring CreateOrgUnit(std::wstring name, std::wstring parent)
{
    HRESULT hr;
    IADsContainer* pContainer = nullptr;
    IDispatch* pDisp = nullptr;

    wstring ouPath{ L"OU=" + name + L"," + parent };
    bool bExists = OUExists(ouPath);
    if (bExists) {
        return ouPath;
    }

    // Bind to the parent container (domain root)
    wstring parentPath{ L"LDAP://" + parent };
    hr = ADsGetObject(parentPath.c_str(), IID_IADsContainer, (void**)&pContainer);
    if (FAILED(hr)) {
        std::cerr << "Failed to bind to container." << std::endl;        
        return nullptr;
    }

    // Create the new OU
    wstring ou{ L"OU=" + name };
    hr = pContainer->Create(CComBSTR("organizationalUnit"), CComBSTR(ou.c_str()), &pDisp);
    if (FAILED(hr)) {
        std::cerr << "Failed to create OU." << std::endl;
        pContainer->Release();
        return nullptr;
    }

    // Commit the new OU to the directory
    IADs* pOU = nullptr;
    hr = pDisp->QueryInterface(IID_IADs, (void**)&pOU);
    wstring newOU;
    if (SUCCEEDED(hr)) {
        hr = pOU->SetInfo(); // Saves the OU
        BSTR bstrNewOU;
        pOU->get_ADsPath(&bstrNewOU);
        newOU = bstrNewOU;
        SysFreeString(bstrNewOU);
        if (SUCCEEDED(hr)) {
            std::wcout << L"OU=" << name << L"' created successfully under " << parent << std::endl;
        }
        pOU->Release();
        return newOU;
    }

    // Cleanup
    pDisp->Release();
    pContainer->Release();
}

/// <summary>
/// Determines if an OU already exists
/// </summary>
/// <param name="ouPath"></param>
/// <returns></returns>
bool OUExists(const std::wstring& ouPath) {
    IADs* pOU = nullptr;
    wstring ldapPath{ L"LDAP://" + ouPath };
    HRESULT hr = ADsGetObject(ldapPath.c_str(), IID_IADs, (void**)&pOU);

    if (SUCCEEDED(hr)) {
        pOU->Release();
        pOU = nullptr;
        return true;  // OU exists
    }

    if (hr == HRESULT_FROM_WIN32(ERROR_DS_NO_SUCH_OBJECT)) {
        return false; // OU does not exist
    }

    std::wcerr << L"Error checking OU: HRESULT=" << hr << std::endl;
    return false;
}

/// <summary>
/// This method reads names from a text file and resturns a vector pointer
/// </summary>
/// <param name="fileName"></param>
/// <returns></returns>
std::vector<CComBSTR>* GetTextVectorFromFile(wstring fileName)
{
    wifstream file(fileName);
    //ifstream file()
    vector<CComBSTR>* firstNameVector = new std::vector<CComBSTR>();
    wstring line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            firstNameVector->push_back(CComBSTR(line.c_str()));
        }
        file.close();
    }

    return firstNameVector;
}

std::vector<wstring>* GetCityStatesOUPathVector(wstring rootOU)
{
    std::vector<wstring>* cityState = new std::vector<wstring>();
    for (const auto& state : g_States) {
        for (const auto& city : g_Cities) {
            wstring cityStateString{ L"LDAP://OU=" + city + L",OU=" + state + L"," + rootOU };
            cityState->push_back(cityStateString);
        }
    }

    return cityState;
}

bool CreateUser(wstring organizationalUnit, BSTR firstName, BSTR lastName)
{
    bool results = false;
    IADsContainer* pOU = nullptr;
    IDispatch* pDisp = nullptr;
    IADsUser* pUser = nullptr;

    HRESULT hr = ADsGetObject(organizationalUnit.c_str(), IID_IADsContainer, (void**)&pOU);
    if (FAILED(hr)) {
        std::wcerr << L"Failed to bind to OU:" << organizationalUnit << std::endl;
        return false;
    }

    CComBSTR userCN(L"CN=");
    userCN += firstName;
    userCN += L".";
    userCN += lastName;

    // Create the user object
    hr = pOU->Create(CComBSTR("user"), userCN, &pDisp);
    if (SUCCEEDED(hr)) {
        hr = pDisp->QueryInterface(IID_IADsUser, (void**)&pUser);
        if (SUCCEEDED(hr)) {
            pUser->put_FirstName(CComBSTR(firstName));
            pUser->put_LastName(CComBSTR(lastName));
            pUser->put_Description(CComBSTR("Created via C++ ADSI"));
            pUser->SetInfo(); // Commit to AD
            pUser->Release();
            std::wcout << L" [+] User created successfully:" << userCN.m_str << L" - " << organizationalUnit << std::endl;
        }
        pDisp->Release();
        results = true;
    }
    else {
        std::wcerr << L"Failed to create user object:" << userCN << std::endl;
    }

    pOU->Release();

    return results;
}

bool GetDefaultNamingContext(wstring& dnc)
{
    IADs* pRootDSE = nullptr;
    HRESULT hr = ADsGetObject(L"LDAP://RootDSE", IID_IADs, (void**)&pRootDSE);
    if (SUCCEEDED(hr)) {
        VARIANT var;
        VariantInit(&var);
        hr = pRootDSE->Get(CComBSTR("defaultNamingContext"), &var);
        if (SUCCEEDED(hr)) {
            wprintf(L"Default Naming Context: %s\n", var.bstrVal);
            dnc = var.bstrVal;
        }
        VariantClear(&var);
        pRootDSE->Release();
        return true;
    }
    else {
        std::wcerr << L"Failed to bind to RootDSE." << std::endl;
        return false;
    }
}

/// <summary>
/// Returns a random integer less than size
/// </summary>
/// <param name="size"></param>
/// <returns></returns>
int GetRandomVectorIndex(int size)
{
    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, size - 1);

    // Get a random index
    int randomIndex = dist(gen);

    return randomIndex;
}

/// <summary>
/// This method builds the entire OU structure
/// </summary>
/// <param name="defaultNamingContext"></param>
/// <param name="rootOrgUnitName"></param>
/// <returns></returns>
bool CreateOrgUnitSubtree(wstring defaultNamingContext, wstring rootOrgUnitName)
{
    wstring rootOU = CreateOrgUnit(rootOrgUnitName, defaultNamingContext);

    for (const auto& state : g_States) {
        wstring stateOU = CreateOrgUnit(state, rootOU);
        for (const auto& city : g_Cities) {
            wstring cityOU = CreateOrgUnit(city, stateOU);
        }
    }
    return 0;
}