#include <iostream>
#include <fstream>
#define MAX 201

using namespace std;
template<class V>
struct terna{
    V first, second, third;
};
template<class V>
bool operator < (terna<V> &a, terna<V> &b){
    return a.first < b.first || (a.first == b.first && a.second < b.second) ||
            (a.first == b.first && a.second == b.second && a.third < b.third);
}
template<class V>
bool operator == (terna<V> &a, terna<V> &b){
    return a.first == b.first && a.second == b.second && a.third == b.third;
}
template<class V>
bool operator > (terna<V> &a, terna<V> &b){
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
            terna<int> iarray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> iarray[i].first;
                //in >> c;
                in >> iarray[i].second;

                in >> iarray[i].third;

                in >> c;
            }
            //for(int i=0;i<n;i++) cout << "(" << iarray[i].first << " " << iarray[i].second << ")";
            Heap<terna<int>> *ih = new Heap<terna<int>>(iarray,n);
            ih->BuildMaxHeap();
            terna<int> *iarr = ih->ExtractMax(n);
            out << ih->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << iarr[i].first << " " << iarr[i].second << " " << iarr[i].third <<  ") ";
            out << endl;
            break;
        }
        case 'd':
        {
            terna<double> darray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> darray[i].first;
                //in >> c;
                in >> darray[i].second;

                in >> darray[i].third;

                in >> c;
            }
            Heap<terna<double>> *dh = new Heap<terna<double>>(darray,n);
            dh->BuildMaxHeap();
            terna<double> *darr = dh->ExtractMax(n);
            out << dh->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << darr[i].first << " " << darr[i].second << " " << darr[i].third <<  ") ";
            out << endl;
            break;
        }
        case 'b':
        {
            terna<bool> barray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> barray[i].first;
                //in >> c;
                in >> barray[i].second;

                in >> barray[i].third;

                in >> c;
            }
            Heap<terna<bool>> *bh = new Heap<terna<bool>>(barray,n);
            bh->BuildMaxHeap();
            terna<bool> *barr = bh->ExtractMax(n);
            out << bh->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << barr[i].first << " " << barr[i].second << " " << barr[i].third <<  ") ";
            out << endl;
            break;
        }
        case 'c':
        {
            terna<char> carray[MAX];
            char c;
            for(int i=0;i<n;i++){
                in >> c;
                in >> carray[i].first;
                //in >> c;
                in >> carray[i].second;

                in >> carray[i].third;

                in >> c;
            }
            Heap<terna<char>> *ch = new Heap<terna<char>>(carray,n);
            ch->BuildMaxHeap();
            terna<char> *carr = ch->ExtractMax(n);
            out << ch->getCount() << " ";
            for(int i=0;i<n;i++) out << "(" << carr[i].first << " " << carr[i].second << " " << carr[i].third <<  ") ";
            out << endl;
            break;
        }
        default:
            break;

        }
    }
}