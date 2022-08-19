//Collision means when hash function genarate same key for different value
//Collision handling in hahsMap is done in two ways 

// Seperate chaining in this we create a linked list in the time of collision (most commonly used and eay to use and understand)

//Close Addressing : In this alternating cells is find to place collision element.
//Close addressing can be done by three ways :
//Linear Probing
//Quadratic probing
//Double Hashing

#include<bits/stdc++.h>
using namespace std;

//Linear Probing
class hashing{
    int *hashTable;
    int size;

    public:
    //constructor
    hashing(int n){
        size = n;
        //delcaring hash Table as array
        hashTable = new int[size];
        
        //Intialising the all array element as minimum value
        for(int i=0;i<size;i++){
            hashTable[i] = INT_MIN;
        }
    }

    //hash Function
    int hash(int x){
        return x%size;
    }

    //insertion 
    //Time complexity : O(1) if directly value is inserted without collision or worst case is O(N)
    void insert(int x){
        int k = hash(x);

        //findig empty cell for insertion if occupied by linear probing
        while(hashTable[k] != INT_MIN ){
            k = (k+1)%size; // this is done so that the k doesn't exceed the index of the table
        }
        hashTable[k] = x;
    }

    //searching
    bool search(int x){
        int k = hash(x);
        while(hashTable[k] != x){
            //if empty cell is found instead of value then given value is not present in table
            if(hashTable[k] == INT_MIN)
                return false;

            k = (k+1)%size;
        }
        return hashTable[k] == x;
    }

    //delete
    void Delete(int x){
        int k = hash(x);

        while(hashTable[k] != x){
            if(hashTable[k] == INT_MIN){
                return;
            }
            k = (k+1)%size;
        } 
        if(hashTable[k] == x){
            hashTable[k] = INT_MIN;
        }
    }
};

//Quadratic Probing

class Hashing{
    int *table;
    int size;
    public:
    Hashing(int n){
        size = n;
        table = new int[size];
        for(int i = 0;i<size;i++){
            table[i] = INT_MIN;
        }
    }

    int hash(int x){
        return x%size;
    }

    //Insertion
    void insert(int x){
        int k = hash(x);
        for(int i=1;i<size;i++){
            if(table[k] == INT_MIN){
                break;
            }
            k = (k+(i*i))%size;
        }
        table[k] = x;
    }


    //search
    bool search(int x){
        int k = hash(x);
        if(table[k] == x){
            return true;
        }
        else{
            for(int i=1;i<size;i++){
                if(table[k] == x){
                    return true;
                }
                k = (k+(i*i))%size;
            }
            return false;
        }
    }

    //deletion
    void Delete(int x){
        int k = hash(x);
        if(table[k] == x){
            table[k] = INT_MIN;
            return;
        }
        for(int i = 1;i<size;i++){
            k = (k+(i*i))%size;
            if(table[k] == x){
                table[k] = INT_MIN;
                break;
            }
        }
    }

};

int main(){
    Hashing h(7);
    h.insert(16);
    h.insert(40);
    h.insert(27);
    h.insert(9);
    h.insert(75);
    if(h.search(75) == true)
         cout<<"75 found"<<endl;
    if(h.search(40))
        cout<<"40 found"<<endl;

    h.Delete(40);
    if(!h.search(40))
        cout<<"After deleting 40, 40 is not found";
    return 0;
}