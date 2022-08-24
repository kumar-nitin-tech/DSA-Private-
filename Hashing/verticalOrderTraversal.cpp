//Problem: We have to print the binary tree in level order traversal
#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node*left;
    node*right;

    node(int x){
        data = x;
        left = NULL;
        right = NULL;
    }
};

//Time complexity: O(NlogN)
//Space complexity: O(n)
vector<vector<int>> verticalTraversal(node* root){
    //First we have to map level with the horizaontal distance root(0,0) and its node value and node value should be in sorted order for that 
    //we can use multiset or normal vector(if used should be sorted at last)
    map<int,map<int,multiset<int>>> mapDistance;
    //As we are using level Order traversal to map values so we use queue
    queue<pair<node*,pair<int,int>>> q;
    q.push({root,{0,0}});

    while(!q.empty()){
        //in place of auto we can take pair<node*,pair<int,int>> p;
        auto p = q.front();
        q.pop();
        node* temp = p.first;
        //level if is y axis and horizontal is x axis
        int level = p.second.first, horizontal = p.second.second;
        //Inserting the value of node in position of vertical and horizontal and mapping the position to its value
        mapDistance[horizontal][level].insert(temp->data);

        if(temp->left != NULL){
            q.push({temp->left,{level+1,horizontal-1}});
        }
        if(temp->right != NULL){
            q.push({temp->right,{level+1,horizontal+1}});
        }
    }

    //Mapping all value to its level and horizontal distance is done 

    vector<vector<int>>ans;

    for(auto i:mapDistance){
        //to store the multiset value and push the vector in ans
        vector<int>temp;
        for(auto j:i.second){
            temp.insert(temp.end(),j.second.begin(),j.second.end());
        }
        ans.push_back(temp);
    }
    return ans;
}

int main(){
    node* root = new node(1);
    root -> left = new node(2);
    root -> left -> left = new node(4);
    root -> left -> right = new node(10);
    root -> left -> left -> right = new node(5);
    root -> left -> left -> right -> right = new node(6);
    root -> right = new node(3);
    root -> right -> left = new node(9);
    root -> right -> right = new node(10);
    vector<vector<int>>ans;
    ans = verticalTraversal(root);
    for(auto i:ans){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    return 0;
}