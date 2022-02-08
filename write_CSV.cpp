#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;

int main(){
    ofstream fp;
    fp.open("Book1.csv",std::ios_base::app);
    string str="";
    cout<<"Name: ";
    cin>>str;
    fp<<"\n"<<str<<",";
    cout<<"Roll: ";
    cin>>str;
    fp<<str<<",";
    cout<<"Phone: ";
    cin>>str;
    fp<<str<<",";
    float x;
    cout<<"CGPA: ";
    cin>>x;
    fp<<x;
    return 0;

}

