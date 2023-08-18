/*
    Maximum Xor Queries

    Problem Statement:  You are given an array/list ‘ARR’ consisting of ‘N’ non-negative integers. You are also given a list ‘QUERIES’ 
                        consisting of ‘M’ queries, where the ‘i-th’ query is a list/array of two non-negative integers ‘Xi’, ‘Ai’, i.e ‘QUERIES[i]’ = [‘Xi’, ‘Ai’]. The answer to the ith query, i.e ‘QUERIES[i]’ is the maximum bitwise xor value of ‘Xi’ with any integer less than or equal to ‘Ai’ in ‘ARR’. You should return an array/list consisting of ‘N’ integers where the ‘i-th’ integer is the answer of ‘QUERIES[i]’.

    Problem Link:   https://www.codingninjas.com/studio/problems/maximum-xor-with-an-element-from-array_1382020?leftPanelTab=0
                    https://leetcode.com/problems/maximum-xor-with-an-element-from-array/

    Refer:  https://takeuforward.org/trie/maximum-xor-queries-trie/
            https://www.youtube.com/watch?v=Q8LhG9Pi5KM&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=11
*/

#include<bits/stdc++.h>
using namespace std;

//Brute Force
vector<int> getMaxQueriesB(vector<int> &arr, vector<vector<int>> &queries){
    vector<int> ans;
    int maxXor = INT_MIN;
    for(int i=0; i<queries.size(); i++){
        int xi = queries[i][0], ai = queries[i][1];
        for(int j=0; j<arr.size(); j++){
            if(arr[j] <= ai){
                maxXor = max(maxXor,arr[j]^xi);
            }
        }
        ans.push_back(maxXor);
    }
    return ans;
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

vector<int> getMaxQueries(vector<int> &arr, vector<vector<int>> &queries){
    vector<int> ans(queries.size(),0);
    //O(N logN)
    sort(arr.begin(), arr.end());

    //we create a offline query
    //          ai         xi   ind
    vector<pair<int, pair<int, int>>> offlineQuery;
    //insert the query in the offline query

    for(int i=0; i<queries.size(); i++){
        offlineQuery.push_back({queries[i][1], {queries[i][0], i}});
    }

    //sort the offline query according to ai
    //O(Q logQ)
    sort(offlineQuery.begin(), offlineQuery.end());
    Trie trie;
    int ind = 0;
    //O( Q*32 + N*32)
    for(int i=0; i<queries.size(); i++){
        int ai = offlineQuery[i].first;
        int xi = offlineQuery[i].second.first;
        int queryInd = offlineQuery[i].second.second;

        
        //we only insert element which are less then ai
        while(ind < arr.size() && arr[ind] <= ai){
            trie.insert(arr[ind]);
            ind++;
        }
        //if ind == 0 means no element in the array is greater then ai
        if(ind == 0) ans[queryInd] = -1;
        else    ans[queryInd] = trie.getMax(xi);   
    }
    return ans;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> arr(n);
    vector<vector<int>> queries(m, vector<int> (2));
    for(auto &i:arr)    cin>>i;
    for(auto &i:queries){
        for(auto &j:i){
            cin>>j;
        }
    }
    vector<int> ans = getMaxQueriesB(arr,queries);

    for(auto i:ans)
        cout<<i<<" ";

    return 0;
}