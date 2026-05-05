#include <iostream>
#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <cctype>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

#include <custom_exceptions.h>

string convertToLowerCase(const string &s)
{
    try
    {

        if (s.empty())
        {
            throw ExceptionInFunction(__FUNCTION__, "String to convert to lowercase is empty!");
        }
        string result = s;
        transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                  { return tolower(c); });

        cout << "Original String:" << s << "String converted to lowerCase is:" << result << endl;
        return result;
    }
    catch (ExceptionInFunction &e)
    {
        cout << e.what() << endl;
        throw;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
        throw;
    }
}

bool findString(const string &text, const string &pattern)
{
    // cout << "In here" << __FUNCTION__ << endl;
    try
    {
        if (text.empty())
        {
            throw ExceptionInFunction(__FUNCTION__, "String is empty!");
        }

        if (text.find(pattern) != string::npos)
        {
            return true;
        }
        return false;
        // cout << "Out here" << __FUNCTION__ << endl;
    }
    catch (ExceptionInFunction &e)
    {
        cout << e.what() << endl;
        throw;
    }
    catch (exception &e)
    {
        cout << __FUNCTION__ << ":" << e.what() << endl;
        throw;
    }
}

bool validate_file(const std::string &path)
{
    // cout << "In here" << __FUNCTION__ << endl;
    try
    {
        fs::path p(path);

        // 1. Check if file exists
        if (!fs::exists(p))
        {
            throw ExceptionInFunction(__FUNCTION__, "File does not exist: " + path);
        }

        // 2. Check if it is a directory
        if (fs::is_directory(p))
        {
            throw ExceptionInFunction(__FUNCTION__, "Path is a directory, not a file: " + path);
        }

        // 3. Check permissions (e.g., Read permission)
        fs::perms prms = fs::status(p).permissions();
        if ((prms & fs::perms::owner_read) == fs::perms::none)
        {
            throw ExceptionInFunction(__FUNCTION__, "Missing read permissions for: " + path);
        }

        // 4. Check Extension
        if (p.extension() != ".txt")
        {
            throw ExceptionInFunction(__FUNCTION__, "Extension is Different");
        }
        // cout << "Out here" << __FUNCTION__ << endl;
        return true;
    }
    catch (exception &e)
    {
        throw;
    }
}

ifstream openFile(const string &path)
{
    // cout << "In here" << __FUNCTION__ << endl;
    try
    {
        if (path.empty())
        {
            throw ExceptionInFunction(__FUNCTION__, "Path is empty!");
        }
        fs::path p(path);

        if (!validate_file(path))
        {
            throw ExceptionInFunction(__FUNCTION__, "File Path is not valid");
        }

        ifstream f(path);

        // cout << "Out here" << __FUNCTION__ << endl;

        return f;
    }
    catch (ExceptionInFunction &e)
    {
        cout << e.what() << endl;
    }
    catch (exception &e)
    {
        cout << __FUNCTION__ << ":" << e.what() << endl;
    }
}

vector<string> returnLine(const string &path, const string &pattern, const bool isCaseInsensitive, const bool isDir)
{
    // cout << "In here" << __FUNCTION__ << endl;
    ifstream f = openFile(path);
    // cout << "Reached 133 in " << __FUNCTION__ << endl;

    vector<string> matched_lines;
    if (f.is_open())
    {
        // cout << "Reached 136 in " << __FUNCTION__ << endl;
        string line;

        while (getline(f, line))
        {
            // cout << "Reached 141 in " << __FUNCTION__ << endl;
            string original = line;
            if (isCaseInsensitive)
                line = convertToLowerCase(line);

            // cout << "Line is:" << line << endl;
            // cout << "Pattern is:" << pattern << endl;

            if (findString(line, pattern))
            {
                // cout << line << endl;
                if (isDir)
                {
                    string pathAndLine = fs::path(path).string() + ":" + original;
                    matched_lines.push_back(pathAndLine);
                }
                else
                    matched_lines.push_back(original);
            }
        }

        return matched_lines;
    }
    else
    {
        cout << "Null Ptr returned in " << __FUNCTION__ << endl;
    }

    // cout << "Out here" << __FUNCTION__ << endl;
}

vector<string> stdInput(const string &pattern, const bool isCaseInsensitive, istream &in, ostream &out)
{
    try
    {
        string line;
        vector<string> v;
        while (getline(in, line))
        { // Reads from 'in' (cin by default)
            string original = line;
            if (isCaseInsensitive)
                line = convertToLowerCase(line);

            // cout << "Line is:" << line << endl;
            // cout << "Pattern is:" << pattern << endl;

            if (findString(line, pattern))
            {
                // cout << "Line is: " << original << endl;
                v.push_back(original);
            }
        }
        // out << "\n\n";
        // for (const auto &s : v)
        // {
        //     out << s << endl; // Writes to 'out' (cout by default)
        // }
        return v;
    }
    catch (exception &e)
    {
        out << e.what() << endl;
    }
}

void writeToFile(const string &path, vector<string> &ans)
{
    try
    {
        cout << "Inside " << __FUNCTION__ << endl;

        if (!(fs::exists(fs::path(path))))
        {
            throw ExceptionInFunction(__FUNCTION__, "File Already Exists");
        }
        cout << "Inside " << __FUNCTION__ << "183" << endl;
        ofstream of(path);
        if (of.is_open())
        {
            for (string ele : ans)
            {
                of << ele;
            }
            of.close();
        }
        else
        {
            cout << "File not Opened: " << endl;
        }
    }
    catch (ExceptionInFunction &e)
    {
        cout << e.what() << endl;
        throw;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
        throw;
    }
}

bool checkIfDir(const string &path)
{
    try
    {
        if (path.empty())
        {
            throw ExceptionInFunction(__FUNCTION__, "Empty Path passed!");
        }

        fs::path p(path);

        if (!fs::exists(p))
        {
            return false;
            // throw ExceptionInFunction(__FUNCTION__, "Path does not exist!");
        }

        if (!fs::is_directory(p))
        {
            return false;
            // throw ExceptionInFunction(__FUNCTION__, "Not a directory");
        }

        if (fs::directory_iterator(p) == fs::end(fs::directory_iterator(p)))
        {
            throw ExceptionInFunction(__FUNCTION__, "Empty Directory");
        }

        return true;
    }
    catch (ExceptionInFunction &e)
    {
        cout << e.what() << endl;
        throw;
    }
    return false;
}

vector<string> returnLineInDir(const string &path, const string &pattern, const bool isCaseInsensitive)
{
    try
    {
        fs::path p(path);
        vector<string> ans;
        bool isDir = true;
        for (auto &file_path : fs::recursive_directory_iterator(p))
        {
            vector<string> tmp;
            tmp = returnLine(path, pattern, isCaseInsensitive, isDir);
            for (auto &ele : tmp)
            {
                ans.push_back(ele);
            }
        }

        return ans;
    }
    catch (ExceptionInFunction &e)
    {
        cout << e.what() << endl;
        throw;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
        throw;
    }
}
