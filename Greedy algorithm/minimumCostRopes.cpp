#include<bits/stdc++.h>
using namespace std;

long long minCost(vector<long long> &arr, long long n){
    //minHeap
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for(int i=0;i<arr.size();i++){
        pq.push(arr[i]);
    }
    long long cost = 0;
    while(pq.size() > 1){
        long long first = pq.top();
        pq.pop();
        long long second = pq.top();
        pq.pop();

        long long merge = first + second;
        cost += merge;
        pq.push(merge);
    }
    return cost;
}

int main(){
    long long n;
    cin>>n;
    vector<long long> arr(n);
    for(auto &i:arr){
        cin>>i;
    }
    cout<<minCost(arr,n);
    return 0;
}