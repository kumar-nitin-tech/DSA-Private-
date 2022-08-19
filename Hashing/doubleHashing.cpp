#include<bits/stdc++.h>
using namespace std;

class doubleHashing{
    int *table;
    int size;

    public:
    doubleHashing(int Size){
        size  = Size;
        table = new int[size];
        for(int i=0;i<size;i++){
            table[i] = INT_MIN;
        }
    }

    //hash function 1
    int hash1(int x){
        return x%size;
    }

    //hash function 2
    int hash2(int x){
        return 1+(x%(size-1));
    }

    //insertion
    void insert(int x){
        int k1 = hash1(x);
        int k2 = hash2(x);
        if(table[k1] == INT_MIN){
            table[k1] = x; 
        }
        else if(table[k2] == INT_MIN){
            table[k2] = x;
        }
        else{
            int k = 0;
            for(int i=1;i<size;i++){
                k = (k1+i*k2)%size;
                if(table[k] == INT_MIN){
                    table[k] = x;
                    return;
                }
            }
        }
    }

    //serach
    bool search(int x){
        int k1 = hash1(x);
        int k2 = hash2(x);

        if(table[k1] == x){
            return true;
        }
        else if(table[k2] == x){
            return true;
        }
        else{
            int k = 0;
            for(int i=1;i<size;i++){
                k = (k1+i*k2)%size;
                if(table[k] == x){
                    return true;
                }
            }
            return false;
        }
    }

    //delete
    void Delete(int x){
        int k1 = hash1(x);
        int k2 = hash2(x);

        if(table[k1] == x){
            table[k1] = INT_MIN;
            return;
        }
        else if(table[k2] == x){
            table[k2] = INT_MIN;
            return;
        }
        else{
            int k = 0;
            for(int i=1;i<size;i++){
                k = (k1+i*k2)%size;
                if(table[k] == x){
                    table[k] = INT_MIN;
                    return;
                }
            }
        }
    }

};

int main(){
    doubleHashing h(7);
    h.insert(37);
    h.insert(25);
    h.insert(12);
    h.insert(40);
    h.insert(74);
    if(h.search(40))
        cout<<"40 found"<<endl;
    if(h.search(74))
        cout<<"74 found"<<endl;
    h.Delete(74);
    if(!h.search(74))
        cout<<"After deleting 74, 74 is not found";
    return 0;
}