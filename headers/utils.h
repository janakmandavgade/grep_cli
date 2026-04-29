#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
using namespace std;

bool findString(const string &text, const string &pattern);
bool validate_file(const std::string &path);
ifstream *openFile(const string &path);
void returnLine(const string &path, const string &pattern);

#endif