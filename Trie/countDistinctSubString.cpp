/*
    Number of Distinct Substrings in a String

    Problem Statement:  Given a string of alphabetic characters. Return the count of distinct substrings of the string(including the 
                        empty string) using the Trie data structure.  

    Problem Link:   https://www.codingninjas.com/studio/problems/count-distinct-substrings_985292

    Refer:  https://takeuforward.org/data-structure/number-of-distinct-substrings-in-a-string-using-trie/
            https://www.youtube.com/watch?v=RV0QeTyHZxo&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=4

*/

#include<bits/stdc++.h>
using namespace std;

struct Node{
    Node* link[26];

    bool containKey(char ch){
        return link[ch-'a'];
    }
    void put(char ch, Node* node){
        link[ch-'a'] = node;
    }

    Node* get(char ch){
        return link[ch - 'a'];
    }
};

int countDistinctSubstrings(string &s) {
    Node* root = new Node();
    int count = 0;
    for(int i=0; i<s.size(); i++){
        Node *node = root;
        for(int j=i; j<s.size(); j++){
            if(!node->containKey(s[j])){
                count++;
                node->put(s[j], new Node());
            }
            node = node->get(s[j]);
        }
    }
    return count+1;
}

int main(){
    string s;
    cin>>s;
    cout<<countDistinctSubstrings(s);
    return 0;
}