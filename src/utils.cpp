#include <iostream>
#include <exception>
using namespace std;

#include <custom_exceptions.h>

bool findString(string &text, string& pattern){
    try{
        if(text.empty()){
            throw ExceptionInFunction(__FUNCTION__, "String is empty!");
        }

        if(text.find(pattern) != string::npos)

    }catch(ExceptionInFunction& e){
        cout<<e.what()<<endl;
    }
    catch(exception &e){
        cout<<__FUNCTION__ << ":" << e.what()<< endl;
    }
}