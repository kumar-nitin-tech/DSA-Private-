#include<bits/stdc++.h>
using namespace std;

//printing frequency in any order 
void printFrequency(vector<int>&nums){
    unordered_map<int,int>count;
    for(int i=0;i<nums.size();i++){
        count[nums[i]]++;
    }

    unordered_map<int,int>::iterator it;
    for(it=count.begin();it!=count.end();it++){
        cout<<it->first<<" "<<it->second<<"\n";
    }
}

//printing frequency in given order

void printFrequencyOrder(vector<int>&nums){
    map<int,int>count;
    for(int i=0;i<nums.size();i++){
        count[nums[i]]++;
    }

    map<int,int>::iterator it;
    for(it=count.begin();it!=count.end();it++){
        cout<<it->first<<" "<<it->second<<"\n";
    }
}

int main(){
    int n;
    cin>>n;
    vector<int>nums(n);
    for(auto &i:nums){
        cin>>i;
    }
    printFrequency(nums);
    
    cout<<"\n\n";

    printFrequencyOrder(nums);
    return 0;
}