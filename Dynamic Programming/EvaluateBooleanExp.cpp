/*
    Evaluate Boolean Expression to True

    Problem Statement:  Given an expression, A, with operands and operators (OR, AND, XOR), in how many ways can you evaluate the 
                        expression to be true, by grouping it in different ways?
                        Operands are only true and false.
                        Return the number of ways to evaluate the expression modulo 103 + 3.  

    Problem Link:   https://leetcode.com/problems/parsing-a-boolean-expression/
                    https://www.codingninjas.com/studio/problems/boolean-evaluation_1214650

    Refer:  https://takeuforward.org/data-structure/evaluate-boolean-expression-to-true-partition-dp-dp-52/
            https://www.youtube.com/watch?v=MM7fXopgyjw&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY

*/

#include<bits/stdc++.h>
using namespace std;

//Recursive 
//Time Complexity:
//Space Complexity:
int evaluateExpR(int i, int j, int isTrue, string &exp){
    if(i>j) return 0;
    if(i == j){
        //check if we want ways for true or false
        if(isTrue)  return exp[i] == 'T';
        else    return exp[i] == 'F';
    }

    long long ways = 0;
    //partition
    //we increase k by +2 as operand are at +2 interval of string and we have to part when we find a operand
    for(int k=i+1; k<j; k+=2){
        long long leftT = evaluateExpR(i,k-1,1,exp);
        long long leftF = evaluateExpR(i,k-1,0,exp);
        long long rightT = evaluateExpR(k+1,j,1,exp);
        long long rightF = evaluateExpR(k+1,j,0,exp);

        //check if expression is &, |, ^ 
        if(exp[k] == '&'){
            //This means left & right so what are the cases of having a true 
            //AND table->
            //T T -> T
            //T F -> F
            //F T -> F
            //F F -> F
            //So if we have to find the no. of ways for getting True 
            if(isTrue){
                //no. of ways if we are finding true is leftT * rightT
                ways += leftT * rightT;
            }
            else{
                //if we are finding no. of ways for false
                ways += (leftF * rightT) + (leftT * rightF) + (leftF * rightF);
            }
        }
        else if(exp[k] == '|'){
            //This means left & right so what are the cases of having a true 
            //OR table->
            //T T -> T
            //T F -> T
            //F T -> T
            //F F -> F
            //So if we have to find the no. of ways for getting True 
            if(isTrue){
                //no. of ways if we are finding true is leftT * rightT
                ways += (leftT * rightT) + (leftF * rightT) + (leftT * rightF);
            }
            else{
                //if we are finding no. of ways for false
                ways += (leftF * rightF);
            }
        }
        else{
            //This means left & right so what are the cases of having a true 
            //XOR table->
            //T T -> F
            //T F -> T
            //F T -> T
            //F F -> F
            //So if we have to find the no. of ways for getting True 
            if(isTrue){
                //no. of ways if we are finding true is leftT * rightT
                ways +=  (leftF * rightT) + (leftT * rightF);
            }
            else{
                //if we are finding no. of ways for false
                ways += (leftT * rightT) + (leftF * rightF);
            }
        }
    }
    return ways;
}

//Memomization
//Time Complexity:
//Space Complexity:
int evaluateExpM(int i, int j, int isTrue, string &exp, vector<vector<vector<int>>> &dp){
    if(i>j) return 0;

    if(i==j){
        if(isTrue)  return exp[i] == 'T';
        else    return exp[i] == 'F';
    }

    if(dp[i][j][isTrue] != -1)  return dp[i][j][isTrue];

    long long ways = 0;
    for(int k=i+1; k<j; k+=2){
        long long leftT = evaluateExpM(i,k-1,1,exp,dp);
        long long leftF = evaluateExpM(i,k-1,0,exp,dp);
        long long rightT = evaluateExpM(k+1,j,1,exp,dp);
        long long rightF = evaluateExpM(k+1,j,0,exp,dp);
        if(exp[k] == '&'){
            if(isTrue)
                ways += leftT * rightT;
            else
                ways += (leftF * rightT) + (leftT * rightF) + (leftF * rightF);
        }
        else if(exp[k] == '|'){
            if(isTrue)
                ways += (leftT * rightT) + (leftF * rightT) + (leftT * rightF);
            else
                ways += (leftF * rightF);
        }
        else{
            if(isTrue)
                ways +=  (leftF * rightT) + (leftT * rightF);
            else
                ways += (leftT * rightT) + (leftF * rightF);
        }
    }
    return dp[i][j][isTrue] = ways;
}

//Tabulation
//Time Complexity:
//Space Complexity:
int evaluateExpT(string &exp){
    int n = exp.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>> (n, vector<int> (2,0)));

    //nested loop
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<n; j++){
            if(i>j) continue;
            for(int isTrue=0; isTrue<=1; isTrue++){
                if(i==j){
                    if(isTrue)  dp[i][j][isTrue] =  exp[i] == 'T';
                    else    dp[i][j][isTrue] = exp[i] == 'F';
                    continue;
                }
                long long ways = 0;
                for(int k=i+1; k<j; k+=2){
                    long long leftT = dp[i][k-1][1];
                    long long leftF = dp[i][k-1][0];
                    long long rightT = dp[k+1][j][1];
                    long long rightF = dp[k+1][j][0];
                    if(exp[k] == '&'){
                        if(isTrue)
                            ways += leftT * rightT;
                        else
                            ways += (leftF * rightT) + (leftT * rightF) + (leftF * rightF);
                    }
                    else if(exp[k] == '|'){
                        if(isTrue)
                            ways += (leftT * rightT) + (leftF * rightT) + (leftT * rightF);
                        else
                            ways += (leftF * rightF);
                    }
                    else{
                        if(isTrue)
                            ways +=  (leftF * rightT) + (leftT * rightF);
                        else
                            ways += (leftT * rightT) + (leftF * rightF);
                    }
                }
                dp[i][j][isTrue] = ways;
            }
        }
    }
    return dp[0][n-1][1];
}

int main(){
    string exp;
    cin>>exp;
    int n = exp.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2,-1)));
    cout<<evaluateExpT(exp);

    return 0;
}