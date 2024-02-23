#include <iostream>
#include <fstream>
#include <limits.h>
#define MAX 1001
using namespace std;

void CountingSort(int* a, int n, ostream &os){
    int c[MAX];
    int min = INT_MAX;
    int max = 0;
    int b[MAX];
    for(int i=0;i<n;i++){
        if(a[i]< min) min = a[i];
        if(a[i]> max) max = a[i];
    }
    int k = max-min+1;
    //inizializzare array C di max-min elementi tutti a 0
    for(int i=0;i<k;i++) c[i] = 0;

    for(int i=0;i<n;i++){
        c[a[i]-min]++;
    }
    
    for(int i=1;i<k;i++) c[i] = c[i-1] + c[i];
    for(int i=n-1;i>=0;i--){
        b[c[a[i]-min]-1] = a[i];
        c[a[i]-min]--;
    }
    for(int i=0;i<k;i++){
        os << c[i] << " ";
    }
    for(int i=0;i<n;i++){
        os << b[i] << " ";
    }
    os << endl;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    int a[MAX];
    for(int k=0;k<100;k++){
        in >> n;
        for(int i=0;i<n;i++) in >> a[i];
        CountingSort(a,n,out);  
    }
    
}