#include<bits/stdc++.h>
using namespace std;

//Time Complexity: O(n)
//Space Complexity : O(n)
void frequencyOfKDistinctElement(vector<int>&nums, int k){
    unordered_map<int,int> map;
    map[nums[0]] = 1;
    for(int i=1;i<nums.size();i++){
        if(nums[i] == nums[i-1]){
            map[nums[i]]++;
        }
        else{
            if(map.size()>=k){
                break;
            }
            map[nums[i]]++;
        }
    }
    for(auto &i:map){
        cout<<i.first<<" "<<i.second<<"\n";
    }
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int>nums(n);
    for(auto &i:nums){
        cin>>i;
    }
    frequencyOfKDistinctElement(nums,k);
    return 0;
}