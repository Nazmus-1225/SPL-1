#pragma once
#include<bits/stdc++.h>
#define EPS 1.0e-3
#define ERROR 404
using namespace std;

int numOfColumn=1,numOfRow=0,numOfCategories=0;
int iteration=0,leaf=0,treeSize=0;
int top=-1;
int *stackVariables;
float *mean;

struct tree{
    int start;
    int end;
    bool isLeaf;
    int decision;
    int splitting;
}*tree;

struct record{
    float *variable;
    int category;
    } ;

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

    float** arr = new float*[numOfRow];

    for (int i = 0; i < numOfRow; i++) {
        arr[i] = new float[numOfColumn];
    }
    fp.open(file);

    for(i=0;i<numOfRow;i++){
        getline(fp,line,'\n');
        stringstream X(line);

        for(j=0;j<numOfColumn;j++){
            string temp;
            getline(X,temp,',');

            arr[i][j]=atof(temp.c_str());}

        if(!fp)
            break;
}

    int temp[numOfRow];
    for(j=0;j<numOfRow;j++){
        temp[j]=0;}

    for(i=0;i<numOfRow;i++){
        for(j=0;j<numOfRow;j++){
            if(arr[i][numOfColumn-1]==j){
                temp[j]++;}}
}

    for(j=0;j<numOfRow;j++){
        if(temp[j]!=0){
            numOfCategories++;
        }}

    cout<<"Number of categories:"<<numOfCategories<<endl;

    stackVariables=new int [numOfColumn-1];
    treeSize=pow(2,numOfColumn)-1;
    mean = new float[numOfColumn-1];
    tree=new struct tree [treeSize];

    return arr;
}

void push(int element)
{
    top++;
    stackVariables[top]=element;
    //cout<<"Pushed: "<<element<<endl;

}

int pop()
{
    int a;
    a=stackVariables[top];
    top--;
    //cout<<"Popped: "<<a<<endl;
    return a;
}


struct record *data;

void storeData(){
    char file[100];
    cout<<"Filename: ";
    cin>>file;
    float **temp=readData(file);
    int i,j;

    data=(struct record*)malloc(numOfRow*sizeof(struct record ));

    for(i=0;i<numOfRow;i++){
        data[i].variable=(float*)malloc((numOfColumn-1)*sizeof(float));
        for(j=0;j<numOfColumn-1;j++){
            data[i].variable[j]=temp[i][j];
        }
        data[i].category=temp[i][numOfColumn-1];
    }


}


int minIndex(float arr[]){
    int i;
    int index=0;
    float min=arr[0];
    for(i=1;i<numOfColumn-1;i++){
        if(arr[i]<min){
            min=arr[i];
            index=i;
        }
    }
return index;
}

int maxIndex(int arr[]){
    int i;
    int index=0;
    float max=arr[0];
    for(i=0;i<numOfCategories;i++){
        if(arr[i]>max){
            max=arr[i];
            index=i;
        }
    }
return index;
}


float minEntropy(float arr[]){
    int i;
    float min=arr[0];
    for(i=0;i<numOfColumn-1;i++){
        if(arr[i]<min){
            min=arr[i];
        }
    }
return min;//min entropy
}

void meanCalculation(){
    int sum,i,j;
    for(j=0;j<numOfColumn-1;j++){
        sum=0;
        for(i=0;i<numOfRow;i++)
            sum=sum+data[i].variable[j];

        mean[j]=(float)sum/(float)numOfRow;
    }
}

