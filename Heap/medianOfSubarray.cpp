#include<bits/stdc++.h>
using namespace std;

class medianFinder{
    vector<int>numArray;
    public:
    void insert(int num){
        numArray.push_back(num);
    }
    double findMedian(){
        sort(numArray.begin(),numArray.end());
        int n = numArray.size();
        if(numArray.size()%2==0){
            int mid1 = numArray.size()/2;
            int mid2 = (numArray.size()/2)-1;
            return ((double)numArray[mid1]+numArray[mid2])/2; 
        }
        else{
            int mid = numArray.size()/2;
            return numArray[mid];
        }
    }
};

class MedianFinder{
    priority_queue<int,vector<int>,greater<int>>minHeap;
    priority_queue<int>maxHeap;
    public:
    void insert(int num){
        if(maxHeap.empty() || num<maxHeap.top()){
            maxHeap.push(num);
        }
        else{
            minHeap.push(num);
        }
        if(minHeap.size() > maxHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        else if(maxHeap.size() > minHeap.size()+1){//Checking that no extra element are there in maxHeap container
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
    }

    double findMedian(){
        if(maxHeap.size() == minHeap.size()){
            return ((double)maxHeap.top()+minHeap.top())/2; 
        }
        else{
            return maxHeap.top();
        }
    }
};

int main(){
    MedianFinder m;
    m.insert(12);
    cout<<m.findMedian()<<" ";
    m.insert(10);
    cout<<m.findMedian()<<" ";
    m.insert(13);
    cout<<m.findMedian()<<" ";
    m.insert(11);
    cout<<m.findMedian()<<" ";
    m.insert(5);
    cout<<m.findMedian()<<" ";
    m.insert(15);
    cout<<m.findMedian()<<" ";
    return 0;
}