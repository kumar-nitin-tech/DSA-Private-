/*
    Maximum XOR of Two Numbers in an Array

    Problem Statement:  You are given two arrays of non-negative integers say ‘arr1’ and ‘arr2’ of sizes N and M respectively. Find the 
                        maximum value of ( ‘A’ xor ‘B’ ) where ‘A’ and ‘B’ are any elements from ‘arr1’ and ‘arr2’ respectively and ‘xor’ represents the bitwise xor operation. Maximum XOR of Two Numbers in an Array.  

    Problem Link:   https://www.codingninjas.com/studio/problems/maximum-xor_973113

    Refer:  https://takeuforward.org/data-structure/maximum-xor-of-two-numbers-in-an-array/
            https://www.youtube.com/watch?v=EIhAwfHubE8&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=7

*/

#include<bits/stdc++.h>
using namespace std;

//Brute Force
//TC: O(n*m)
//Sc: O(1)
int maximumXor(vector<int> &arr1, vector<int> &arr2){
    int maxXOR = 0;
    for(int i=0; i<arr1.size(); i++) {
        for(int j=0; j<arr2.size(); j++) {
            int tempXor = arr1[i] ^ arr2[j];
            maxXOR = max(maxXOR,tempXor);
        }
    }
    return maxXOR;
}

//using Trie
struct Node{
    Node* link[2];

    bool containKey(int bit){
        return link[bit] != NULL;
    }

    void put(int bit, Node* node){
        link[bit] = node;
    }

    Node* get(int bit){
        return link[bit];
    }

};

class Trie{
    private:
        Node* root;

    public:
        Trie(){
            root = new Node();
        }

        void insert(int num){
            Node* node = root;
            for(int i=31; i>=0; i--){
                int bit = (num>>i) & 1;
                if(!node->containKey(bit)){
                    node->put(bit,new Node());
                }
                node = node->get(bit);
            }
        }

        int getMax(int num){
            Node* node = root;
            int maxNum = 0;
            //iterate from 31 to 0
            for(int i=31; i>=0; i--){
                int bit = (num>>i) & 1;
                //if the trie contain opposite of bit we will consider it in order to maximise the output
                if(node->containKey(1-bit)){
                    maxNum = maxNum | (1<<i);
                    //move to the reference of that bit
                    node = node->get(1-bit);
                }
                else{
                    node = node->get(bit);
                }
            }
            return maxNum;
        }
};

//TC: O(n*32) + O(m*32)
int maximumXORTrie(vector<int> &arr1, vector<int> &arr2){
    Trie trie;
    for(auto &it:arr1){
        trie.insert(it);
    }
    int maxi = 0;
    for(auto &it:arr2){
        maxi = max(maxi,trie.getMax(it));
    }
    return maxi;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> arr1(n);
    vector<int> arr2(m);

    for(auto &i:arr1)   cin>>i;
    for(auto &i:arr2)   cin>>i;

    cout<<maximumXORTrie(arr1,arr2);
    return 0;
}