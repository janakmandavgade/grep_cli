#include <iostream>
#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
namespace fs = std::filesystem;

#include <custom_exceptions.h>

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
    }
    catch (exception &e)
    {
        cout << __FUNCTION__ << ":" << e.what() << endl;
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
        if(p.extension() != ".txt"){
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

// ifstream* openFile(string &path){
//     try{
//         if(path.empty()){
//             throw ExceptionInFunction(__FUNCTION__, "Path is empty!");
//         }
//         fs::path p(path);

//         if(!validate_file(path)){
//             throw ExceptionInFunction(__FUNCTION__, "File Path is not valid");
//         }

//         ifstream f(path);

//         return &f;

//     }catch(ExceptionInFunction& e){
//         cout<<e.what()<<endl;
//     }
//     catch(exception &e){
//         cout<<__FUNCTION__ << ":" << e.what()<< endl;
//     }
// }

void returnLine(const string &path, const string &pattern)
{
    // cout << "In here" << __FUNCTION__ << endl;
    ifstream f = openFile(path);
    // cout << "Reached 133 in " << __FUNCTION__ << endl;
    if (f.is_open())
    {
        // cout << "Reached 136 in " << __FUNCTION__ << endl;
        string line;

        while (getline(f, line))
        {
            // cout << "Reached 141 in " << __FUNCTION__ << endl;
            if (findString(line, pattern))
            {
                cout << line << endl;
            }
        }
    }
    else
    {
        cout << "Null Ptr returned in " << __FUNCTION__ << endl;
    }

    // cout << "Out here" << __FUNCTION__ << endl;
}