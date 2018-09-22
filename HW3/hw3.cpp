/**
*  Author: 范真瑋
*  Date: Oct. 25, 2016
*  Purpose: Test if a knight can travel around a chess board (stack)
*/

#include <iostream>
#include <vector>
using namespace std;

typedef struct xy {
    int x, y;  //  record position
    int dir;  // record direction
}xy;

//  A finite ordered list with zero or more elemtents
class Stack {
    public:
        //  Create an empty stack
        Stack() {
            s.clear();
        }

        //  If no element in the stack return true else return false
        bool IsEmpty() const {
            return s.empty();
        }

        //  Return top element of stack
        xy& Top() {
            if (IsEmpty()) {
                throw "Stack is empty!\n";
            }

            return s.back();
        }

        //  Insert item into the top of the stack
        void Push (const xy& x) {
            s.push_back(x);
        }

        //  Delete the top element of the stack
        void Pop() {
            if (IsEmpty()) {
                throw "Stack is empty. Cannot delete.\n";
            }
            s.pop_back();
        }

        vector<xy> s;  // vector for stack
};

//  check if x, y are valid indexes for n*n chessboard
bool check(const xy& next, int** board, const int& n) {
    int x = next.x;
    int y = next.y;

    if ((x>=0 && x<n) && (y>=0 && y<n) && (board[x][y] == 0)) {
        return true;
    }
    else {
        return false;
    }
}

//  solves the Knight Tour problem using Backtracking
bool solve(int** board, const int& n, xy K[], xy current, int count) {
    xy next;
    Stack record;
    int d = 0;

    while (!record.IsEmpty() || count == 1) {
        while (d < 8) {
            next.x = current.x + K[d].x;  //  try all possible moves
            next.y = current.y + K[d].y;

            if (count == n*n)  //  complete
                return true;
            else if (check (next, board, n)) {  //  next.x, next.y are valid indexes
                board[next.x][next.y] = ++count;  //  store the step
                ++current.x;  //[0][0] -> [1][1]
                ++current.y;
                current.dir = d + 1;  //  d = 0 -> K1, d = 1 -> K2
                record.s.push_back(current);  //  record x, y and direction in the stack
                current = next;  //  next step
                d = 0;
                continue;
            }
            else {
                ++d;  //  try another move
            }
        }
        if (d == 8 && record.IsEmpty()) {  //  no solution (the stack is empty)
            return false;
        }
        board[current.x][current.y] = 0;  //  backtracking
        current.x = record.Top().x - 1;  //  go back
        current.y = record.Top().y - 1;
        d = record.Top().dir;  //  try another move
        record.Pop();
        --count;
    }
}

//  print the solution
void printSolution(int** board, const int& n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
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

        for (int i = 0; i < n; ++i) {  //  delete the chessboard
            delete board[i];
        }
        delete[] board;
    }
    else {
        cout << "no solution\n";

        for (int i = 0; i < n; ++i) {  //  delete the chessboard
            delete board[i];
        }
        delete[] board;
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
