#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
using namespace std;

bool findString(const string &text, const string &pattern);
bool validate_file(const std::string &path);
ifstream openFile(const string &path);
// vector<string> returnLine(const string &path, const string &pattern);
vector<string> returnLine(const string &path, const string &pattern, const bool isCaseInsensitive);
// vector<string> stdInput(const string &pattern, istream &in , ostream &out );
vector<string> stdInput(const string &pattern, const bool isCaseInsensitive, istream &in = std::cin, ostream &out = std::cout);
void writeToFile(const string &path, vector<string> &ans);
string convertToLowerCase(const string &s);

template <typename t>
void printVec(vector<t> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

#endif