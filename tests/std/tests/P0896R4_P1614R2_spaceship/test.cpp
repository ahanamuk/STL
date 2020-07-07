// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Covers:
// * spaceship for containers

#include <array>
#include <cassert>
#include <compare>
#include <concepts>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

void ordering_test_cases() {
    {
        // Array
        // std::array<int> input1(3, 100);
        // std::array<int> input2(2, 200);
        // assert(input1 != input2);
        // assert((input1 <=> input2) != 0);
    } { // deque
        std::deque<int> a1(3, 100);
        std::deque<int> a2(3, 100);
        std::deque<int> b1(2, 200);
        assert((a1 <=> b1) < 0);
        assert((b1 <=> a1) > 0);
        assert((a1 <=> a2) == 0);
    }
    { // list
        std::list<int> a1(3, 100);
        std::list<int> a2(3, 100);
        std::list<int> b1(2, 200);
        assert((a1 <=> b1) < 0);
        assert((b1 <=> a1) > 0);
        assert((a1 <=> a2) == 0);
    }
    { // vector
        std::vector<int> a1(3, 100);
        std::vector<int> a2(3, 100);
        std::vector<int> b1(2, 200);
        assert((a1 <=> b1) < 0);
        assert((b1 <=> a1) > 0);
        assert((a1 <=> a2) == 0);
    }
    { // forward_list
        std::forward_list<int> a1(3, 100);
        std::forward_list<int> a2(3, 100);
        std::forward_list<int> b1(2, 200);
        assert((a1 <=> b1) < 0);
        assert((b1 <=> a1) > 0);
        assert((a1 <=> a2) == 0);
    }
    { // unordered_map
        typedef std::unordered_map<std::string, std::string> stringmap;
        stringmap a = {{"AAPL", "Apple"}, {"MSFT", "Microsoft"}, {"GOOG", "Google"}};
        stringmap b = {{"MSFT", "Microsoft"}, {"GOOG", "Google"}, {"AAPL", "Apple"}};
        stringmap c = {{"MSFT", "Microsoft Corp."}, {"GOOG", "Google Inc."}, {"AAPL", "Apple Inc."}};
        assert(a == b);
        assert(b != c);
    }
    { // unordered_set
        std::unordered_set<std::string> a = {"AAPL", "MSFT", "GOOG"}, b = {"MSFT", "GOOG", "AAPL"},
                                        c = {"MSFT", "GOOG", "AAPL", "ORCL"};
        assert(a == b);
        assert(b != c);
    }
    { // queue
        std::deque<int> deq1(3, 100);
        std::deque<int> deq2(2, 200);
        std::queue<int> input1(deq1);
        std::queue<int> input2(deq2);
        assert(input1 != input2);
        // assert((input1 <=> input2) != 0);
    }
    { // stack
        std::stack<int> input1;
        input1.push(2);
        input1.push(2);
        std::stack<int> input2;
        input2.push(3);
        input2.push(3);
        assert(input1 != input2);
        // assert((input1 <=> input2) != 0);
    }
}

int main() {
    // STATIC_ASSERT((ordering_test_cases(), true));
    ordering_test_cases();
}
