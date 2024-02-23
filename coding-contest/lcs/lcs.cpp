#include<iostream>
#include <fstream>
#define MAX 1001

using namespace std;

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    char x[MAX], y[MAX];
    int l[MAX][MAX];

    
    for(int k=0;k<100;k++){
        in >> n >> m;

        for(int i=1;i<=n;i++){
            in >> x[i];
        }
        for(int i=1;i<=m;i++){
            in >> y[i];
        }

        for(int i=0;i<=n;i++){
            l[i][0] = 0;
        }
        for(int i=0;i<=m;i++){
            l[0][i] = 0;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(x[i]==y[j]){
                    l[i][j] = l[i-1][j-1]+1;
                }
                else{
                    l[i][j] = max(l[i-1][j], l[i][j-1]);
                }
            }
        }

        for(int i=0;i<=n;i++){

            for(int j=0;j<=m;j++){
                cout << l[i][j] << " ";
            }
            cout << endl;
        }
        out << l[n][m] << endl;
    }
}