#include<bits/stdc++.h>
using namespace std;

//Time complexity: O(n^2)
//Space complexity: O(1)
int countSumSUbarrayBrute(vector<int>&nums){
    int count = 0;
    for(int i=0;i<nums.size();i++){
        int sum = 0;
        for(int j=i;j<nums.size();j++){
            sum += nums[j];
            if(sum == 0){
                count++;
            }
        }
    }
    return count;
}

//Better Approach using HashMap
//Time Complexity : O(n)
//Space Comlexity : O(n)
int countSubarraySumZeroOptimal(vector<int>&nums){
    int count = 0;
    unordered_map<int,int>uMap;
    int sum = 0;
    uMap[0] = 1;
    for(int i=0;i<nums.size();i++){
        sum += nums[i];
        if(uMap.find(sum) != uMap.end()){
            count += uMap[sum];
            uMap[sum] = uMap[sum]+1;
        }
        else{
            uMap[sum] = 1;
        }
    }
    return count;
}

int main(){
    int n;
    cin>>n;
    vector<int>nums(n);
    for(auto &i:nums){
        cin>>i;
    }
    cout<<countSubarraySumZeroOptimal(nums);
    return 0;
}