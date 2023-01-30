#include<bits/stdc++.h>
using namespace std;

long long findMinDiff(vector<long long> &a, long long n, long long m){
    sort(a.begin(), a.end());
    int i = 0, j = m-1;
    int minAns = INT_MAX;

    while(j<a.size()){
        int temp = a[j] - a[i];
        minAns = min(minAns,temp);
        i++;j++;
    }
    return minAns;
}

int main(){
    long long n,m;s
    cin>>n>>m;
    vector<long long> a(n);
    for(auto &i:a){
        cin>>i;
    }
    cout<<findMinDiff(a,n,m);
    return 0;
}