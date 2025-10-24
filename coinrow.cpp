// coinrow.cpp  UNFINISHED
// Glenn G. Chappell
// 2025-10-24
//
// For CS 411 Fall 2025
// Bottom-Up Dynamic-Programming Example

#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
using std::getline;
#include <cstdlib>
using std::size_t;
#include <vector>
using std::vector;


// coinRow_bf
// Returns maximum sum of subset of given values, on the condition that
// no two consecutive values lie in the subset. Assumes values are all
// nonnegative.
// Brute-force method.
int coinRow_bf(const vector<int> & values)
{
    // TODO: WRITE THIS!!!
    return 42;  // DUMMY
}


// coinRow_dp
// Returns maximum sum of subset of given values, on the condition that
// no two consecutive values lie in the subset. Assumes values are all
// nonnegative.
// Uses dynamic programming (bottom-up).
int coinRow_dp(const vector<int> & values)
{
    // TODO: WRITE THIS!!!
    return 42;  // DUMMY
}


// try_coinRow
// Calls functions on a list of the given size; prints results.
void try_coinRow(size_t n,
                 bool dobf)  // True if we do brute-force method
{
    // Values to push
    vector<int> valuepattern { 1, 10, 1, 10, 10, 1, 10, 1 };

    // Make dataset
    vector<int> values;
    for (size_t i = 0; i != n; ++i)
        values.push_back(valuepattern[i%valuepattern.size()]);

    // Call coin-row function(s)
    cout << "Number of values: " << n << "\n";
    cout << "Result (dynamic-programming version): \n";
    cout << "    " << coinRow_dp(values) << "\n";
    if (dobf)
    {
        cout << "Result (brute-force version): \n";
        cout << "    " << coinRow_bf(values) << "\n";
    }
    cout << "\n";
}


// getYN
// Prompt user with given string, repeatedly input until user types a
// string beginning with 'y', 'Y', 'n', or 'N'. Return yes/no to caller
// as bool (true means yes). Exit on EOF.
bool getYN(const string & prompt)
{
    while (true)
    {
        cout << prompt;
        string line;
        getline(cin, line);
        if (!cin)
        {
            cin.clear();
            cin.ignore();
            continue;
        }

        if (line.size() > 0 && (line[0] == 'y' || line[0] == 'Y'))
            return true;
        if (line.size() > 0 && (line[0] == 'n' || line[0] == 'N'))
            return false;

        cout << "\n";
        cout << "Please type \"y\" or \"n\"\n";
    }
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Try functions for increasing input sizes.
int main()
{
    // Ask user whether to do brute-force computation
    cout << "Coin Row Problem, Dynamic Programming Method\n\n";
    string prompt =
        "Also use brute-force method (for comparison)? [y/n] ";
    bool do_brute_force = getYN(prompt);
    cout << "\n";

    // Loop through problem sizes
    for (size_t i = 0; i < 100000000; ++i)
        try_coinRow(i, do_brute_force);

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

