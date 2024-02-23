#include <iostream>
#include <fstream>
#include <limits.h>

#define MAX 1002

using namespace std;
template <class T> void scambia(T *v, int i, int j) {
    T t = v[i];
    v[i] = v[j];
    v[j] = t;
}

template <class T> void bubbleSort(T *v, int n) {
    for(int i=n; i>=1; i--) {
        for(int j=0; j<i-1; j++) {
            if(v[j]>v[j+1]) scambia(v,j,j+1);
        }
    }
}
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    int r,n;
    int t[MAX];
    int m[MAX][MAX];
    int mins[MAX];

    for(int k=0;k<100;k++){

        in >> r >> n;
        int ri = r+1;
        for(int i=0;i<ri;i++) mins[i] = 10000;//INT_MAX;
        for(int i=0;i<n;i++){
            in >> t[i];
        }
        bubbleSort<int>(t,n);

        for(int i=0;i<ri;i++){
            for(int j=0;j<n;j++){
                //FIRST: resto minore del taglio
                if(i < t[j]){
                    m[i][j] = 10000;                    
                }
                else{
                    //SECOND: resto uguale al taglio
                    if(i == t[j]){
                        m[i][j] = 1;                        
                    }
                    else {
                        //THIRD: resto maggiore del taglio
                        if(i > t[j]){
                            m[i][j] = mins[i-t[j]]+1;
                        }
                    }
                }

                if(mins[i]>m[i][j]) mins[i] = m[i][j];   
            }
            
        }
        /*for(int i=0;i<r;i++){
            out << i << ") ";
            for(int j=0;j<n;j++){
                if(m[i][j] > 5000) out << "INF" << "\t";
                else if(m[i][j] < 0) out << "n" << "\t";
                else out << m[i][j] << "\t";
            }
            out <<mins[i]<< endl;
        }*/
        out << mins[ri-1] << endl;
    }
}