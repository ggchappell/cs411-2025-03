// unionfind.hpp  UNFINISHED
// Glenn G. Chappell
// 2025-11-03
//
// For CS 411 Fall 2025
// Header for class UnionFind
// Union-Find Structure
// There is no associated source file.

#ifndef FILE_UNIONFIND_HPP_INCLUDED
#define FILE_UNIONFIND_HPP_INCLUDED

#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;


// class UnionFind
// Union-Find structure.
// "Quick union" (rooted tree) implementation.
// path-compression optimizations.
//
// Items are size_t values.
// Member functions:
// - makeSet (Make-Set operation)
// - find    (Find operation)
// - unionx  (Union operation)
class UnionFind {

// ***** UnionFind: ctors, dctor, op= *****
public:

    // Compiler generated default ctor, copy ctor, copy =, dctor used

// ***** UnionFind: general public functions *****
public:

    // makeSet
    // Make-Set operation.
    void makeSet(size_t x)
    {
        // TODO: WRITE THIS!!!
    }

    // find
    // Find operation.
    size_t find(size_t x)
    {
        // TODO: WRITE THIS!!!
        return 42;  // DUMMY
    }

    // unionx
    // Union operation ("union" is a reserved word in C++).
    void unionx(size_t x,
                size_t y)
    {
        // TODO: WRITE THIS!!!
    }

// ***** UnionFind: internal-use types *****
private:

    // struct Info
    // Info on single item in union-find structure
    struct Info {
        // TODO: WRITE THIS!!!
    };

// ***** UnionFind: data members *****
private:

    vector<Info> _data;  // Info for each item

};  // End class UnionFind


#endif //#ifndef FILE_UNIONFIND_HPP_INCLUDED

