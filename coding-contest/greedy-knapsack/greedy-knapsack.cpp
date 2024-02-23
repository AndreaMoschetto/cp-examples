#include <iostream>
#include <fstream>
#define MAX 1001
using namespace std;
void Swap(int &a, int &b, int *array){
    int t = array[a];
    array[a] = array[b];
    array[b] = t;
}
int UnitaryGreedyKnapsack(int n, int p, int* item){
    int sack = 0;
    int weight = 0;
    for(int i=0;i<n-1;i++){
        int max = i;
        for(int j=i;j<n;j++){
            if(item[j] > item[max]) max = j;
        }
        Swap(i,max,item);
        if(weight < p){
            sack += item[i];
            weight++;
        }
    }
    return sack;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    for(int k=0;k<100;k++){
        int n, p;
        in >> n >> p;
        int item[MAX];
        for(int i=0;i<n;i++) in >> item[i];

        out << UnitaryGreedyKnapsack(n,p,item) << endl;
    }
    
}