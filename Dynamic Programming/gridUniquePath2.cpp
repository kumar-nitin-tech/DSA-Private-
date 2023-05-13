/*
     You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The testcases are generated so that the answer will be less than or equal to 2 * 109.
*/

#include<bits/stdc++.h>
using namespace std;

int uniquePath(int n, int m, vector<vector<int>> &maze){
    vector<int> prev(m,0);
    for(int i=0;i<n;i++){
        vector<int> temp(m,0);
        for(int j=0;j<m;j++){
            if(maze[i][j] == -1){
                temp[j] = 0;
            }
            else if(i==0 && j==0){
                temp[j] = 1;
            }
            else{
                int up =0, left = 0;
                if(i>0) up = prev[j];
                if(j>0) left = temp[j-1];
                temp[j] = up+left;
            }
        }
        prev = temp;
    }
    return prev[m-1];
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> maze(n, vector<int>(m));
    for(auto &i:maze){
        for(auto &j:i){
            cin>>j;
        }
    }
    cout<<uniquePath(n,m, maze);
    return 0;
}