#include<bits/stdc++.h>
using namespace std;

//Approach 1: POWER SET 
//Time Complexity : O(N.2^N)
//Space Complexity : O(1) ignoring the auxillary 2d array as it is return 
vector<vector<int>>generateSubsequenceUsingPowerSet(vector<int>&nums){
    //Defining the 2d array size to the 2^n
    vector<vector<int>>ans(pow(2,nums.size()));
    for(int i =0 ;i<(1<<nums.size());i++){
        for(int j = 0;j<nums.size();j++){
            //Only set bit positioned indexed element in array is pushed to ans array
            if(i & 1<<j){
                ans[i].push_back(nums[j]);
            }
        }
    }
    return ans;
}

//Approach 2: Recursive approach
//Time Complexity: O(2^n)
//Space Complexity: O(n)
void generateSubsequenceUsingRecursion(vector<int>&nums, int idx, vector<int>temp, int &index, vector<vector<int>>&ans){
    if(idx>=nums.size()){
        ans[index] = temp;
        index++;
        return;
    }
    temp.push_back(nums[idx]);
    //Take the element to subsequence
    generateSubsequenceUsingRecursion(nums,idx+1,temp,index,ans);
    //remove the element to make another subsequnce 
    temp.pop_back();
    //doesn't take the element 
    generateSubsequenceUsingRecursion(nums,idx+1,temp,index,ans);
}


int main(){
    int n;
    cin>>n;
    vector<int>nums(n);
    for(auto &i:nums){
        cin>>i;
    }
    vector<vector<int>>ans(pow(2,nums.size()));
    vector<int>temp;
    int index = 0;
    generateSubsequenceUsingRecursion(nums,0,temp,index,ans);
    for(auto i:ans){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<"\n";
    }
    return 0;
}