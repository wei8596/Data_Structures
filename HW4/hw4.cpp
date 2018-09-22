/**
*  Author: 范真瑋
*  Date: Oct. 25, 2016
*  Purpose: Test if a knight can travel around a chess board (recursive)
*/

#include <iostream>
#include <vector>
using namespace std;

typedef struct xy {
    int x, y;  //  record position
}xy;

//  check if x, y are valid indexes for n*n chessboard
bool check(const xy& next, int** board, const int& n) {
    int x = next.x;
    int y = next.y;

    if ((x>=0 && x<n) && (y>=0 && y<n) && (board[x][y] == 0))
        return true;
    else
        return false;
}

//  solves the Knight Tour problem using Backtracking
bool solve(int** board, const int& n, xy K[], xy current, int count) {
    xy next;

    if (count == n*n) {
        return true;
    }

    for (int i = 0; i < 8; ++i) {
        next.x = current.x + K[i].x;  //  try all possible moves
        next.y = current.y + K[i].y;

        if (check (next, board, n)) {  //  next.x, next.y are valid indexes
            board[next.x][next.y] = count + 1;  //  store the step
            if (solve (board, n, K, next, count+1)) {  //  recursive
                return true;
            }
            else {
                board[next.x][next.y] = 0;  //  backtracking
            }
        }
    }
    return false;  //  no solution
}

//  print the solution
void printSolution(int** board, const int& n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < n; ++i) {  //  delete the chessboard
        delete board[i];
    }
    delete[] board;
}

//  Testing
void knightTravel(const int& n) {
    int** board = new int*[n];  //  create the chessboard
    for (int i = 0; i < n; ++i)
        board[i] = new int[n];

    //  initialize
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = 0;
        }
    }

    //  eight possible moves of the knight
    xy dirK[8] = { {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1} };
    xy beginPosition = {0, 0};  //  set the begin position
    board[0][0] = 1;  //  the first step

    if (solve (board, n, dirK, beginPosition, 1)) {
        printSolution(board, n);
    }
    else {
        cout << "no solution\n";
    }
}

//  driver program for testing
int main() {
    for (int n = 1; n <= 6; ++n) {  // test n = 1~6
        cout << "n = " << n << endl;
        knightTravel(n);
        if (n != 6) {
            cout << endl;
        }
    }

    return 0;
}
