#include<bits/stdc++.h>
using namespace std;

//Code for maximum non adjacent sum
int maxSumSubsequenceTS(vector<int> &nums){
    int prev = nums[0];
    int prev2 = 0;
    for(int i=1;i<nums.size();i++){
        int pick = nums[i] + prev2;
        int notPick = 0 + prev;
        int ans = max(pick,notPick);
        prev2 = prev;
        prev = ans;
    }
    return prev;
}

//for House robber problem or for circular array whose first and last element is adjacent
int houseRobber(vector<int> &arr){
    //2 arrays for storing the array element without first once and last once
    vector<int> temp1, temp2;
    int n = arr.size();

    if(n==1){
        return arr[0];
    }
    for(int i=0;i<n;i++){
        // not including first element
        if(i!=0) temp1.push_back(arr[i]);

        //not including last element
        if(i!=n-1) temp2.push_back(arr[i]);
    }

    return max(maxSumSubsequenceTS(temp1), maxSumSubsequenceTS(temp2));
    
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr){
        cin>>i;
    }
    cout<<houseRobber(arr);
    return 0;
}