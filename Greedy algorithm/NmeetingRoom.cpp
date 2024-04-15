/*
    N meetings in one room   
    Problem Statement:  There is one meeting room in a firm. You are given two arrays, start and end each of size N.For an index ‘i’, start[i] denotes the starting time of the 
                        ith meeting while end[i]  will denote the ending time of the ith meeting. Find the maximum number of meetings that can be accommodated if only one meeting can happen in the room at a  particular time. Print the order in which these meetings will be performed.

    Problem Link:   https://www.naukri.com/code360/problems/1062712?topList=striver-sde-sheet-problems
                    https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

    Refer:  https://takeuforward.org/data-structure/n-meetings-in-one-room/

*/

#include<bits/stdc++.h>
using namespace std;

struct meet{
    int start;
    int end;
    int pos;
};

static bool cmp(meet a, meet b){
    return a.end < b.end;
}

vector<int> maxMeeting(vector<int> &start, vector<int> &end){
    int n = start.size();
    vector<meet> meeting(n);
    for(int i=0; i<n; i++){
        meeting[i].start = start[i];
        meeting[i].end = end[i];
        meeting[i].pos = i+1;
    }

    sort(meeting.begin(), meeting.end(), cmp);
    vector<int> ans;
    int limit = meeting[0].end;
    ans.push_back(meeting[0].pos);
    for(int i=1; i<n; i++){
        if(meeting[i].start > limit){
            ans.push_back(meeting[i].pos);
            limit = meeting[i].end;
        }
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    vector<int> start(n), end(n);
    for(auto &i:start)  cin>>i;
    for(auto &i:end)  cin>>i;
    vector<int> ans = maxMeeting(start, end);
    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}