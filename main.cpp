#include <iostream>
#include <ostream>
#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower
using namespace std;

#include "utils.h"

// ./mygrep -i search_string filename.txt -o output.txt

int main(const int argc, const char *argv[])
{
    cout << "Args Count is: " << argc << endl;
    vector<string> ans;
    // if (argc == 2)
    // {
    // }

    // if (argc >= 3)
    // {
    //     ans = returnLine(argv[2], argv[1]);
    //     if (argc == 5)
    //     {
    //         writeToFile(argv[4], ans);
    //         exit(1);
    //     }
    // }

    bool isCaseInsensitive = false;
    bool isOutputFilePresent = false;
    bool isDir = false;
    string ip_path = "";
    string op_path = "";
    string pattern = "";

    for (int i = 1; i < argc; i++)
    {
        string tmp = argv[i];
        // if(i == 0) continue;
        cout << "Argv:" << argv[i] << endl;
        if (tmp == "-i")
        {
            isCaseInsensitive = true;
        }
        else if (tmp == "-o")
        {
            isOutputFilePresent = true;
        }
        // cout<<tmp.substr
        else if (ip_path.size() == 0 && tmp.size() >= 4 && tmp.substr(tmp.size() - 4) == ".txt")
        {
            ip_path = tmp;
        }

        else if (ip_path.size() == 0 && checkIfDir(tmp))
        {
            ip_path = tmp;
            isDir = true;
        }

        else if (isOutputFilePresent && ip_path.size() != 0 && tmp.substr(tmp.size() - 4) == ".txt" && op_path.size() == 0)
        {
            op_path = tmp;
        }

        else
        {
            pattern = tmp;
        }
    }

    cout << isCaseInsensitive << endl;
    cout << isOutputFilePresent << endl;
    cout << ip_path << endl;
    cout << op_path << endl;
    cout << pattern << endl;

    if (!isOutputFilePresent && ip_path.size() == 0)
    {
        if (isCaseInsensitive) // convert everything to lowercase
            pattern = convertToLowerCase(pattern);

        ans = stdInput(pattern, isCaseInsensitive, cin, cout);
    }
    else if (ip_path.size() > 0 && pattern.size() > 0)
    {
        if (isCaseInsensitive) // convert everything to lowercase
            pattern = convertToLowerCase(pattern);

        if(isDir){
            ans = returnLineInDir(ip_path, pattern, isCaseInsensitive);
        }else{
            ans = returnLine(ip_path, pattern, isCaseInsensitive);
        }

        if (isOutputFilePresent && op_path.size() > 0)
        {
            writeToFile(op_path, ans);
            exit(1);
        }
    }
    cout << endl;
    printVec(ans);
}