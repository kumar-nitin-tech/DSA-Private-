#include<bits/stdc++.h>
using namespace std;

//This the function to check whether the char inserted in the board doesn't violated the three rule
//1. 1. All the rows should be filled with numbers(1 – 9) exactly once.
// 2. All the columns should be filled with numbers(1 – 9) exactly once.
//3. Each 3×3 submatrix should be filled with numbers(1 – 9) exactly once.

bool isValid(vector<vector<char>>&board, int row, int col, int c){
    //in this we use elemination rule 
    //we check the row that is the character placed in row if present we would return false as it violate the rule
    for(int i=0;i<9;i++){
        if(board[row][i] == c){
            return false;
        }
        //for column
        if(board[i][col] == c)
            return false;

        //for 3*3 sub grid we 
        if(board[3*(row/3)+(i/3)][3*(col/3)+(i%3)] == c){
            return false;
        }
    }
    return true;

}

//This Sudoku we can do it with backtracking easily 
//Time Complexity: O(9^(n*n))
//Space Compelxity : O(1)

bool solveSudoku(vector<vector<char>>&board){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == '.'){
                for(char c='1';c<='9';c++){
                    if(isValid(board,i,j,c)){
                        board[i][j] = c;

                        if(solveSudoku(board)){
                            return true;
                        }
                        else
                            board[i][j] = '.';
                    }
                }
                return false;
            }

        }
    }
    return true;

}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<char>>board(n,vector<char>(m));
    for(auto &i:board){
        for(auto &j:i){
            cin>>j;
        }
    }
    solveSudoku(board);
    for(auto i:board){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }

    return 0;
}