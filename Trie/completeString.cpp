/*
    Longest Word With All Prefixes

    Problem Statement:  Ninja developed a love for arrays and strings so this time his teacher gave him an array of strings, ‘A’ of size 
                        ‘N’. Each element of this array is a string. The teacher taught Ninja about prefixes in the past, so he wants to test his knowledge. A string is called a complete string if every prefix of this string is also present in the array ‘A’. Ninja is challenged to find the longest complete string in the array ‘A’.If there are multiple strings with the same length, return the lexicographically smallest one and if no string exists, return "None".

    Problem Link:   https://www.codingninjas.com/studio/problems/complete-string_2687860

    Refer:  Notes
            https://www.youtube.com/watch?v=AWnBa91lThI&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=3

*/

#include<bits/stdc++.h>
using namespace std;

//Structure of Trie
struct Node{
    Node* link[26];
    bool flag = false;

    bool containKey(char ch){
        return link[ch - 'a'];
    }

    void put(char ch, Node* node){
        link[ch - 'a'] = node;
    }

    Node* get(char ch){
        return link[ch - 'a'];
    }

    void setEnd(){
        flag = true;
    }

    bool isEnd(){
        return flag;
    }
};

class Trie{
    private:
        Node* root;
    
    public:
        Trie() {
            root = new Node();
        }

        void insert(string word){
            Node* node = root;
            for(int i=0; i<word.size(); i++){ 
                if(!node->containKey(word[i])){
                    node->put(word[i],new Node());
                }
                node = node->get(word[i]);
            }
            node->setEnd();
        }

        bool checkPrefix(string &word){
            bool fl = true;
            Node* node = root;
            for(int i=0; i<word.size(); i++){
                if(node->containKey(word[i])){
                    node = node->get(word[i]);
                    if(node->isEnd() == false)  return false;
                }else{
                    return false;
                }
            }
            return true;
        }
};

//TC: O(n * l) + O(n * l)

string completeString(vector<string> &a, int n){
    Trie trie;
    for(int i=0; i<n; i++){
        trie.insert(a[i]);
    }
    string longestString = "";
    for(auto &it:a){
        if(trie.checkPrefix(it)){
            if(it.length() > longestString.length()){
                longestString = it;
            }
            else if(it.length() == longestString.length() && it < longestString){
                longestString = it;
            }
        }
    }
    return longestString == "" ? "None" : longestString;
}

int main(){
    int n;
    cin>>n;     
    vector<string> a(n);
    for(auto &i:a)    cin>>i;

    string ans = completeString(a,n);
    cout<<ans;
    return 0;
}