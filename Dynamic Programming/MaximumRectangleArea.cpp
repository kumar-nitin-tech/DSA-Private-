/*
    Maximum Rectangle Area with all 1's

    Problem Statement:  Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and 
                        return its area.

    Problem Link:   https://leetcode.com/problems/maximal-rectangle/
                    https://www.codingninjas.com/studio/problems/maximum-size-rectangle-sub-matrix-with-all-1-s_893017?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/maximum-rectangle-area-with-all-1s-dp-on-rectangles-dp-55/
            https://www.youtube.com/watch?v=tOylVCugy9k&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=56

*/

#include<bits/stdc++.h>
using namespace std;

//We use Largest Rectangle in histogram function to solve the area of maximum area of the rectangle
//This using two passes
int maximumAreaHisto(vector<int> &arr){
    //In this we use the concept of next smaller/ greater number which 
    int n = arr.size();
    vector<int> left(n), right(n);
    stack<int> st;

    //For left Smaller array
    for(int i=0; i<n; i++){
        while(!st.empty() && arr[st.top()] > arr[i]){
            st.pop();
        }
        if(st.empty())  left[i] = 0;
        else    left[i] = st.top() + 1;
        st.push(i);
    }
    
    //clearing the stack for reuse
    while(!st.empty())  st.pop();

    //For right smaller array
    for(int i=n-1; i>=0; i--){
        while(!st.empty() && arr[st.top()] > arr[i]){
            st.pop();
        }
        if(st.empty())  right[i] = 0;
        else    right[i] = st.top() - 1;
        st.push(i);
    }

    int maxArea = INT_MIN;
    //finding maximum area
    for(int i=0; i<n; i++){
        int area = arr[i] * (right[i] - left[i] + 1);
        maxArea = max(area,maxArea);
    }
    return maxArea;
}

//In Single Pass
int maxArea(vector<int> &arr){
    int n = arr.size();
    stack<int> st;
    //idea is to simulataneously find the area for the next smaller and prev smaller as we are pushing index in the stack, when we find a element which smaller then current we know that prev element next smaller is this and prev smaller would be already there in the stack
    int maxA = INT_MIN;
    //Why till i<=n because when we reach to n-1 we have to check n-1 height area also so we go to n as its height is 0 so we can find the area of n-1;
    for(int i=0; i<=n; i++){
        //We have to check till n and consider n-1 element so i==n
        while(!st.empty() && (i == n || arr[st.top()] >= arr[i])){
            int h = arr[st.top()];
            st.pop();
            int width;
            if(st.empty())  width = i;
                            //i is next smaller for h and st.top is prev smaller for h
            else    width = i-st.top()-1;
            maxA = max(maxA, h*width);
        }
        st.push(i);
    }
    return maxA;
}

//Come back to original problem of finding max area of the rectangle in the matrix of 1 and 0 
//TC: O(N * (M + M))
//SC: O(N)
int maxAreaOfRectangle(vector<vector<int>> &arr){
    int n = arr.size();
    int m = arr[0].size();

    //Idea to create a height array of every row and with every row we increase the height in array and call the function for every row array for finding maximum area
    int maxA = INT_MIN;
    vector<int> height(m,0);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j] == 1) height[j]++;  
            else	height[j] = 0;
        }
        maxA = max(maxA, maxArea(height));
    }
    return maxA;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> arr(n, vector<int> (m));
    for(auto &i: arr){
        for(auto &j: i){
            cin>>j;
        }
    }

    cout<<maxAreaOfRectangle(arr);
    return 0;
}