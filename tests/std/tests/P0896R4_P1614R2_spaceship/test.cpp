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

template <class Container>
void ordered_containers_test(Container smaller, Container smaller_equal, Container larger) {
    assert(smaller < larger);
    assert(smaller <= larger);
    assert(larger > smaller);
    assert(larger >= smaller);
    assert(smaller == smaller_equal);
    assert(smaller != larger);
    assert((smaller <=> larger) < 0);
    assert((larger <=> smaller) > 0);
    assert((smaller_equal <=> smaller) == 0);
}

template <class Container>
void unordered_containers_test(Container smaller, Container smaller_equal, Container larger) {
    assert(smaller == smaller_equal);
    assert(smaller != larger);
    // assert((smaller <=> larger) < 0);
    // assert((larger <=> smaller) > 0);
    // assert((smaller_equal <=> smaller) == 0);
}

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
        ordered_containers_test(a1, a2, b1);
    }
    { // list
        std::list<int> a1(3, 100);
        std::list<int> a2(3, 100);
        std::list<int> b1(2, 200);
        ordered_containers_test(a1, a2, b1);
    }
    { // vector
        std::vector<int> a1(3, 100);
        std::vector<int> a2(3, 100);
        std::vector<int> b1(2, 200);
        ordered_containers_test(a1, a2, b1);
    }
    { // forward_list
        std::forward_list<int> a1(3, 100);
        std::forward_list<int> a2(3, 100);
        std::forward_list<int> b1(2, 200);
        ordered_containers_test(a1, a2, b1);
    }
    { // unordered_map
        using stringmap = std::unordered_map<std::string, std::string>;
        stringmap a     = {{"cat", "tabby"}, {"dog", "poodle"}, {"bear", "grizzly"}};
        stringmap b     = {{"cat", "tabby"}, {"dog", "poodle"}, {"bear", "grizzly"}};
        stringmap c     = {{"cat", "siamese"}, {"dog", "lab"}, {"bear", "polar"}};
        unordered_containers_test(a, b, c);
    }
    { // unordered_set
        std::unordered_set<std::string> a = {"cat", "dog", "bear"};
        std::unordered_set<std::string> b = {"bear", "cat", "dog"};
        std::unordered_set<std::string> c = {"mouse", "cat", "bear", "dog"};
        unordered_containers_test(a, b, c);
    }
    { // queue
        std::deque<int> deq1(3, 100);
        std::deque<int> deq2(2, 200);
        std::queue<int> a(deq1);
        std::queue<int> b(deq1);
        std::queue<int> c(deq2);
        unordered_containers_test(a, b, c);
        // assert((input1 <=> input2) != 0);
    }
    { // stack
        std::stack<int> a;
        a.push(2);
        a.push(2);
        std::stack<int> b;
        b.push(2);
        b.push(2);
        std::stack<int> c;
        c.push(3);
        c.push(3);
        unordered_containers_test(a, b, c);
        // assert((input1 <=> input2) != 0);
    }
}

int main() {
    // STATIC_ASSERT((ordering_test_cases(), true));
    ordering_test_cases();
}
