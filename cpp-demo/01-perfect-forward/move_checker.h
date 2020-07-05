//
// Created by eason on 2020/7/5.
//

#ifndef CPP_DEMO_MOVE_CHECKER_H
#define CPP_DEMO_MOVE_CHECKER_H

#include <vector>
#include <memory>


class move_checker {
    // shared counters of copies and moves.
    std::shared_ptr<int> _copies;
    std::shared_ptr<int> _moves;

public:
    // expensive payload
    std::vector<int> payload;

    typedef std::vector<int>::const_iterator const_iterator;

    // construct a new checker, with counters reset to 0,
    // and a non-empty payload.
    move_checker() : _copies(new int(0)),
                     _moves(new int(0)),
                     payload({1, 2, 3, 4, 5, 6, 7}) {}

    // copy constructor. counts copy operations.
    move_checker(const move_checker &other) : _copies(other._copies),
                                              _moves(other._moves),
                                              payload(other.payload) {
        *_copies += 1;
    }

    // copy assignment is similar to copy constructor.

    // move constructor. counts move operations.
    move_checker(move_checker &&other) : _copies(other._copies),
                                         _moves(other._moves),
                                         payload(std::move(other.payload)) {
        *_moves += 1;
    }
    // move assignment is similar to move constructor

    const_iterator begin() const {return payload.begin();}

    const_iterator end() const {return payload.end();}

    int copies() const {return *_copies;}
    int moves() const {return *_moves;}
};


#endif //CPP_DEMO_MOVE_CHECKER_H
