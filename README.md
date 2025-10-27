# CreateBulkADUsers
This utility is for testing purposes only.

This utility creates Active Directory users in bulk to simulate large AD databases. It must not be used in production environments.
It creates 501 OU's using the following OU structure (using the example of contoso.com):
contoso.com
+ GiganticDIT
  + Alabama
    + Clinton
    + Franklin
    + Georgetown
    + Greenville
    + Jackson
    + Lexington
    + Madison
    + Salem
    + Springfield
    + Washington
  + Alaska
  + Arizona
  + ...
  + Wyoming

This utility will randomly creates users in the above OU's. 

## Prerequisites
You must install the latest [Microsoft Visual C++ Redistributable (X64)](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170)
