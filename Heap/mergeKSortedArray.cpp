#include<bits/stdc++.h>
using namespace std;

//We have to store 3 data from each array element
//array number, element data, element index
//pair first-> element data
//pair second->first -> array number
//pair second ->second ->index number
#define pii pair<int,pair<int,int>>

vector<int> mergeSortedKArray(vector<vector<int>>&sortedArray){
    vector<int>ans;
    //create a min Heap
    priority_queue<pii,vector<pii>,greater<pii>> minHeap;
    
    //Push the data in minHeap
    for(int i=0;i<sortedArray.size();i++){
        minHeap.push({sortedArray[i][0],{i,0}});
    }
    //Min Heap will store the smallest element in top always
    while(!minHeap.empty()){
        pii curr = minHeap.top();
        minHeap.pop();
        //Push top smallest element in the ans array 
        ans.push_back(curr.first);
        //i -> array number
        //j -> index
        int i = curr.second.first;
        int j = curr.second.second;
        //Update the index to next element of that array number array
        if(j+1<sortedArray[i].size()){
            minHeap.push({sortedArray[i][j+1],{i,j+1}});
        }
    }
    return ans;
}

int main(){
    int k;
    cin>>k;
    vector<vector<int>>sortedArray(k);
    for(int i=0;i<k;i++){
        int n;
        cin>>n;
        sortedArray[i] = vector<int>(n);
        for(int j=0;j<n;j++){
            cin>>sortedArray[i][j];
        }
    }

    vector<int>ans = mergeSortedKArray(sortedArray);

    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}