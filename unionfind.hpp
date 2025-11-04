// unionfind.hpp
// Glenn G. Chappell
// 2025-11-03
//
// For CS 411 Fall 2025
// Header for class UnionFind
// Union-Find Structure
// There is no associated source file

#ifndef FILE_UNIONFIND_HPP_INCLUDED
#define FILE_UNIONFIND_HPP_INCLUDED

#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <cassert>
// for assert


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
    // Pre:
    //     x >= 0.
    //     makeSet must not have been previously called on x.
    void makeSet(size_t x)
    {
        if (x >= _data.size())
        {
            _data.resize(x+1, Info(false, 0));
        }

        assert(!_data[x]._inited);
        _data[x] = Info(true, x);
    }

    // find
    // Find operation.
    // Pre:
    //     x >= 0.
    //     makeSet must have been previously called on x.
    size_t find(size_t x)
    {
        assert(x < _data.size());
        assert(_data[x]._inited);

        if (_data[x]._parent != x)
        {
            return find(_data[x]._parent);
        }
        return x;
    }

    // unionx
    // Union operation ("union" is a reserved word in C++).
    // Pre:
    //    x >= 0.
    //    y >= 0.
    //    makeSet must have been previously called on each of x, y.
    void unionx(size_t x,
                size_t y)
    {
        assert(x < _data.size());
        assert(_data[x]._inited);
        assert(y < _data.size());
        assert(_data[y]._inited);

        size_t xroot = find(x);
        assert(_data[xroot]._parent == xroot);
        size_t yroot = find(y);
        assert(_data[yroot]._parent == yroot);
        if (xroot == yroot)
        {
            return;
        }

        _data[xroot]._parent = yroot;
    }

// ***** UnionFind: internal-use types *****
private:

    // struct Info
    // Info on single item in union-find structure
    struct Info {
        bool _inited;     // Has Make-Set been called on this item?
                          //  _parent field invalid if !_inited
        size_t  _parent;  // Parent of item

        // Ctor from field values, for convenience
        Info(bool theInited,
             size_t theParent)
           :_inited(theInited),
            _parent(theParent)
        {}
    };

// ***** UnionFind: data members *****
private:

    vector<Info> _data;  // Info for each item

};  // End class UnionFind


#endif //#ifndef FILE_UNIONFIND_HPP_INCLUDED

