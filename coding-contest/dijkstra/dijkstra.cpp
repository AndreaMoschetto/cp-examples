#include <iostream>
#include <fstream>
#include <limits.h>
#define MAX 200
#define INF 99999

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
        //cout << "d[" << v << "]:"<< d[v]<< " > d[" << u << "]:" << d[u] << "+ w["<< u << "," << v << "]:" << m[u][v]<< "? ";
        if(d[v] > d[u] + m[u][v]){
            //cout << "yes"<< endl;
            d[v] = d[u] + m[u][v];
            p[v] = u;
        } //else cout << "no" << endl;
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
    int hasNodes(int *Q, int n){
        for(int i=0;i<n;i++) if(Q[i] == 1) return 1;
        return 0;
    }

    int Dijkstra(H s, H f){
        int n = key->size();
        int start = key->findIndex(s);
        int finish = key->findIndex(f);

        int *Q = new int[n];
        for(int i=0;i<n;i++) Q[i] = 1;

        _INIT_SS(start);

        while(hasNodes(Q,n)){
            int min = INF;
            int minIndex = 0;

            for(int i=0;i<n;i++){
                if(min > d[i] && Q[i]){
                    min = d[i];
                    minIndex = i;
                }
            }
            Q[minIndex] = 0; //tolto dall'insieme

            if(minIndex == finish){
                return d[minIndex];
            }

            for(int i=0;i<n;i++){
                if(Q[i])
                    _Relax(minIndex, i);
            }

        }

    }

};




int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    char c;
    string t;

    for(int k=0;k<100;k++){
        in >> n >> m >> t;
        Graph<double> *g = new Graph<double>(n);

        for(int i=0;i<n;i++){
            double a;
            in >> a;
            g->insertNode(a);
        }
        for(int i=0;i<m;i++){
            double s, d, p;
            in >> c;
            in >> s;
            //in >> c;
            in >> d;
            //in >> c;
            in >> p;
            in >> c;

            g->insertEdge(s,d,p);
        }

        double start, end;
        in >> start >> end;

        out << g->Dijkstra(start,end) << endl;       
    }
}