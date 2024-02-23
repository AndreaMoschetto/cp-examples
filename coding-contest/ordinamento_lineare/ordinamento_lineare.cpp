#include<iostream>
#include<fstream>
#include<limits.h>

#define MAX 1001

using namespace std;

int* Countingsort(int *a, int n, ofstream &out){
    int m = INT_MAX, M = 0, k;
    int C[MAX];
    int *B = new int[MAX];
    for(int i=0;i<n;i++){
        if(a[i] < m) m = a[i];
        if(a[i] > M) M = a[i];
    }
    k = M-m+1;

    for(int i=0;i<k;i++)C[i] = 0;

    for(int i=0;i<n;i++)C[a[i]-m]++;
    
    for(int i=1;i<k;i++)C[i] = C[i-1] + C[i];
    for(int i=n-1;i>=0;i--){
        B[C[a[i]-m]-1] = a[i];
        C[a[i]-m]--;
    }

    for(int i=0;i<k;i++) out << C[i] << " ";
    
    return B;
}
int* Cast_CHAR_INT(char* a, int n){
    int *r = new int[MAX];;
    for(int i=0;i<n;i++) r[i] = (int)a[i];
    return r;
}
int* Cast_DOUBLE_INT(double* a, int n){
    int *r = new int[MAX];;
    for(int i=0;i<n;i++) r[i] = a[i]*(double)10;
    return r;
}
int* Cast_BOOL_INT(bool* a, int n){
    int *r = new int[MAX];
    for(int i=0;i<n;i++) r[i] = (int)a[i];
    return r;
}
char* Cast_INT_CHAR(int* a, int n){
    char *r = new char[MAX];;
    for(int i=0;i<n;i++) r[i] = (char)a[i];
    return r;
}
double* Cast_INT_DOUBLE(int* a, int n){
    double *r = new double[MAX];;
    for(int i=0;i<n;i++) r[i] = a[i]/(double)10;
    return r;
}
bool* Cast_INT_BOOL(int* a, int n){
    bool *r = new bool[MAX];;
    for(int i=0;i<n;i++) r[i] = (bool)a[i];
    return r;
}



int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    string s;

    for(int k=0;k<100;k++){
        in >> s;
        in >> n;
        char t = s[0];
        
        switch(t){
        case 'i':
            int iarr[MAX];
            for(int i=0;i<n;i++) in >> iarr[i];
            
            int *ni;
            ni = Countingsort(iarr,n,out); 
            for(int i=0;i<n;i++) out << ni[i] << " ";
            break;
        case 'd':
            double d[MAX];
            for(int i=0;i<n;i++) in >> d[i];
            double *nd;
            nd = Cast_INT_DOUBLE(Countingsort(Cast_DOUBLE_INT(d,n),n,out),n);
            for(int i=0;i<n;i++) out << nd[i] << " ";
            break;
        case 'b':
            bool b[MAX];
            for(int i=0;i<n;i++) in >> b[i];
            bool *nb;
            nb = Cast_INT_BOOL(Countingsort(Cast_BOOL_INT(b,n),n,out),n);
            for(int i=0;i<n;i++) out << nb[i] << " ";
            break;
        case 'c':
            char c[MAX];
            for(int i=0;i<n;i++) in >> c[i];
            char *nc;
            nc = Cast_INT_CHAR(Countingsort(Cast_CHAR_INT(c,n),n,out),n); 
            for(int i=0;i<n;i++) out << nc[i] << " ";
            break;
        default:
            break;
        }
        out << endl;
    }
}