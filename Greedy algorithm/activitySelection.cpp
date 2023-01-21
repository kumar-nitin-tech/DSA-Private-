
#include<bits/stdc++.h>
using namespace std;

//a compartiver to sort the array according to end timing
static bool cmp(pair<int,int> a, pair<int,int> b){
    return a.second < b.second;
}

//FUNCTION which tells us the no. of meeting can held
int Nmeeting(vector<int> &start, vector<int> &end, int n){
    
    vector<pair<int,int>> meeting;
    for(int i=0;i<n;i++){
        meeting.push_back({start[i],end[i]});
    } 
    sort(meeting.begin(), meeting.end(), cmp);
    int count = 1;
    int ansEnd = meeting[0].second;
    for(int i=1;i<n;i++){
        if(meeting[i].first > ansEnd){
            count++;
            ansEnd = meeting[i].second;
        }
    }
    return count;
}

int main(){
    int n;
    cin>>n;
    vector<int> start(n);
    vector<int> end(n);
    for(auto &i:start){
        cin>>i;
    }
    for(auto &i:end){
        cin>>i;
    }
    cout<<Nmeeting(start,end,n);
    return 0;
}