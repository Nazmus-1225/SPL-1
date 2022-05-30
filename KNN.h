#include<bits/stdc++.h>
using namespace std;

int column=1,row=0,categories=0;


float **readData1(char file[]){
ifstream fp;
   fp.open(file);
    string line="";
    int i,j;
    getline(fp, line);
    for(i=0;i<line.length();i++){
        if(line.at(i)==','){column++;}
    }
    cout<<"Number of variables:"<<column<<endl;
    fp.close();

    fp.open(file);
    for(i=0;;++i)
        {
            getline(fp,line,'\n');
            if(!fp)
            break;
            row++;
            }
    fp.close();

    cout<<"Number of records:"<<row<<endl;

    float** a = new float*[row];

    for (int i = 0; i < row; i++) {
        a[i] = new float[column];
    }
    fp.open(file);

    for(i=0;i<row;i++){
        getline(fp,line,'\n');
        stringstream X(line);

        for(j=0;j<column;j++){
            string temp;
            getline(X,temp,',');

            a[i][j]=atof(temp.c_str());}

        if(!fp)
            break;
}

    int temp[row];
    for(j=0;j<row;j++){
        temp[j]=0;}

    for(i=0;i<row;i++){
        for(j=0;j<row;j++){
            if(a[i][column-1]==j){
                temp[j]++;}}
}

    for(j=0;j<row;j++){
        if(temp[j]!=0){
            categories++;
        }}

        cout<<"Number of categories:"<<categories<<endl;
    return a;
}

struct record1{
    float *variable;
    int category;
    float distance=0;
    float weight;
    } ;
struct record1 *neighbours;


void storeData1(){
    char file[100];
    cout<<"Filename: ";
    cin>>file;
    float **temp=readData1(file);
    int i,j;

    neighbours=(struct record1*)malloc(row*sizeof(struct record1 ));

    for(i=0;i<row;i++){
        neighbours[i].variable=(float*)malloc((column-1)*sizeof(float));
        for(j=0;j<column-1;j++){
            neighbours[i].variable[j]=temp[i][j];
        }
        neighbours[i].category=temp[i][column-1];
    }
}

void calculateDistance(struct record1 x){
    int i,j;
    float diff;
    for(i=0;i<row;i++){
        neighbours[i].distance=0;
    }
    for(i=0;i<row;i++){
        for(j=0;j<column-1;j++){
            diff=x.variable[j]-neighbours[i].variable[j];
            neighbours[i].distance+=pow(diff,2);

        }

        neighbours[i].distance=sqrt(neighbours[i].distance);
        neighbours[i].weight=1/neighbours[i].distance;
    }


}

void bubbleSort(){
    int i,j;
    struct record1 temp;

    for(i=0;i<row;i++){
        for(j=i+1;j<row;j++){
            if(neighbours[i].distance>neighbours[j].distance){
                temp=neighbours[i];
                neighbours[i]=neighbours[j];
                neighbours[j]=temp;
            }
        }
    }
}

int prediction(int K){
    float freq[categories];
    int i,j;

    for(i=0;i<categories;i++){
        freq[i]=0;
    }

    for(i=0;i<K;i++){
        freq[neighbours[i].category]+=neighbours[i].weight;
    }

    float maximum=0;
    int value=0;
    for(i=0;i<categories;i++){
        if(freq[i]>maximum){
            maximum=freq[i];
            value=i;
    }
    }
    return value;
}

int knn(){
    storeData1();
    struct record1 test;
    int i,j,K;

    test.variable=(float*)malloc((column-1)*sizeof(float));

    for(i=0;i<column-1;i++){
        cout<<"Variable "<<i+1<<": ";
        cin>>test.variable[i];
    }

    calculateDistance(test);
    bubbleSort();

    cout<<"\nEnter the value of K: ";
    cin>>K;


    int result=prediction(K);
    cout<<"Class: "<<result<<endl;


    return result;}

