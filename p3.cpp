//  AOA2_PROJECT3
//  Hüma Kalaycı
//  
//
//  compilation:
//  g++ -std=c++11 p3.cpp -o project3
//  ./project3 input1.txt
#include <iostream>
#include <fstream>
#define MAX_N 20        //maximum numbers of players
using namespace std;

class matches{
    public:
        int N;
        int currentWins[MAX_N];
        int matchesMatrix[MAX_N][MAX_N];
        int restMatchesForEach[MAX_N] = {0};
        int othersTotalCurrent[MAX_N] = {0};
        float meanForRestEach[MAX_N] = {0};
        int winners[MAX_N];
    matches(int x){  //constructor with parameter
       N = x;
       for(int i=0; i<MAX_N; i++)   winners[i] = -1;
    } 
};

void printInput(matches obj){ //print inputs function for testing
    cout<<obj.N<<endl;
    for(int i=0; i< obj.N ; i++) cout<<obj.currentWins[i]<<" ";
    cout<<endl;
    for (int i = 0; i < obj.N; i++){
        for (int j = 0; j < obj.N; j++){
            cout<<obj.matchesMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

matches minCut(matches obj){ //mincut function to apply maxflow
    int i, j;
     for (i = 0; i <obj.N; i++){
        //cout<<"\t";
        for (j = 0; j <obj.N; j++){
            //cout<<obj.matchesMatrix[i][j]<<" ";
            obj.restMatchesForEach[i] += obj.matchesMatrix[i][j];
        }
        //cout<<"\nRestMatches"<<i<<": "<<obj.restMatchesForEach[i];
        //cout<<"\tCurrentWin"<<i<<": "<<obj.currentWins[i];
        //cout<<"\tothers current: ";
        for (j = 0; j < obj.N; j++){
            if(i!=j){
                //cout<<j<<":"<<obj.currentWins[j]<<"  ";
                obj.othersTotalCurrent[i] += obj.currentWins[j];
            }
        }
        //cout<<"\tOthersTotalCurrent: "<<obj.othersTotalCurrent[i];
        obj.meanForRestEach[i] = ( float(obj.othersTotalCurrent[i] + obj.restMatchesForEach[i]) ) / float(obj.N-1);
        //cout<<"\tMean: "<<obj.meanForRestEach[i]<<endl;
    }
    return obj;
}

matches winners(matches obj){
    for (int i = 0; i < obj.N; i++){///
        if(obj.meanForRestEach[i] <= obj.restMatchesForEach[i] + obj.currentWins[i]){
            //cout<<i<<" kazanabilir"<<endl;
            obj.winners[i] = 1;
        }
        else    obj.winners[i] = 0;
    }
    return obj;
}

int main(int argc, char *argv[]){
    int i, j;
    int size;

    string filename = argv[1]; //take the input file name as command line argument 
    ifstream f(filename);
    f >> size;
     
    matches obj(size); //create object frorm matches class

    for(int i=0; i< obj.N; i++) f >> obj.currentWins[i];  //assign input.txt to variables and matches matrix
    for (int i = 0; i < obj.N; i++){
        for (int j = 0; j < obj.N; j++){
            f >> obj.matchesMatrix[i][j];
        }
    }
    f.close();
    //printInput(obj); //for testing, print input
    
    obj = minCut(obj);
    obj = winners(obj);
    for (i = 0; i < obj.N; i++)    cout<<obj.winners[i]<<" ";
    cout<<endl;
    
    ofstream myfile;
    myfile.open ("output.txt");
    for (i = 0; i < obj.N; i++)    myfile << obj.winners[i]<<" "; 
    myfile.close();
    
    return 0;
}
