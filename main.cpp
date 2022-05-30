#include "KNN.h"
#include "Decision Tree.h"
#include "Random Forest.h"

using namespace std;

int main(){
    int choice;
    cout<<"1. Decision Tree\n2.Random Forest\n3.KNN\nChoice: ";
    cin>>choice;

    if(choice==1){decisionTree();}
    else if(choice==2){RandomForest();}
    else if(choice==3){knn();}


return 0;
}
