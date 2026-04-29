#include <iostream>
using namespace std;

#include "utils.h"

int main(const int argc,const char* argv[]){
    if(argc < 3) {
        cout<<"Wrong inputs"<<endl;
    }
    // if(argv[0] != "./mygrep" ){
    //     cout<<"Wrong file name and args" << endl;
    // }
    // string pattern = argv[1];

    // cout<<"argv is: " << argv[1] << endl;

    // cout<<pattern<<endl;
    // cout<<"In here" << __FUNCTION__ << endl;
    returnLine(argv[2], argv[1]);

}