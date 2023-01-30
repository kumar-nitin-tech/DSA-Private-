
/*
    Huffman Encoding

    Given a string S of distinct character of size N and their corresponding frequency f[ ]
    i.e. character S[i] has f[i] frequency. Your task is to build the Huffman tree print all the huffman codes in preorder traversal of the tree.
*/

#include<bits/stdc++.h>
using namespace std;

// Nodes for the encoding
class node{
    public:
    int data;
    node* left, *right;

    node(int x){
        data = x;
        left = NULL;
        right = NULL;
    }
};

void traverse(node* root, string temp, vector<string> &ans){
    if(root->left == NULL && root->right == NULL){
        ans.push_back(temp);
        return;
    }
    traverse(root->left,temp+'0',ans);
    traverse(root->right,temp+'1',ans);
}

class cmp{
    public:
    bool operator()(node *a, node *b){
        return a->data > b->data;
    }
};

vector<string> huffmanEncoding(string S, vector<int> f, int N){
    priority_queue<node*, vector<node*>, cmp>pq;

    for(int i=0;i<N;i++){
        node* temp = new node(f[i]);
        pq.push(temp);
    }

    while(pq.size() > 1){
        node* left = pq.top();
        pq.pop();
        node* right = pq.top();
        pq.pop();
        node *newNode = new node(left->data + right->data);
        newNode ->left = left;
        newNode ->right = right;
        pq.push(newNode);
    }
    node* root = pq.top();
    vector<string> ans;
    string temp = "";
    traverse(root,temp,ans);
    return ans;
}

int main(){
    int N;
    cin>>N;
    string S;
    cin>>S;
    vector<int> f(N);
    for(auto &i:f){
        cin>>i;
    }
    vector<string>ans = huffmanEncoding(S,f,N);
    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}