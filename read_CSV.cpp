#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<string>
#include<string.h>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;

int n=1,m=0;

float minimum(float *a,int n){
    float m=a[0];
    int i;
    for(i=0;i<n-1;i++){
        if(m>a[i]){m=a[i];}
    }
    return m;
}

int minimumIndex(float *a,int n){
    float m=a[0];
    int i,c=0;
    for(i=1;i<n-1;i++){
        if(m>a[i]){m=a[i];
        c=i;}
    }
    return c;
}

void rowcopy(int r1,int r2,float **a,float **b,int n){
    int i,j;
    for(i=0;i<n;i++){
        a[r1][i]=b[r2][i];
    }
}

float entropy(float **a,float *b,int m,int n,int col,int c){
   int i,j,k,c1=0,c2=0,categories[c];


        for(j=0;j<m;j++){
            if(a[j][col]<=b[col])
                c1++;
            else c2++;
        }


         float** left = new float*[c1];

    for (int i = 0; i < c1; i++) {
        left[i] = new float[n];
    }

    float** right = new float*[c2];

    for (int i = 0; i < c2; i++) {
        right[i] = new float[n];
    }

        k=0,i=0;
        for(j=0;j<m;j++){
            if(a[j][col]<=b[col])
                {rowcopy(i,j,left,a,n);
                i++;}
            else
                {rowcopy(k,j,right,a,n);
                k++;}
        }


        float le=0,re=0,e;

        for(j=0;j<c;j++){
    categories[j]=0;}

        for(i=0;i<c1;i++){
            int f=left[i][n-1];
            categories[f]++;
        }

        for(i=0;i<c;i++){
            if(categories[i]!=0){
                float p=(float)categories[i]/c1;

                le=le+-p*log2(p);

            }
        }
        float v=(float)c1/m;
        le=v*le;
       // cout<<le<<endl;

        for(j=0;j<c;j++){
    categories[j]=0;}
        for(i=0;i<c2;i++){
            int f=right[i][n-1];
            categories[f]++;
        }

        for(i=0;i<c;i++){
            if(categories[i]!=0){
                float p=(float)categories[i]/c2;
                re=re+-p*log2(p);

            }
        }
        v=(float)c2/m;
        re=v*re;
//cout<<re<<endl;
        e=le+re;
        return e;


}

float* mean(float **a,int m,int n){
float* mean=new float[n-1];
int sum,i,j;
for(j=0;j<n-1;j++){
        sum=0;

    for(i=0;i<m;i++)
        sum=sum+a[i][j];

    mean[j]=sum/(float)m;
}
return mean;}

float **data(char file[]){
ifstream fp;
   fp.open(file);
    string line="";
    int i,j;
    getline(fp, line);
    for(i=0;i<line.length();i++){
        if(line.at(i)==','){n++;}
    }
    cout<<"Number of variables:"<<n<<endl;
    fp.close();

    fp.open(file);
    for(i=0;;++i)
        {
            getline(fp,line,'\n');
            if(!fp)
            break;
            m++;
            }
    fp.close();

    cout<<"Number of records:"<<m<<endl;

    float** a = new float*[m];

    for (int i = 0; i < m; i++) {
        a[i] = new float[n];
    }
    fp.open(file);

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

    return a;
}

int main(){

char file[]="Book1.csv";
//string x;
//cout<<"Enter filename: ";
//cin>>x;
//char file[100];
//strcpy(file, x.c_str());


float **a=data(file);
int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cout<<a[i][j]<<"\t";
    }
        cout<<"\n";}



int t[m];
for(j=0;j<m;j++){
    t[j]=0;}

for(i=0;i<m;i++){
        for(j=0;j<m;j++){
    if(a[i][n-1]==j){
            t[j]++;}}
}
int c=0;
for(j=0;j<m;j++){
    if(t[j]!=0){
        c++;
        }}

        int categories[c];
        for(j=0;j<m;j++){
    if(t[j]!=0){
        categories[j]=t[j];
        }}
        for(i=0;i<c;i++){cout<<"category "<<i<<": "<<categories[i]<<endl;}

    float *mn=mean(a,m,n);
        for(i=0;i<n-1;i++){cout<<mn[i]<<"\t";}
        cout<<endl;

        float entr[n-1];
        for(i=0;i<n-1;i++){
     entr[i]=entropy(a,mn,m,n,i,c);
     //cout<<entr[i];
     }

     cout<<"Minimum entropy : "<<minimum(entr,n)<<" for variable "<<minimumIndex(entr,n);

    return 0;

}


