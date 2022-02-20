#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;

int main(){
    ifstream fp;
    fp.open("Book1.csv");
    string line="";
    int i,n=1;
    getline(fp, line);
    for(i=0;i<line.length();i++){
        if(line.at(i)==','){n++;}
    }
    cout<<"Number of variables:"<<n;
    getline(fp, line,',');
    cout<<"Roll: "<<line<<endl;
    getline(fp, line,',');
    cout<<"Phone: "<<line<<endl;
    float x;
    fp>>x;
    cout<<"CGPA: "<<x;
    return 0;

}
