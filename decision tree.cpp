#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<string>
#include<string.h>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ifstream fp;
    char x[]="Book1.csv";
    fp.open(x);
    string line="";
    int i,j,n=1,m=0;
    getline(fp, line);
    for(i=0;i<line.length();i++){
        if(line.at(i)==','){n++;}
    }
    cout<<"Number of variables:"<<n<<endl;
    fp.close();
    fp.open(x);
    for(i=0;;++i)
        {
            getline(fp,line,'\n');
            if(!fp)
            break;
            m++;
            }
    fp.close();

    cout<<"Number of records:"<<m<<endl;

    float a[m][n];

    fp.open(x);
    for(i=0;i<m;i++){
        getline(fp,line,'\n');
        stringstream X(line);
        for(j=0;j<n;j++){
            string temp;
            getline(X,temp,',');
            a[i][j]=atof(temp.c_str());}

        if(!fp)
            break;

    }


    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cout<<a[i][j]<<"\t";
    }
        cout<<"\n";}
    
    int sum;
for(j=0;j<n;j++){
        sum=0;
   // mean[i]=Mean(m,n,a,i);
    for(i=0;i<m;i++)
        sum=sum+a[i][j];

    mean[j]=sum/(float)m;
}
cout<<"Mean: ";
for(i=0;i<n;i++)
    cout<<mean[i]<<" ";
    cout<<endl;

//Percentage
int c;

for(j=0;j<n;j++){
        c=0;
    for(i=0;i<m;i++){
        if(a[i][j]<mean[i])
            c++;
    }


    percentage[j]=c/(float)m;
}
cout<<"Percentage: ";
for(i=0;i<n;i++)
    cout<<percentage[i]<<" ";


    return 0;

}

