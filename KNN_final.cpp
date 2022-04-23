#include<bits/stdc++.h>
using namespace std;

int numOfColumn=1,numOfRow=0,numOfCategories=0;


float **readData(char file[]){
ifstream fp;
   fp.open(file);
    string line="";
    int i,j;
    getline(fp, line);
    for(i=0;i<line.length();i++){
        if(line.at(i)==','){numOfColumn++;}
    }
    cout<<"Number of variables:"<<numOfColumn<<endl;
    fp.close();

    fp.open(file);
    for(i=0;;++i)
        {
            getline(fp,line,'\n');
            if(!fp)
            break;
            numOfRow++;
            }
    fp.close();

    cout<<"Number of records:"<<numOfRow<<endl;
    cout<<endl;

    float** a = new float*[numOfRow];

    for (int i = 0; i < numOfRow; i++) {
        a[i] = new float[numOfColumn];
    }
    fp.open(file);

    for(i=0;i<numOfRow;i++){
        getline(fp,line,'\n');
        stringstream X(line);

        for(j=0;j<numOfColumn;j++){
            string temp;
            getline(X,temp,',');

            a[i][j]=atof(temp.c_str());}

        if(!fp)
            break;
}

    int temp[numOfRow];
    for(j=0;j<numOfRow;j++){
        temp[j]=0;}

    for(i=0;i<numOfRow;i++){
        for(j=0;j<numOfRow;j++){
            if(a[i][numOfColumn-1]==j){
                temp[j]++;}}
}

    for(j=0;j<numOfRow;j++){
        if(temp[j]!=0){
            numOfCategories++;
        }}

    return a;
}

struct record{
    float *variable;
    int category;
    float distance=0;
    float weight;
    } ;
struct record *neighbours;


void storeData(){
    char file[]="Book1.csv";
    float **data=readData(file);
    int i,j;

    neighbours=(struct record*)malloc(numOfRow*sizeof(struct record ));

    for(i=0;i<numOfRow;i++){
        neighbours[i].variable=(float*)malloc((numOfColumn-1)*sizeof(float));
        for(j=0;j<numOfColumn-1;j++){
            neighbours[i].variable[j]=data[i][j];
        }
        neighbours[i].category=data[i][numOfColumn-1];
    }

    for(i=0;i<numOfRow;i++){
        for(j=0;j<numOfColumn-1;j++){
            cout<<neighbours[i].variable[j]<<"\t";
        }
        cout<<neighbours[i].category<<"\n";
    }
    cout<<endl;
}

void calculateDistance(struct record x){
    int i,j;
    float diff;
    for(i=0;i<numOfRow;i++){
        neighbours[i].distance=0;
    }
    for(i=0;i<numOfRow;i++){
        for(j=0;j<numOfColumn-1;j++){
            diff=x.variable[j]-neighbours[i].variable[j];
            neighbours[i].distance+=pow(diff,2);

        }

        neighbours[i].distance=sqrt(neighbours[i].distance);
        neighbours[i].weight=1/neighbours[i].distance;
    }


}

void bubbleSort(){
    int i,j;
    struct record temp;

    for(i=0;i<numOfRow;i++){
        for(j=i+1;j<numOfRow;j++){
            if(neighbours[i].distance>neighbours[j].distance){
                temp=neighbours[i];
                neighbours[i]=neighbours[j];
                neighbours[j]=temp;
            }
        }
    }
}

int prediction(int K){
    float freq[numOfCategories];
    int i,j;

    for(i=0;i<numOfCategories;i++){
        freq[i]=0;
    }

    for(i=0;i<K;i++){
        freq[neighbours[i].category]+=neighbours[i].weight;
    }

    float maximum=0;
    int value=0;
    for(i=0;i<numOfCategories;i++){
        if(freq[i]>maximum){
            maximum=freq[i];
            value=i;
    }
    }
    return value;
}

int main(){
    storeData();
    struct record test;
    int i,j,K;

    test.variable=(float*)malloc((numOfColumn-1)*sizeof(float));

    for(i=0;i<numOfColumn-1;i++){
        cout<<"Variable "<<i+1<<": ";
        cin>>test.variable[i];
    }

    calculateDistance(test);
    bubbleSort();

    cout<<"\nEnter K: ";
    cin>>K;


    int result=prediction(K);

    cout<<"\nThe test belongs to category "<<result<<endl;

    return 0;}

