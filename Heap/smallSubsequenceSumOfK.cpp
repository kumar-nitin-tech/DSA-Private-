#include<bits/stdc++.h>
using namespace std;

void generateSubsequence(vector<int>&nums, int idx, vector<int>&temp, int &index, vector<vector<int>>&ans){
    if(idx>=nums.size()){
        ans[index] = temp;
        index++;
        return;
    }

    temp.push_back(nums[idx]);
    generateSubsequence(nums,idx+1,temp,index,ans);
    temp.pop_back();
    generateSubsequence(nums,idx+1,temp,index,ans);
}

//Approach 1: Generating all subsequence and summing the subsequence and returning the size of the array
//Time Complexity: O(N.2^N)
//Space Complexity: O(2^N)
int smallestSubsequenceOfKSumBrute(vector<int>&nums, int k){
    vector<int>temp;
    vector<vector<int>>ans(pow(2,nums.size()));
    int index = 0;
    generateSubsequence(nums,0,temp,index,ans);
    int minSize = INT_MAX;
    for(int i=0;i<ans.size();i++){
        int sum = 0;
        for(int j= 0;j<ans[i].size();j++){
            sum += ans[i][j];
        }
        int size = ans[i].size();
        if(sum >= k){
            minSize = min(size,minSize);
        }
    }
    return minSize;
}

//Approach 2: Using maxHeap and greedy approcah to solve the problem
//Time Complexity: O(N.logN)
//Space Complexity: O(N)
int smallestSubsequenceOfKSum(vector<int>&nums, int k){
    priority_queue<int>maxHeap;
    //Sort the array in Descending Order
    for(int i=0;i<nums.size();i++){
        maxHeap.push(nums[i]);
    }
    int count = 0;
    int sum = 0;
    while(!maxHeap.empty()){
        //Adding up the largest element one by one to array
        sum += maxHeap.top();
        count++;
        maxHeap.pop();
        //if the sum is equal to given sum we return the count
        if(sum >= k){
            return count;
        }
    }
    return -1;
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int>nums(n);
    for(auto &i:nums){
        cin>>i;
    }
    cout<<smallestSubsequenceOfKSum(nums,k);
    return 0;
}