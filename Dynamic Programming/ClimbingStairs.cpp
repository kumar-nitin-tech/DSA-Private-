#include<bits/stdc++.h>
using namespace std;

int climbStair(int n){
    if(n == 0){
        return 0;
    }
    int prev = 1;
    int prev1 = 1;

    for(int i=2;i<=n;i++){
        int ans = prev + prev1;
        prev = prev1;
        prev1 = ans;
    }
    return prev1;
}

int main(){
    int n;
    cin>>n;
    cout<<climbStair(n);
    return 0;
}