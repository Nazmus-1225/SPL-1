#include "Decision Tree.h"

using namespace std;

int RandomForest(){
cout<<"Number of files: ";
int k,i,index=0;
cin>>k;
int decisions[k],categories[100];
for(i=0;i<100;i++){categories[i]=0;}
for(i=0;i<k;i++){decisions[i]=decisionTree();}

for(i=0;i<k;i++){categories[decisions[i]]++;}

int vote=categories[0];
for(i=0;i<100;i++){
    if(vote<categories[i]){vote=categories[i];
    index=i;}
}
cout<<"Random Forest's result: "<<index<<endl;
return index;
}
