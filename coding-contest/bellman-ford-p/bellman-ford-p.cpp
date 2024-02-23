#include <iostream>
#include <fstream>
#include <limits.h>
#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define MAX 200
#define INF 999999

using namespace std;

template<class H>
class NodeSet{
private:    
    H** v;
    int len, index;
public:
    NodeSet(int len){
        this->index = 0;
        this->len = len;
        v = new H*[len];
        for(int i=0;i<len;i++) v[i] = NULL;
    }
    void insert(H x){
        if(index<len){
            v[index] = new H(x);
            index++;
        }
    }
    int findIndex(H x){
        for(int i=0;i<index;i++){
            if(*v[i] == x) return i;
        }
        return -1;
    }
    H* findKey(int i){
        if(i<0 || i >= len) return NULL;
        else return v[i];
    }
    int search(H x){
        if(findIndex(x) == -1) return 0;
        else return 1;
    }
    int size(){
        return index;
    }
};

template<class H>
class Graph{
private:
    NodeSet<H> *key;
    int nadges;
    int **m;

    int *d, *p;


    void _INIT_SS(int s){
        int n = key->size();
        d = new int[MAX];
        p = new int[MAX];
        for(int i=0;i<n;i++){
            d[i] = INF;
            p[i] = -1;
        }
        d[s] = 0;
    }
    void _Relax(int u, int v){
        cout << "d[" << v << "]:"<< d[v]<< " > d[" << u << "]:" << d[u] << "+ w["<< u << "," << v << "]:" << m[u][v]<< "? ";
        if(d[v] > d[u] + m[u][v]){
            cout << "yes"<< endl;
            d[v] = d[u] + m[u][v];
            p[v] = u;
        } else cout << "no" << endl;
    }

    int _BellmanFord(int s,int k){
        _INIT_SS(s);
        int n = key->size();
        for(int h=0;h<k;h++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    //if(m[i][j] != -101)
                    _Relax(i,j);
                    cout << "d[" << j << "]=" <<  d[j] << endl;
                }
                //cout << endl;
            }
        }

        /*for(int i = 0;i<n;i++){
            for(int j=0;j<n;j++){
                if(d[j] > d[i] + m[i][j])return -1;
            }
        }  */ 
    }
public:
    Graph(int n){
        nadges = 0;
        key = new NodeSet<H>(n);
        m = new int*[n];
        for(int i=0;i<n;i++){
            m[i] = new int[n];
            for(int j=0;j<n;j++){
                m[i][j] = INF;
            }
        }
    }
    int insertNode(H x){
        if(key->search(x)) return -1;
        key->insert(x);
        return 1;
    }

    int insertEdge(H x, H k, int w){
        int i = key->findIndex(x);
        int j = key->findIndex(k);
        if(i == -1 || j == -1) return 0;
        m[i][j] = w;
        nadges++;
        return 1;
    }

    void print(){
        for(int i=0;i<key->size();i++){
            cout << "[" << *key->findKey(i) << "]" << "-->";
            for(int j=0;j<key->size();j++){
                if(m[i][j] != 1000) cout << *key->findKey(j) << "(" << m[i][j] <<")" << "-->";
            }
            cout << "||" << endl;
        }
    }

    int BellmanFord(H s, H f, int k, ofstream &out){
        int start = key->findIndex(s);
        int end = key->findIndex(f);
        cout << "end:" << end << endl;
        if(start == -1 || end == -1) return -1;
        /*int n = key->size();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << m[i][j] << " ";
            }
            cout << endl;
        }*/
        _BellmanFord(start, k);
        if(d[end] != INF) out << d[end] << endl;
        else out << "inf." << endl;
        return 1;
    }

    int size(){return key->size();}

};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m, numk;
    char c;

    for(int k=0;k<100;k++){
        in >> n >> m >> numk;
        Graph<double> *g = new Graph<double>(n);

        for(int i=0; i<n; i++){
            g->insertNode(i);
        }
        for(int i=0;i<m;i++){
            int s, d, p;
            in >> c;
            in >> s;
            //in >> c;
            in >> d;
            //in >> c;
            in >> p;
            in >> c;

            g->insertEdge(s,d,p);
        }

        int start, end;
        in >> start >> end;
        g->BellmanFord(start, end, numk, out);
    }
}