float* entropy(int start,int end){


    float *entropy=new float[numOfColumn-1];
    float leftEntropy,rightEntropy,prob,perc;

    int i,j,k,temp,countLow,countHigh,leftCategories[numOfCategories],rightCategories[numOfCategories];



    for(j=0;j<numOfColumn-1;j++){

        countLow=0,countHigh=0;
        leftEntropy=0;
        rightEntropy=0;

        for(k=0;k<numOfCategories;k++){
        leftCategories[k]=0;
        rightCategories[k]=0;}

        for(i=start;i<=end;i++){
            if(data[i].variable[j]<mean[j]){
                countLow++;
                temp=data[i].category;
                leftCategories[temp]++;
                }
            else{
                countHigh++;
                temp=data[i].category;
                rightCategories[temp]++;}}




        for(k=0;k<numOfCategories;k++){
            if(rightCategories[k]!=0){
                prob=(float)rightCategories[k]/countHigh;
                rightEntropy=rightEntropy+(-prob*log2(prob));

            }
        }

        perc=(float)countHigh/(countHigh+countLow);
        rightEntropy=perc*rightEntropy;

        for(k=0;k<numOfCategories;k++){
            if(leftCategories[k]!=0){
                prob=(float)leftCategories[k]/countLow;

                leftEntropy=leftEntropy+(-prob*log2(prob));

            }
        }

        perc=(float)countLow/(countHigh+countLow);
        leftEntropy=perc*leftEntropy;

        entropy[j]=leftEntropy+rightEntropy;
        }


        return entropy;
}


int split(int start,int end, int splitColumn)
{
    int before=start;
    int after=end;
    int i,j;

    float splittingValue=mean[splitColumn];

    struct record temp[end-start+1];

    for(i=start,j=0;i<=end;i++,j++){
        temp[j]=data[i];
    }


	for (i=start,j=0;i<end;i++,j++){
		if(temp[j].variable[splitColumn]<splittingValue){
			data[before]=temp[j];
			before++;
		}
		else{
			data[after]=temp[j];
			after--;
		}
	}

	if(temp[j].variable[splitColumn]<splittingValue){
        data[before]=temp[j];
        return before;
	}
	else
    {
        data[after]=temp[j];
        return before-1;
    }
}

void DecisionTree(int start,int finish,int index)
{
iteration++;

int i,categories[numOfCategories];
for(i=0;i<numOfCategories;i++){
    categories[i]=0;
}

    if(start>=finish || finish==-1){
            tree[index].isLeaf=true;
            leaf++;

        tree[index].decision=data[start].category;

        return;
    }


    float *entr=entropy(start,finish);


    for(i=0;i<=top;i++){
        entr[stackVariables[i]]=ERROR;
    }

    float minEntropyValue=minEntropy(entr);
    int splitColumn=minIndex(entr);

    push(splitColumn);

    if( top>=numOfColumn-1){
        tree[index].isLeaf= true;
        leaf++;

        for(i=start;i<=finish;i++){
            int temp=data[i].category;
            categories[temp]++;
        }
        tree[index].decision=maxIndex(categories);

        pop();
        return;
    }

    if(minEntropyValue<EPS){
        split(start,finish,splitColumn);

        tree[2*index+1].isLeaf=true;
        tree[2*index+1].decision=data[start].category;

        tree[2*index+2].isLeaf=true;
        tree[2*index+2].decision=data[finish].category;

    }

    tree[index].start=start;
    tree[index].end=finish;
    tree[index].splitting=splitColumn;
    tree[index].isLeaf=false;

    int midpoint=split(start,finish,splitColumn);

    if(start<=midpoint){
        DecisionTree(start,midpoint,2*index+1);}

    if(finish>midpoint){
        DecisionTree(midpoint+1,finish,2*index+2);}

        pop();
        return;

}

int decision(float *userInput)
{
    int index,category,splittingValue;
    for(index=0;tree[index].isLeaf==false;){
        category=tree[index].splitting;
        if(userInput[category]<mean[category])
            index=2*index+1;
        else
            index=2*index+2;
    }

    return tree[index].decision;
}

int decisionTree(){
storeData();
meanCalculation();
DecisionTree(0,numOfRow-1,0);
cout<<"Tree generated"<<endl;
struct record test;
test.variable=(float*)malloc((numOfColumn-1)*sizeof(float));
for(int i=0;i<numOfColumn-1;i++){
        cout<<"Variable "<<i+1<<": ";
        cin>>test.variable[i];
    }
test.category=decision(test.variable);

cout<<"Class: "<<test.category<<endl;
numOfColumn=1;
numOfRow=0;
numOfCategories=0;
iteration=0;
leaf=0;
treeSize=0;
top=-1;
return test.category;}



