#include <iostream>
#include <fstream>
#define MAX 201

using namespace std;

template<class T> class MinHeap{
private:
    T* A;
    int size;
    int index;
    int _Parent(int x){return x>>1;}
    int _Left(int x){return x<<1;}
    int _Right(int x){return (x<<1)|1;}
    int _Swap(T& a, T& b){
        T t = a;
        a = b;
        b = t;
    }
    int _Heapify(int x){
        int l = _Left(x);
        int r = _Right(x);
        int max = x;
        if(A[max] > A[l] && l <= size) max = l;
        if(A[max] > A[r] && r <= size) max = r;
        if(max != x){
            _Swap(A[max],A[x]);
            _Heapify(max);
        }
    }
public:
    MinHeap(T* array, int n){
        A = new T[n+1];
        size = n;
        for(int i=0;i<n;i++){
            A[i+1] = array[i];
        }
    }
    MinHeap(int size){
        A = new T[size+1];
        this->size = size;
        index = 1;
    }
    
    void Enqueue(T k){
        int x = index;
        A[x] = k;
        index ++;

        while(A[x] < A[_Parent(x)] && x > 1){
            _Swap(A[x],A[_Parent(x)]);
            x = _Parent(x);
        }
    }
    void Print(ofstream &out){
        for(int i = 1; i<=size; i++){
            out << A[i] << " ";
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
            MinHeap<int>* ih = new MinHeap<int>(n);
            int a;
            for(int i=0;i<n;i++){
                in >> a;
                ih->Enqueue(a);
            }
            ih->Print(out);
            break;
        }
        case 'd':
        {
            MinHeap<double>* dh = new MinHeap<double>(n);
            double a;
            for(int i=0;i<n;i++){
                in >> a;
                dh->Enqueue(a);
            }
            dh->Print(out);
            break;
        }
        case 'b':
        {
            MinHeap<bool>* bh = new MinHeap<bool>(n);
            bool a;
            for(int i=0;i<n;i++){
                in >> a;
                bh->Enqueue(a);
            }
            bh->Print(out);
            break;
        }
        case 'c':
        {
            MinHeap<char>* ch = new MinHeap<char>(n);
            char a;
            for(int i=0;i<n;i++){
                in >> a;
                ch->Enqueue(a);
            }
            ch->Print(out);
            break;
        }
        default:
            break;

        }
    }

}