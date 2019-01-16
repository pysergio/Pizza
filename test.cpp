#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>

using namespace std;

main(int argc, char const *argv[])
{
    string str = "somefile.in";

    cout << str.substr(str.length() - 3);

    return 0;
}
