#include <iostream>
#include <fstream>
#include <string>
#define RED 0
#define BLACK 1
#define MAX 1001

using namespace std;

template <class T> class Node{
private:
    T* key;
    Node<T> *parent, *left, *right;
    int color;


public:
    Node(T* key){
        this->key = key;
        parent = left = right = NULL;
        color = RED;
    }

    Node<T>* getParent(){return parent;}
    Node<T>* getLeft(){return left;}
    Node<T>* getRight(){return right;}
    T* getKey(){return key;}
    int getColor(){return color;}

    void setParent(Node<T>* p){this->parent = p;}
    void setLeft(Node<T>* l){this->left = l;}
    void setRight(Node<T>* r){this->right = r;}
    void setKey(T* k){this->key = k;}
    void setColor(int c){this->color = c;}
};

template <class H> class BST{
private:
    Node<H>* root;
    int n; //number of nodes in BST
    //Node<H>* current;

   
    Node<H>* _rsearch(Node<H>* x, H k){
        if(*x->getKey() == k || !x) return x;
        if(k<=*x->getKey()) return _rsearch(x->getLeft(),k);
        return _rsearch(x->getRight(),k);
    }

    Node<H>* _rmin(Node<H>* y){
        if(!y || !y->getLeft())return y;
        return _rmin(y->getLeft());
    }

    void _canc(Node<H> *x, H k){
        Node<H>* y = _rsearch(x,k);
        if(!y)return;
        if(y->getRight() && y->getLeft()){
            Node<H>* suc = _rmin(y->getRight());
            y->setKey(suc->getKey());
            _canc(suc, *suc->getKey());
        }
        else{
            Node<H>* child = y->getRight();
            if(!child) child = y->getLeft();
            Node<H>* p = y->getParent();

            if(p){
                if(k < *(p->getKey())) p->setLeft(child);
                else p->setRight(child);
            }
            else root = child;

            if(child) child->setParent(p);
            n--;
        }
    }

    void _preorder(ofstream &out, Node<H> *y){
        if(y){
            string c = y->getColor() == RED?"R":"B";
            out << "(" << *(y->getKey()) << " " << c << ") ";
            _preorder(out,y->getLeft());
            _preorder(out,y->getRight());
        }
    }
    void _inorder(ofstream &out, Node<H> *y){
        if(y){
            _inorder(out,y->getLeft());
            string c = y->getColor() == RED?"R":"B";
            out << "(" << *(y->getKey()) << " " << c << ") ";
            _inorder(out,y->getRight());
        }
    }
    void _postorder(ofstream &out, Node<H> *y){
        if(y){
            _postorder(out,y->getLeft());
            _postorder(out,y->getRight());
            string c = y->getColor() == RED?"R":"B";
            out << "(" << *(y->getKey()) << " " << c << ") ";
        }
    }

    void _RightRotation(Node<H>* y){
        if(y && y->getLeft()){
            Node<H>* l = y->getLeft();
            Node<H>* p = y->getParent();
            Node<H>* g = l->getRight();
            
            if(p){
                if(*y->getKey() <= *(p->getKey())) p->setLeft(l);
                else p->setRight(l);
            }
            else root = l;

            l->setParent(p);
            y->setParent(l);
            l->setRight(y);
            
            y->setLeft(g);
            if(g){
                g->setParent(y); 
            } 
        }
        root->setColor(BLACK);
    }
    void _LeftRotation(Node<H>* y){
        if(y && y->getRight()){
            Node<H>* r = y->getRight();
            Node<H>* p = y->getParent();
            Node<H>* g = r->getLeft();

            if(p){
                if(*y->getKey() <= *(p->getKey())) p->setLeft(r);
                else p->setRight(r);
            }
            else root = r;
            

            r->setParent(p);
            y->setParent(r);
            r->setLeft(y);

            y->setRight(g);
            if(g){
                g->setParent(y);
            } 
        }
        root->setColor(BLACK);
    }

    void _Balance(Node<H> *z){
        Node<H> *p = z->getParent();
        if(p == root || !p || (z->getColor() == RED && p->getColor() == BLACK)){
            //z->setColor(RED);
            return;
        }

        Node<H> *nonno, *zio;
        bool pIsLeft;

        nonno = p->getParent();
        if(p == nonno->getLeft()){
            zio = nonno->getRight();
            pIsLeft = true;
        } 
        else {
            zio = nonno->getLeft();
            pIsLeft = false;
        }
        
        if(!zio || zio->getColor()==BLACK){//y è nero o nill
            if(z == p->getLeft() xor pIsLeft){//z è interno
                if(pIsLeft) _LeftRotation(p);
                else _RightRotation(p);
                _Balance(p);
            }
            else{//z è esterno
                p->setColor(BLACK);
                nonno->setColor(RED);
                if(pIsLeft) _RightRotation(nonno);
                else _LeftRotation(nonno);
                _Balance(z);
            }
        }
        else{//y è rosso
            p->setColor(BLACK);
            zio->setColor(BLACK);
            nonno->setColor(RED);
            _Balance(nonno);
        }
        root->setColor(BLACK);
    }

public:
    BST(){
        root = NULL;
        n = 0;
    }

    void insert(H x){
        Node<H>* tmp = root;
        Node<H>* pre = NULL;
        while(tmp){
            pre = tmp;
            if(x <= *(tmp->getKey()))tmp = tmp->getLeft();
            else tmp = tmp->getRight();
        }
        Node<H> *y = new Node<H>(new H(x));
        y->setParent(pre);
        if(!pre){ root = y; root->setColor(BLACK);}
        else{
            if(x <= *(pre->getKey())) pre->setLeft(y);
            else pre->setRight(y);
            _Balance(y);
        }
        
        n++;
    }

    H search(H x){
        return *(_rsearch(root,x)->getKey());
    }

    void canc(H x){
        Node<H>* tmp = _rsearch(root,x);
        if(tmp) _canc(tmp, x);
    }

    void RightRotation(H x){
        Node<H>* y = _rsearch(root,x);
        _RightRotation(y);
        return;
    }
    
    void LeftRotation(H x){
        Node<H>* y = _rsearch(root,x);
        _LeftRotation(y);
    }

    void preorder(ofstream &out){
        _preorder(out,root);
    }
    void inorder(ofstream &out){
        _inorder(out,root);
    }
    void postorder(ofstream &out){
        _postorder(out,root);
    }

};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    string t;
    char c;
    BST<double> *bst;
    double x;

    for(int k=0;k<100;k++){
        in >> t >> n >> t;

        bst = new BST<double>();

        for(int i=0;i<n;i++){
            in >> x;
            bst->insert(x);
        }
        
        if(t == "preorder") bst->preorder(out);
        else if(t == "inorder") bst->inorder(out);
        else bst->postorder(out);

        out << endl;

        delete(bst);
    }
    in.close();
    out.close();
    return 0;
    
}