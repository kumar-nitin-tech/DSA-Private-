/*
    Reverse words in a given string

    Given a String S, reverse the string without reversing its individual words. Words are separated by dots.

    Example:
    Input:
        S = i.like.this.program.very.much

    Output: much.very.program.this.like.i

    Explanation: After reversing the whole
                string(not individual words), the input
                string becomes
                much.very.program.this.like.i
*/

#include<bits/stdc++.h>
using namespace std;

string reverseWordInString(string S){
    //stores final output of given string
    string ans = "";
    
    //for storing word of the string
    string temp = "";

    for(int i=S.size()-1;i>=0;i--){
        if(S[i] == '.'){
            reverse(temp.begin(),temp.end());
            ans += temp;
            ans.push_back('.');
            temp = "";
        }
        else{
            temp.push_back(S[i]);
        }
    }
    reverse(temp.begin(),temp.end());
    ans += temp;
    return ans;
}

int main(){
    string S;
    cin>>S;
    string ans = reverseWordInString(S);
    cout<<ans;
    return 0;
}