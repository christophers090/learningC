N-Queens
The n-queens puzzle is the problem of placing n queens on an n x n chessboard so that no two queens can attack each other.

A queen in a chessboard can attack horizontally, vertically, and diagonally.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a unique board layout where the queen pieces are placed. 'Q' indicates a queen and '.' indicates an empty space.

You may return the answer in any order.

Example 1:



Input: n = 4

Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There are two different solutions to the 4-queens puzzle.

Example 2:

Input: n = 1

Output: [["Q"]]
Constraints:

1 <= n <= 8


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<bool> cols(n, false), leftDiag(2*n-1, false), rightDiag(2*n-1, false);
        vector<int> queens(n, -1);  // queens[row] = col position
        vector<vector<string>> solution;

        dfs(0, n, cols, leftDiag, rightDiag, queens, solution);

        return solution;
    }

    void dfs(int row, int n, vector<bool> &cols, vector<bool> &leftDiag, vector<bool> &rightDiag, vector<int> &queens, vector<vector<string>>& solution){
        if(row == n){
            addSolution(queens, solution, n);
            return;
        }

        for(int col = 0; col < n; col++){
            int left = row + col;
            int right = row - col + n - 1;
            
            if(!cols[col] && !leftDiag[left] && !rightDiag[right]){
                // Place queen
                queens[row] = col;
                cols[col] = true;
                leftDiag[left] = true;
                rightDiag[right] = true;
                
                dfs(row + 1, n, cols, leftDiag, rightDiag, queens, solution);
                
                // Backtrack
                cols[col] = false;
                leftDiag[left] = false;
                rightDiag[right] = false;
            }
        }
    }

    void addSolution(vector<int> &queens, vector<vector<string>>& solution, int n){
        vector<string> board(n, string(n, '.'));
        
        for(int row = 0; row < n; row++){
            board[row][queens[row]] = 'Q';
        }

        solution.push_back(board);
    }
};