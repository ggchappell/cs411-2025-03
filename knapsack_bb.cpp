// knapsack_bb.cpp
// Glenn G. Chappell
// 2025-12-03
//
// For CS 411 Fall 2025
// Knapsack Problem with Branch-and-Bound

#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
using std::getline;
#include <cstdlib>
using std::size_t;
#include <utility>
using std::pair;
using std::make_pair;
#include <vector>
using std::vector;
#include <algorithm>
using std::max;
using std::sort;
#include <cassert>
// for assert


// knapsack_bf_recurse
// Given lists of object weights & values, knapsack capacity, and n,
// returns greatest possible value in knapsack problem using only
// objects from first n.
// Brute-force method.
// Recursive helper for function knapsack_bf.
int knapsack_bf_recurse(const vector<int> & weights,
                        const vector<int> & values,
                        int capacity,
                        size_t n)
{
    assert(weights.size() == values.size());
    assert(n <= weights.size());

    // BASE CASE

    if (n == 0)  // BASE CASE
        return 0;

    // RECURSIVE CASE

    int result;  // For our final result

    int max_without_last =
        knapsack_bf_recurse(weights, values,
                            capacity, n-1);
    if (weights[n-1] > capacity)
        result = max_without_last;
    else
    {
        int max_with_last = values[n-1] +
            knapsack_bf_recurse(weights, values,
                                capacity-weights[n-1], n-1);
        result = max(max_with_last, max_without_last);
    }

    return result;
}


// knapsack_bf
// Given lists of object weights & values, and knapsack capacity,
// returns greatest possible value in knapsack problem.
// Brute-force method.
// Calls recursive helper function knapsack_bf_recurse.
int knapsack_bf(const vector<int> & weights,
                const vector<int> & values,
                int capacity)
{
    assert(weights.size() == values.size());
    size_t n = weights.size();

    return knapsack_bf_recurse(weights, values,
                               capacity, n);
}


using ipair = pair<int, int>;  // Type of value-weight pair
                               //   .first: value
                               //   .second: weight


// knapsack_bb_recurse
// Given lists of object weights & values, knapsack capacity, and n,
// returns greatest possible value in knapsack problem using only
// objects from first n, UNLESS best value found + value_in_sack is
// <= best_so_far. In latter case returns 0. Updates best_so_far to
// best value found.
// Uses branch-and-bound.
// Recursive helper for function knapsack_bb.
int knapsack_bb_recurse(const vector<ipair> & vw,
                        int capacity,
                        size_t n,
                        int value_in_sack,
                        int & best_so_far)
{
    assert(n <= vw.size());

    // BASE CASE

    if (n == 0)  // BASE CASE
        return 0;

    // RECURSIVE CASE

    int result;  // For our final result

    // Compute bound & backtrack if needed
    int bound = value_in_sack +
                (capacity * vw[n-1].first / vw[n-1].second);
        // Our "actual" upper bound is the above as a fractional
        //  value.  But since we are bounding an integer, the floor
        //  of our fractional bound is also a correct upper bound.
    if (bound <= best_so_far)
        return 0;

    // If no backtrack, then continue as usual

    int max_without_last = knapsack_bb_recurse(vw,
                                              capacity, n-1,
                                              value_in_sack,
                                              best_so_far);

    if (vw[n-1].second > capacity)
        result = max_without_last;
    else
    {
        int max_with_last = vw[n-1].first +
            knapsack_bb_recurse(vw,
                                capacity-vw[n-1].second, n-1,
                                value_in_sack + vw[n-1].first,
                                best_so_far);
        result = max(max_with_last, max_without_last);
    }

    best_so_far = max(best_so_far, value_in_sack + result);
    return result;
}


// knapsack_bb
// Given lists of object weights & values, and knapsack capacity,
// returns greatest possible value in knapsack problem.
// Uses branch-and-bound.
// Calls recursive helper function knapsack_bb_recurse.
int knapsack_bb(const vector<int> & weights,
                const vector<int> & values,
                int capacity)
{
    assert(weights.size() == values.size());
    size_t n = weights.size();

    // Make vector of weight-value pairs
    vector<ipair> vw;
    for (size_t i = 0; i < n; ++i)
        vw.push_back(ipair(values[i], weights[i]));

    // Sort objects by value/weight, increasing
    sort(vw.begin(), vw.end(),
         [](const ipair & a, const ipair & b)
         {
             return a.first*b.second < b.first*a.second;
                 // This is a.first/a.second < b.first/b.second, except
                 //  that it does not have the rounding problems of
                 //  integer division.
         });

    int best_so_far = 0;
    return knapsack_bb_recurse(vw,
                               capacity, n,
                               0,
                               best_so_far);
}


// try_knapsack
// Calls functions on given number of objects; prints results.
void try_knapsack(size_t n,
                  bool dobf)  // True if we do brute-force method
{
    // Sizes & values to push
    vector<int> weightpattern { 1, 10, 1, 10, 10, 1, 10, 1 };
    vector<int> valuepattern { 1, 10, 4, 6, 4, 6, 1, 10 };
    assert(weightpattern.size() == valuepattern.size());

    // Make dataset
    vector<int> weights;
    vector<int> values;
    for (size_t i = 0; i < n; ++i)
    {
        weights.push_back(weightpattern[i%weightpattern.size()]);
        values.push_back(valuepattern[i%weightpattern.size()]);
    }
    int cap = int(4*n);

    // Call knapsack function(s)
    cout << "Number of objects: " << n << "\n";
    cout << "Result (branch-and-bound version): " << "\n";
    cout << "    " << knapsack_bb(weights, values, cap) << "\n";
    if (dobf)
    {
        cout << "Result (brute-force version): \n";
        cout << "    " << knapsack_bf(weights, values, cap) << "\n";
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
    cout << "Knapsack Problem, Branch-and-Bound Method\n\n";
    string prompt =
        "Also use brute-force method (for comparison)? [y/n] ";
    bool do_brute_force = getYN(prompt);
    cout << "\n";

    // Loop through problem sizes
    for (size_t i = 0; i < 1000000; ++i)
        try_knapsack(i, do_brute_force);

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

