#include <iostream>
#include <fstream>
#define MAX 201

using namespace std;
template<class V>
struct coppia{
    V first, second;
};
template<class V>
bool operator < (coppia<V> &a, coppia<V> &b){
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}
template<class V>
bool operator == (coppia<V> &a, coppia<V> &b){
    return a.first == b.first && a.first == b.first;
}
template<class V>
bool operator > (coppia<V> &a, coppia<V> &b){
    return !(a < b) && !(a == b);
}

template<class T>
class Heap{
private:
    T* a;
    int size;
    int countH;

    void _Swap(T &a, T &b){
        T t = a;
        a = b;
        b = t;
    }
    int _Parent(int n){return n>>1;}
    int _Left(int n){return n<<1;}
    int _Right(int n){return (n<<1)|1;}
    void _Heapify(int i){
        int l = _Left(i);
        int r = _Right(i);
        int max = i;
        if(a[max] < a[l] && l <= size){
            max = l;
        }
        if(a[max] < a[r] && r <= size){
            max = r;
        }
        countH++;
        if(max != i){
            _Swap(a[max],a[i]);
            _Heapify(max);
            //countH++;
        }

    }

public:
    Heap(T* array, int n){
        a = new T[MAX];
        for(int i=1;i<=n;i++){
            a[i] = array[i-1];
        }
        size = n;
        countH = 0;

        /*a = array;
        size = n;
        countH = 0;*/
    }

    void BuildMaxHeap(){
        for(int i=(size >> 1); i>=1; i--){
            _Heapify(i);
        }
    }
    void ExtractMax(){
        _Swap(a[1],a[size]);
        size--;
        _Heapify(1);
    }
    T* ExtractMax(int n){
        for(int i=0;i<n;i++){
            _Swap(a[1],a[size]);
            size--;
            _Heapify(1);
        }
        return a+1;
    }

    int getCount(){return countH-1;}
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    string t;
    int n;
    for(int k=0;k<100;k++){
        in >> t >> n;
        switch(t[0]){
        case 'i':
        {
            coppia<int> iarray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> iarray[i].first;
                //in >> c;
                in >> iarray[i].second;
                in >> c;
            }
            //for(int i=0;i<n;i++) cout << "(" << iarray[i].first << " " << iarray[i].second << ")";
            Heap<coppia<int>> *ih = new Heap<coppia<int>>(iarray,n);
            ih->BuildMaxHeap();
            coppia<int> *iarr = ih->ExtractMax(n);
            out << ih->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << iarr[i].first << " " << iarr[i].second << ") ";
            out << endl;
            break;
        }
        case 'd':
        {
            coppia<double> darray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> darray[i].first;
                //in >> c;
                in >> darray[i].second;
                in >> c;
            }
            Heap<coppia<double>> *dh = new Heap<coppia<double>>(darray,n);
            dh->BuildMaxHeap();
            coppia<double> *darr = dh->ExtractMax(n);
            out << dh->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << darr[i].first << " " << darr[i].second << ") ";
            out << endl;
            break;
        }
        case 'b':
        {
            coppia<bool> barray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> barray[i].first;
                //in >> c;
                in >> barray[i].second;
                in >> c;
            }
            Heap<coppia<bool>> *bh = new Heap<coppia<bool>>(barray,n);
            bh->BuildMaxHeap();
            coppia<bool> *barr = bh->ExtractMax(n);
            out << bh->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << barr[i].first << " " << barr[i].second << ") ";
            out << endl;
            break;
        }
        case 'c':
        {
            coppia<char> carray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> carray[i].first;
                //in >> c;
                in >> carray[i].second;
                in >> c;
            }
            Heap<coppia<char>> *ch = new Heap<coppia<char>>(carray,n);
            ch->BuildMaxHeap();
            coppia<char> *carr = ch->ExtractMax(n);
            out << ch->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << carr[i].first << " " << carr[i].second << ") ";
            out << endl;
            break;
        }
        default:
            break;

        }
    }
}