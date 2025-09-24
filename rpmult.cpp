// rpmult.cpp  UNFINISHED
// Glenn G. Chappell
// 2025-09-24
//
// For CS 411 Fall 2025
// Russian Peasant Multiplication

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <algorithm>
using std::swap;
#include <string>
using std::string;
using std::getline;
#include <sstream>
using std::istringstream;
#include <cstdlib>
using std::exit;


// rpMult
// Compute and return the product of a, b.
// Uses "Russian Peasant Multiplication". Should be able to handle any
// product that operator* can compute.
// Pre: None.
// Note that postcondtions should hold even when a*b produces numeric
// overflow.
int rpMult(int a,
           int b)
{
    // TODO: WRITE THIS!!!
    return 42;  // DUMMY
}


// getNum
// Prints prompt to cout and then inputs a number of type int on a line
// from cin. Repeats until valid number obtained; returns it to caller
// in reference argument. Return is false if number could not be
// obtained.
bool getNum(const string & prompt,
            int & num)
{
    while (true)
    {
        cout << prompt;
        string line;
        getline(cin, line);
        if (!cin)
        {
            if (cin.eof())
                return false;
            continue;
        }

        istringstream istr(line);
        istr >> num;
        if (!istr)
            continue;
        return true;
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
// Use function rpMult to compute the product of user-provided numbers.
int main()
{
    // Get two numbers to multiply
    int a, b;  // Numbers to multiply
    cout << "\n";
    cout << "I need two numbers to multiply together" << endl;
    cout << "\n";
    if (!getNum("Enter the first number: ", a))
    {
        cout << "Could not do input" << "\n";
        exit(1);
    }
    cout << "\n";
    if (!getNum("Enter the second number: ", b))
    {
        cout << "Could not do input" << "\n";
        exit(1);
    }
    cout << "\n";

    // Print divider between user input, results
    cout << "----------------------------------------" << "\n";
    cout << "\n";

    // Compute & print results
    cout << "Numbers to multiply: " << a << ", " << b << "\n";
    int rpmprod = rpMult(a, b);
    int prod = a * b;
    cout << "Russian Peasant Multiplication result: " << rpmprod
         << "\n";
    cout << "C++ operator* result: " << prod << "\n";
    cout << "\n";

    // Check the result
    if (rpmprod == prod)
    {
        cout << "The results are equal." << "\n";
        cout << "Awesomely nifty!" << "\n";
    }
    else
    {
        cout << "The results differ." << "\n";
        cout << "Crud, phooey, and more crud!" << "\n";
    }
    cout << "\n";

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

