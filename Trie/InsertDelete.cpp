/*
    Trie:   It is Multi way Tree in which we store the string in such a way that we can search any prefix or word in less time and less 
            space. 
            It is also called Prefix Tree or Retrival Tree
*/

#include<bits/stdc++.h>
using namespace std;

//Structure of Trie
struct Node{
    // Node base array which link all the character and store it in trie
    Node* link[26];
    //To keep the track of the character in the word
    bool flag = false;

    //Function to check if the char is present in the trie or not
    bool contain(char c){
        return (link[c - 'a'] != NULL);
    }

    //putting the char in the trie node
    void put(char c, Node* node){
        link[c-'a'] = node;
    }

    //give the trie reference for the char
    Node* get(char c){
        return link[c - 'a'];
    }

    //set the end of the word
    void setEnd(){
        flag = true;
    }

    //check if the char is end
    bool isEnd(){
        return flag;
    }
};


//Construction of Trie
class Trie{
    //We always start with the root node 
    private:    
        Node * root;
    
    public:
    //Construct the node for the trie
    Trie() {
        root = new Node();
    }

    //Insert 
    //TC: O(L)
    void insert(string word){
        //We create a dummy node to track the trie
        Node* node = root;
        for(int i=0; i<word.size(); i++){
            //There are things to keep in mind that we need check if there already exist the word char or not 
            //so for that we check if the char already exists in trie
            //This if statement check if the char is not present in the trie 
            if(!node->contain(word[i])){
                //so we create a reference trie for the char
                //We are refernce this char to new trie and inserted in the trie
                node->put(word[i],new Node());
            }
            //now we have to move to new reference trie so
            node = node->get(word[i]);
        }
        //so we have reach the end of the word we set the end of trie 
        node->setEnd();
    }

    //Search 
    bool searchWord(string word){
        Node* node = root;
        for(int i=0; i<word.size(); i++){
            if(!node->contain(word[i])){
                return false;
            }
            node = node->get(word[i]);
        }
        return node->isEnd();
    }

    //Search for starting char / prefix
    bool startWith(string prefix){
        Node* node = root;
        for(int i=0; i<prefix.size(); i++){
            if(!node->contain(prefix[i])){
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }

};

int main(){
    cout<<sizeof(long long);
    return 0;
}