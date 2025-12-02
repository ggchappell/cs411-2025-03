// nqueen_backtrack.cpp
// Glenn G. Chappell
// 2025-12-01
//
// For CS 411 Fall 2025
// n-Queens Problem
// Backtracking Example
// Based on nqueen_exhaustive.cpp

#include <iostream>
using std::cout;
using std::cin;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::getline;
#include <sstream>
using std::istringstream;
#include <cstddef>
using std::size_t;
#include <cassert>
// For assert


using BoardType = vector<int>;  // Holds queen locs on a chessboard

// We represent a partial queen placement on a chessboard as a BoardType
// object (board) and an int (n). The int (n) gives the size of the
// chessboard. Thus, n = 8 means an 8 x 8 chessboard. Object board is a
// listing of the queen positions (columns) on 0 or more rows of the
// chessboard (at most n rows). There is at most one queen per row. Its
// position (column) is given by a number from 0 to n-1, inclusive.
//
// For example, a Board holding 1, 3, with n = 4 means a 4 x 4
// chessboard with queens in its first 2 rows. The queen in the row 0
// (1st row) lies in column 1 (the 2nd square), and the queen in row 1
// (2nd row) lies in column 3 (the 4th & last square). This is pictured
// below:
//
// +---+---+---+---+
// |   | Q |   |   |
// +---+---+---+---+
// |   |   |   | Q |
// +---+---+---+---+
// |   |   |   |   |
// +---+---+---+---+
// |   |   |   |   |
// +---+---+---+---+

// We print a queen arrangement by printing the position of the queen in
// each column. For example, "1 3 0 2" represents the following
// arrangement of queens on a 4x4 chessboard:
//
// +---+---+---+---+
// |   | Q |   |   |
// +---+---+---+---+
// |   |   |   | Q |
// +---+---+---+---+
// | Q |   |   |   |
// +---+---+---+---+
// |   |   | Q |   |
// +---+---+---+---+


// printBoard
// Given a full solution to the n-Queens Problem, print it, as described
// above.
// Pre:
//     n > 0
//     board.size() == n
//     Each entry of board is in [0, n-1].
//     board, n represent a full solution to the n-Queens Problem (see
//      above).
void printBoard(const BoardType & board,
                [[maybe_unused]] int n)
{
    assert(int(board.size()) == n);
    bool first = true;  // First time through loop?
    for (auto col : board)
    {
        if (first)
            first = false;
        else
            cout << " ";
        cout << col;
    }
    cout << "\n";
}


// checkQueen
// Given a partial solution to the n-Queens Problem (see above),
// determine whether a proposed new queen placement on the next row is
// acceptable, that is, if it cannot attack any any of the existing
// queens. If there is no possible attack, then the return value is
// true.
// Pre:
//     board represents a placement of non-attacking queens on an n x n
//      chessboard (see above).
//     board.size() < n.
//     0 <= newcol < n.
bool checkQueen(const BoardType & board,
                [[maybe_unused]] int n,
                int newrow,
                int newcol)
{
    // Iterate through existing queens
    for (int oldrow = 0; oldrow < newrow; ++oldrow)
    {
        int oldcol = board[size_t(oldrow)];

        // Existing queen: oldrow, oldcol
        // Proposed new queen: newrow, newcol
        // Determine whether new queen can attack old queen

        // Vertical attack (same column)?
        if (newcol == oldcol)
            return false;

        // Diagonal attack #1?
        if (newrow-oldrow == newcol-oldcol)
            return false;

        // Diagonal attack #2?
        if (newrow-oldrow == oldcol-newcol)
            return false;

        // NOTE. We do not need to check for horizontal attack (same
        //  row) because of the assumption that there is at most one
        //  queen in each row.
    }
    return true;
}


// nQueen_recurse
// Given a partial solution to the n-Queens Problem (see above) IN WHICH
// EXISTING QUEENS CANNOT ATTACK EACH OTHER, print out all non-attacking
// placements of n queens that include the given queens. Return number
// of placements.
// Recursive.
// Pre:
//     n > 0.
//     board.size() <= n.
//     Each entry of board is in [0 .. n-1].
//     board represents a placement of NON-ATTACKING queens on an n x n
//      chessboard (see above).
int nQueen_recurse(BoardType & board,
                   int n)
// NOTE. We can pass board by reference since the function always
//  restores it to the same state it was in when the function was
//  called.
{
    // BASE CASE

    if (board.size() == size_t(n))
    {
        // We have a full solution! Print it.
        printBoard(board, n);
        return 1;
    }

    // RECURSIVE CASE

    // Try each position in next row
    int total = 0;
    for (int newcol = 0; newcol < n; ++newcol)
    {
        // If we can add a queen in position newcol in the next row ...
        if (checkQueen(board, n, int(board.size()), newcol))
        {
            // ... then do it, and recurse.
            board.push_back(newcol);            // Add new queen
            total += nQueen_recurse(board, n);  // Recursive call
            board.pop_back();                   // Remove queen
        }
        // else -- PRUNE THE TREE!
    }
    return total;
}


// nQueen
// Print all solutions to the n-Queens Problem for a chessboard of the
// given size. That is, print a representation of every placement of n
// mututally non-attacking queens on an n x n chessboard. Return number
// of placements.
// Pre:
//     n > 0.
int nQueen(int n)
{
    BoardType board;  // Empty board
    return nQueen_recurse(board, n);
}


// getInt
// Input an integer. On non-fatal error, print message and retry. On
// fatal error, return false. On successful input, set n to integer that
// was read and return true.
bool getInt(const string & prompt,  // Print this before doing input
            int & n)                // Number we input
{
    // Prompt & input integer, with retry on bad input
    while (true)
    {
        bool founderror = false;
        cout << prompt;
        cout.flush();
        string line;
        getline(cin, line);
        if (!cin)
        {
            if (cin.eof())      // End of file
                return false;   // Fatal error
            cin.clear();
            cin.ignore();
            founderror = true;  // Bad input; retry
        }
        else
        {
            istringstream is(line);
            is >> n;
            if (!is)
                founderror = true;  // Bad read from string; retry
        }

        if (!founderror)
            break;
        cout << "\n";
        cout << "Try again; please type an integer\n";
    }

    return true;  // Successful input
}


// Main program
// Repeatedly input an integer n and print all n-Queen solutions.
// Terminates on fatal error in input or n <= 0.
int main()
{
    while (true)
    {
        // Print explanation
        cout << "n-Queen Solver\n\n";

        // Prompt & get chessboard size
        int n;
        bool good = getInt("Chessboard size (0 to quit?) ", n);
        if (!good || n <= 0)
            break;

        // Print solutions to n-Queens Problem
        cout << "\n";
        cout << "n-Queen Solutions for "
             << n << " x " << n << " chessboard:\n";
        cout << "-----------------------\n";
        int count = nQueen(n);
        cout << "-----------------------\n";
        cout << "Number of solutions found: " << count << "\n\n";
    }
}

