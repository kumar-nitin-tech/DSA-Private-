#include<bits/stdc++.h>
using namespace std;

//Structure of Trie
struct Node{
    Node* link[26];
    int endCount = 0;
    int prefixCount = 0;

    bool containKey(char ch){
        return link[ch - 'a'] != NULL;
    }
    
    void put(char ch, Node* node){
        link[ch-'a'] = node;
    }

    Node* get(char ch){
        return link[ch - 'a'];
    }

    void increasePrefix(){
        prefixCount++;
    }
    void setEnd(){
        endCount++;
    }

    void deleteEnd(){
        endCount--;
    }

    void reducedPrefix(){
        prefixCount--;
    }

    int getEnd(){
        return endCount;
    }

    int getPrefix(){
        return prefixCount;
    }
};

class Trie{
    private:
        Node *root;
    
    public:
        //Constructor
        Trie(){
            root = new Node();
        }

        //Insert
        void insert(string word){
            //dummy node
            Node* node = root;
            for(int i=0; i<word.size(); i++){
                if(!node->containKey(word[i])){
                    node->put(word[i], new Node());
                }
                node = node->get(word[i]);
                node->increasePrefix();
            }
            node->setEnd();
        }

        //Count the word 
        int countWordsEqualTo(string &word){
            //dummy node
            Node* node = root;
            //iterating over string word
            for(int i=0; i<word.size(); i++){
                if(!node->containKey(word[i])){
                    return 0;
                }
                node = node->get(word[i]);
            }
            return node->getEnd();
        }

        int countWordsStartingWith(string &word){
            Node* node = root;
            //iterating over string word
            for(int i=0; i<word.size(); i++){
                if(!node->containKey(word[i])){
                    return 0;
                }
                node = node->get(word[i]);
            }
            return node->getPrefix();
        }

        void erase(string word){
            Node* node = root;
            for(int i=0; i<word.size(); i++){
                if(!node->containKey(word[i])){
                    return;
                }
                node = node->get(word[i]);
                node->reducedPrefix();
            }
            node->deleteEnd();
        }
};


int main(){
    int n;
    cin>>n;
    vector<string> word(n);
    for(auto &i:word)   cin>>i;
    Trie trie;
    for(auto i:word){
        trie.insert(i);
    }
    
    string apple = "apps";
    trie.erase(apple);
    cout<<trie.countWordsEqualTo(apple);
    cout<<"\n";
    string app = "app";
    cout<<trie.countWordsStartingWith(app);
    return 0;
}