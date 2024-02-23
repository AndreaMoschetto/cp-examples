#include <iostream>
#include <fstream>
#define MAX 201

using namespace std;

template<class T>
class Heap{
private:
    T* a;
    int size;
    int oldSize;
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
        if(a[max] > a[l] && l <= size){
            max = l;
        }
        if(a[max] > a[r] && r <= size){
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
        oldSize = n;
        countH = 0;
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
    void ExtractMax(int n){
        for(int i=0;i<n;i++){
            _Swap(a[1],a[size]);
            size--;
            _Heapify(1);
        }
    }
    void printOrdered(ostream &out){
        ExtractMax(size);
        for(int i=1;i<=oldSize;i++){
            out << a[i] << " ";
        }
        out << endl;
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
            int iarray[MAX];
            for(int i=0;i<n;i++){
                in >> iarray[i];
            }
            Heap<int> *ih = new Heap<int>(iarray,n);
            ih->BuildMaxHeap();
            ih->ExtractMax(n);
            out << ih->getCount() << " ";
            ih->printOrdered(out);
            break;
        }
        case 'd':
        {
            double darray[MAX];
            for(int i=0;i<n;i++){
                in >> darray[i];
            }
            Heap<double> *dh = new Heap<double>(darray,n);
            dh->BuildMaxHeap();
            dh->ExtractMax(n);
            out << dh->getCount() << " ";
            dh->printOrdered(out);
            break;
        }
        case 'b':
        {
            bool barray[MAX];
            for(int i=0;i<n;i++){
                in >> barray[i];
            }
            Heap<bool> *bh = new Heap<bool>(barray,n);
            bh->BuildMaxHeap();
            bh->ExtractMax(n);
            out << bh->getCount() << " ";
            bh->printOrdered(out);
            break;
        }
        case 'c':
        {
            char carray[MAX];
            for(int i=0;i<n;i++){
                in >> carray[i];
            }
            Heap<char> *ch = new Heap<char>(carray,n);
            ch->BuildMaxHeap();
            ch->ExtractMax(n);
            out << ch->getCount() << " ";
            ch->printOrdered(out);
            break;
        }
        default:
            break;

        }
    }
}