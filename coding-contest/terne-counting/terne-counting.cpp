#include <iostream>
#include <fstream>
#include <limits.h>
#define MAX 1001

using namespace std;
template<class T>
struct coppia{
    T first, second, third;
};

coppia<int>* Countingsort(coppia<int> *a, int n, ofstream &out){
    int m = INT_MAX, M = 0, k;
    int C[MAX];
    coppia<int> *B = new coppia<int>[MAX];
    for(int i=0;i<n;i++){
        if(a[i].first < m) m = a[i].first;
        if(a[i].first > M) M = a[i].first;
    }
    k = M-m+1;

    for(int i=0;i<k;i++)C[i] = 0;

    for(int i=0;i<n;i++)C[a[i].first-m]++;
    
    for(int i=1;i<k;i++)C[i] = C[i-1] + C[i];
    for(int i=n-1;i>=0;i--){
        B[C[a[i].first-m]-1] = a[i];
        C[a[i].first-m]--;
    }

    for(int i=0;i<k;i++) out << C[i] << " ";
    
    return B;
}
coppia<int>* Cast_DOUBLE_INT(coppia<double>* a, int n){
    coppia<int> *r = new coppia<int>[MAX];
    for(int i=0;i<n;i++){
        r[i].first = a[i].first*(double)10;
        r[i].second = a[i].second*(double)10;
        r[i].third = a[i].third*(double)10;
    } 
    return r;
}

coppia<double>* Cast_INT_DOUBLE(coppia<int>* a, int n){
    coppia<double> *r = new coppia<double>[MAX];
    for(int i=0;i<n;i++){
        r[i].first = a[i].first/(double)10;
        r[i].second = a[i].second/(double)10;
        r[i].third = a[i].third/(double)10;
    }
    return r;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    coppia<double> v[MAX];
    char c;
    for(int k=0;k<100;k++){
        in >> n;
        for(int i=0;i<n;i++){
            in >> c;
            in >> v[i].first;
            //in >> c;
            in >> v[i].second;
            //in >> c;
            in >> v[i].third;
            in >> c;
        }

        coppia<double>* r;

        r = Cast_INT_DOUBLE(Countingsort(Cast_DOUBLE_INT(v,n),n,out),n);

        for(int i=0;i<n;i++) out << "(" << r[i].first << " " << r[i].second << " " << r[i].third << ") ";
        out << endl;   
    }
}