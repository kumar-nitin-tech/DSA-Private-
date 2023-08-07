/*
    Longest String Chain

    Problem Statement:  You are given an array of words where each word consists of lowercase English letters.
                        wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.
                        For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
                        A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
                        Return the length of the longest possible word chain with words chosen from the given list of words.  

    Problem Link:   https://leetcode.com/problems/longest-string-chain/
                    https://www.codingninjas.com/studio/problems/longest-string-chain_3752111

    Refer:  https://takeuforward.org/data-structure/longest-string-chain-dp-45/
            https://www.youtube.com/watch?v=YY8iBaYcc4g&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=46

*/

#include<bits/stdc++.h>
using namespace std;

bool compare(string &prev, string &curr){
    //prev chota hai and curr bada hai
    if(1+prev.size() != curr.size())    return false;

    int i = 0, j = 0;

    while(i<curr.size()){
        if(prev[j] == curr[i] && j < prev.size()){
            i++; j++;
        }
        else i++;
    }
    if(i == curr.size() && j == prev.size())    return true;
    else    return false;
}

bool cmp(string s1, string s2){
    return s1.size() < s2.size();
}

//Time Complexity: O(n logn)+ O(n2 * l), l-> longest lenght of the string
//Space Complexity: O(n)
int longestStringChain(vector<string> &words){
    int n = words.size();
    sort(words.begin(), words.end(), cmp);
    vector<int> dp(n,1);
    int maxi = 1;
    
    for(int i=1; i<n; i++){
        for(int j=0; j<i; j++){
            if(compare(words[j], words[i])){
                dp[i] = max(dp[i], 1+dp[j]);
            }
        }
        maxi = max(maxi, dp[i]);
    }
    return maxi;
}

int main(){
    int n;
    cin>>n;
    vector<string> words(n);

    for(auto &i:words)  cin>>i;
    cout<<longestStringChain(words);
    return 0;
}