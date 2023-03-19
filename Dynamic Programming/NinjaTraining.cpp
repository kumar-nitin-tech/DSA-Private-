/*
A Ninja has an ‘N’ Day training schedule. He has to perform one of these three activities (Running, Fighting Practice, or Learning New Moves) each day.
There are merit points associated with performing an activity each day. The same activity can’t be performed on two consecutive days. We need to find 
the maximum merit points the ninja can attain in N Days.

We are given a 2D Array POINTS of size ‘N*3’ which tells us the merit point of specific activity on that particular day. Our task is to calculate the 
maximum number of merit points that the ninja can earn.

*/
#include<bits/stdc++.h>
using namespace std;

//Recursive approach
int ninjaTrainingRecursive(vector<vector<int>> &points, int days, int last){
    if(days == 0){
        int maxi = 0;
        for(int i=0;i<3;i++){
            if(i !=last){
                maxi = max(maxi, points[0][i]);
            }
        }
        return maxi;
    }
    int maxi = 0;
    for(int i=0;i<3;i++){
        if(i!=last){
            int activity = points[days][i] + ninjaTrainingRecursive(points,days-1,i);
            maxi = max(maxi, activity);
        }
    }
    return maxi;
}

//memomization
int ninjaTrainingMemomization(vector<vector<int>> &points, int days, int last, vector<vector<int>> &dp){

    if(days == 0){
        int maxi = 0;
        for(int i=0;i<3;i++){
            if(i !=last){
                maxi = max(maxi, points[0][i]);
            }
        }
        return maxi;
    }
    if(dp[days][last] != -1){
        return dp[days][last];
    }
    int maxi = 0;
    for(int i=0;i<3;i++){
        if(i!=last){
            int activity = points[days][i] + ninjaTrainingMemomization(points,days-1,i,dp);
            maxi = max(maxi, activity);
        }
    }
    return dp[days][last] = maxi;
}

//Tabulation
int ninjaTrainingTabulation(vector<vector<int>> &points, int days, vector<vector<int>> &dp){
    for(int last = 0; last<4; last++){
        int maxi = 0;
        for(int i=0;i<3;i++){
            if(i != last)
            maxi = max(maxi,points[0][i]);
        }
        dp[0][last] = maxi;
    }

    for(int n = 1; n<days;n++){
        for(int last = 0; last<4;last++){
            for(int i=0;i<3;i++){
                if(i != last){
                    dp[n][last] = max(dp[n][last],points[n][i] + dp[n-1][i]); 
                }
            } 
        }
    }
    return dp[days-1][3];
}

//Space optimization
int ninjaTrainingTabulationS(vector<vector<int>> &points, int days){
    vector<int> prev(4,-1);
    for(int last = 0; last<4; last++){
        int maxi = 0;
        for(int i=0;i<3;i++){
            if(i != last)
            maxi = max(maxi,points[0][i]);
        }
        prev[last] = maxi;
    }

    for(int n = 1; n<days;n++){
        vector<int> temp(4,0);
        for(int last = 0; last<4;last++){
            temp[last] = 0;
            for(int i=0;i<3;i++){
                if(i != last){
                    temp[last] = max(temp[last] , points[n][i]+prev[i]);
                }
            }   
        }
        prev = temp;
    }
    return prev[3];
}


int main(){
    int days;
    cin>>days;
    vector<vector<int>> points(days,vector<int>(3));
    for(auto &i:points){
        for(auto &j:i){
            cin>>j;
        }
    }
    vector<vector<int>> dp(days,vector<int>(4,-1));

    cout<<ninjaTrainingTabulationS(points,days);
    return 0;
}