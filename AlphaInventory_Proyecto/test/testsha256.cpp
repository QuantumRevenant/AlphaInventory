#include <iostream>
#include <string>
#include <vector>
#include "../controller/Encrypter/sha256.cpp"

using namespace std;

/*

*/

int main(int argc, char *argv[])
{
    string value1,value2;
    cin>>value1;
    value2=sha256(value1);
    cout<<value2;
    
    return 0;
}