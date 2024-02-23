#include <iostream>
#include <fstream>
#define MAX 201

using namespace std;

template<class T> class MaxHeap{
private:
    T* A;
    int size;
    int index;
    int contHeapify;
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
        contHeapify++;
        
        if(A[max] < A[l] && l < index) max = l;
        if(A[max] < A[r] && r < index) max = r;
        if(max != x){
            _Swap(A[max],A[x]);
            _Heapify(max);
        }
        //else contHeapify--;
    }
public:
    MaxHeap(T* array, int n){
        A = new T[n+1];
        size = n;
        for(int i=0;i<n;i++){
            A[i+1] = array[i];
        }
        contHeapify = 0;
    }
    MaxHeap(int size){
        A = new T[size+1];
        this->size = size;
        index = 1;
        contHeapify = 0;
    }
    
    void Enqueue(T k){
        int x = index;
        A[x] = k;
        index ++;

        while(A[x] > A[_Parent(x)] && x > 1){
            _Swap(A[x],A[_Parent(x)]);
            x = _Parent(x);
        }
    }
    void ExtractMax(){
        _Swap(A[1],A[index-1]);
        index--;
        if(index > 1)
            _Heapify(1);
    }
    void Print(ofstream &out){
        for(int i = 1; i<index; i++){
            out << A[i] << " ";
        }
        out << endl;
    }
    void PrintContHeapify (ofstream &out){
        out << contHeapify << " ";
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    string t;
    int n;
    char c;
    for(int k=0;k<100;k++){
        in >> t >> n;
        switch(t[0]){
        case 'i':
        {
            MaxHeap<int>* ih = new MaxHeap<int>(n);
            int a;
            for(int i=0;i<n;i++){
                in >> c >> c;
                if(c == 'x'){//extract
                    ih->ExtractMax();
                    in >> t;
                }
                else if(c == ':'){//e:
                    in >> a;
                    ih->Enqueue(a);
                }
                
            }
            ih->PrintContHeapify(out);
            ih->Print(out);
            break;
        }
        case 'd':
        {
            MaxHeap<double>* dh = new MaxHeap<double>(n);
            double a;
            for(int i=0;i<n;i++){
                in >> c >> c;
                if(c == 'x'){//extract
                    dh->ExtractMax();
                    in >> t;
                }
                else if(c == ':'){//e:
                    in >> a;
                    dh->Enqueue(a);
                }
            }
            dh->PrintContHeapify(out);
            dh->Print(out);
            break;
        }
        case 'b':
        {
            MaxHeap<bool>* bh = new MaxHeap<bool>(n);
            bool a;
            for(int i=0;i<n;i++){
                in >> c >> c;
                if(c == 'x'){//extract
                    bh->ExtractMax();
                    in >> t;
                }
                else if(c == ':'){//e:
                    in >> a;
                    bh->Enqueue(a);
                }
            }
            bh->PrintContHeapify(out);
            bh->Print(out);
            break;
        }
        case 'c':
        {
            MaxHeap<char>* ch = new MaxHeap<char>(n);
            char a;
            for(int i=0;i<n;i++){
                in >> c >> c;
                if(c == 'x'){//extract
                    ch->ExtractMax();
                    in >> t;
                }
                else if(c == ':'){
                    in >> a;
                    ch->Enqueue(a);
                }
            }
            ch->PrintContHeapify(out);
            ch->Print(out);
            break;
        }
        default:
            break;

        }
    }

}