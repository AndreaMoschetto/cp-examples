#include <iostream>
#include <fstream>
#define MAX 201
using namespace std;

template <class T> class Heap{
private:
    T *a;
    int size;
    void _Swap(T &a, T&b){
        T t = a;
        a = b;
        b = t;
    }
    int _Left(int i){return i<<1;}
    int _Parent(int i){return i>>1;}
    int _Right(int i){return (i<<1) | 1;}

    void _Heapify(int x){
        int l = _Left(x);
        int r = _Right(x);
        int max = x;
        if(a[max] < a[l] && l <= size) max = l;
        if(a[max] < a[r] && r <= size)  max = r;
        if(max != x){
            _Swap(a[max],a[x]);
            _Heapify(max);
        }

    }
public:
    Heap(T *array, int n){
        this->a = new T[n+1];
        for(int i=0;i<n;i++)
            a[i+1] = array[i];
        size = n;
    }
    void BuildMaxHeap(){
        for(int i = (size>>1); i>=1; i--){
            _Heapify(i);
        }
    }
    void printArray(ofstream &out){
        for(int i = 1; i<= size; i++){
            out << a[i] << " ";
        }
        out << endl;
    }
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
            ih->printArray(out);
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
            dh->printArray(out);
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
            bh->printArray(out);
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
            ch->printArray(out);
            break;
        }
        default:
            break;

        }
    }

}