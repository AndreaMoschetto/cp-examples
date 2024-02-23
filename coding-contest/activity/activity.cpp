#include<iostream>
#include<fstream>

#define MAX 1001

using namespace std;

void SwapActivity(int *s, int *f, int a, int b){
    int st = s[a];
    int ft = f[a];
    s[a] = s[b];
    f[a] = f[b];
    s[b] = st;
    f[b] = ft;
}

void SelectionSortAcrivity(int *s, int *f, int n){
    for(int i=0;i<n-1;i++){
        int min = i;
        for(int j=i;j<n;j++){
            if(f[j] < f[min]) min = j;
        }
        SwapActivity(s,f,i,min);
    }
}

int activity(int *s, int *f, int n, int i){
    while(s[])
    int senza = activity(s,f,n,i+1);
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    int s[MAX], f[MAX];
    char c;
    for(int k=0;k<100;k++){
        in >> n;
        for(int i=0;i<n;i++){
            in >> c;
            in >> s[i];
            in >> c;
            in >> f[i];
            in >> c;
            //cout << "(" << s[i] << "," << f[i] << "), ";
        }
        
        SelectionSortAcrivity(s,f,n);
        for(int i=0;i<n;i++) cout << "(" << s[i] << "," << f[i] << "), ";

        int m = 0;
        int num = 1;
        for(int i=1;i<n;i++){
            if(s[i] >= f[m]){
                m = i;
                num++;
            }
        }

        
        cout << endl;
        out << num << endl;
    }
}