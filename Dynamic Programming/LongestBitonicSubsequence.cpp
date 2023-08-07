/*
    Longest Bitonic Subsequence

    Problem Statement:  Given an array, ‘Arr’ of length ‘n’, find the longest bitonic subsequence.
                        A bitonic subsequence is a subsequence of an array in which the elements can be any of these three:
                            First, increase till a point and then decrease.
                            Goes on increasing (Longest increasing subsequence)
                            Goes on decreasing (Longest decreasing subsequence)

    Problem Link:   https://www.codingninjas.com/studio/problems/longest-bitonic-sequence_1062688

    Refer:  https://takeuforward.org/data-structure/longest-bitonic-subsequence-dp-46/
            https://www.youtube.com/watch?v=y4vN0WNdrlg&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=47

*/

#include<bits/stdc++.h>
using namespace std;

//TC:   O(n2) + O(n2)
//SC:   O(n)
int longestBitonicSubsequence(vector<int> &arr){
    int n = arr.size();
    vector<int> dp1(n,1), dp2(n,1);
    int maxi = 1;

    for(int i=1; i<n; i++){
        for(int j=0; j<i; j++){
            if(arr[i] > arr[j]){
                dp1[i] = max(dp1[i], 1+dp1[j]);
            }
        }
    }

    for(int i=n-1; i>=0; i--){
        for(int j=n-1; j>i; j--){
            if(arr[i] > arr[j]){
                dp2[i] = max(dp2[i], 1+dp2[j]);
            }
        }
		maxi = max(maxi, dp1[i] + dp2[i] - 1);
    }

    return maxi;
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;
    return 0;
}