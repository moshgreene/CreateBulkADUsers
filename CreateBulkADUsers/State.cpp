#include <atlbase.h>
#include <vector>
#include <array>

std::vector<CComBSTR>* GetStatesVector()
{
    std::array<CComBSTR, 50> States = { CComBSTR(L"Alabama"), CComBSTR(L"Alaska"), CComBSTR(L"Arizona"), CComBSTR(L"Arkansas"), CComBSTR(L"California"), CComBSTR(L"Colorado"), CComBSTR(L"Connecticut"), CComBSTR(L"Delaware"), CComBSTR(L"Florida"),
                            CComBSTR(L"Georgia"), CComBSTR(L"Hawaii"), CComBSTR(L"Idaho"), CComBSTR(L"Illinois"), CComBSTR(L"Indiana"), CComBSTR(L"Iowa"), CComBSTR(L"Kansas"), CComBSTR(L"Kentucky"), CComBSTR(L"Louisiana"), CComBSTR(L"Maine"), CComBSTR(L"Maryland"),
                            CComBSTR(L"Massachusetts"), CComBSTR(L"Michigan"), CComBSTR(L"Minnesota"), CComBSTR(L"Mississippi"), CComBSTR(L"Missouri"), CComBSTR(L"Montana"), CComBSTR(L"Nebraska"), CComBSTR(L"Nevada"), CComBSTR(L"New Hampshire"),
                            CComBSTR(L"New Jersey"), CComBSTR(L"New Mexico"), CComBSTR(L"New York"), CComBSTR(L"North Carolina"), CComBSTR(L"North Dakota"), CComBSTR(L"Ohio"), CComBSTR(L"Oklahoma"), CComBSTR(L"Oregon"), CComBSTR(L"Pennsylvania"),
                            CComBSTR(L"Rhode Island"), CComBSTR(L"South Carolina"), CComBSTR(L"South Dakota"), CComBSTR(L"Tennessee"), CComBSTR(L"Texas"), CComBSTR(L"Utah"), CComBSTR(L"Vermont"), CComBSTR(L"Virginia"), CComBSTR(L"Washington"),
                            CComBSTR(L"West Virginia"), CComBSTR(L"Wisconsin"), CComBSTR(L"Wyoming") };

    std::vector<CComBSTR>* pStates = new std::vector<CComBSTR>(States.begin(), States.end());

    return pStates;
}