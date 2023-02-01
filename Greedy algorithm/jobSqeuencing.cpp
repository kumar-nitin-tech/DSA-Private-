/*
    Job Sequencing Problem

    Given a set of N jobs where each jobi has a deadline and profit associated with it.
    Each job takes 1 unit of time to complete and only one job can be scheduled at a time. We earn the profit associated with job if and only if the job is 
    completed by its deadline.
    Find the number of jobs done and the maximum profit.
*/
#include<bits/stdc++.h>
using namespace std;

struct Job{
    int id; // Job id
    int dead; // Job deadline
    int profit; //Job done profit
};


static bool cmp(Job a, Job b){
    return a.profit > b.profit;
}

vector<int> jobSequencing(int n, vector<Job> arr){
    sort(arr.begin(), arr.end(), cmp);
    int maxiDead = INT_MIN;
    for(int i=0;i<n;i++){
        maxiDead = max(maxiDead,arr[i].dead);
    }
    vector<int> schedule(maxiDead+1, -1);//1 is added beacause time is taken on 1 base indexing
    int maxProfit = 0;
    int jobCount = 0;
    for(int i=0;i<n;i++){
        for(int k = arr[i].dead ; k>0;k--){
            if(schedule[k] == -1){
                schedule[k] = arr[i].id;
                maxProfit += arr[i].profit;
                jobCount ++;
                break;
            }
        }
    }
    vector<int> ans;
    ans.push_back(jobCount);
    ans.push_back(maxProfit);
    return ans;
}

int main(){
    int n;
    cin>>n;
    vector<Job> arr(n);
    for(auto &i: arr){
        cin>>i.id>>i.dead>>i.profit;
    }
    vector<int> ans = jobSequencing(n,arr);
    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}