// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <algorithm>
#include <cassert>
#include <concepts>
#include <range_algorithm_support.hpp>
#include <ranges>
#include <utility>

constexpr void smoke_test() {
    using ranges::reverse, ranges::iterator_t;

    {
        int input[]           = {13, 42, 1367};
        int expected_output[] = { 1367, 42, 13 } auto result = reverse(std::begin(input), std::end(input));
        for (int i = 0; i < 3; ++i) {
            assert(expected_output[i] == input[i]);
        }
        assert(result == std::end(input));
        assert(ranges::equal(input, expected_output));
    }
    {
        int input[]           = {13, 42, 1367};
        int expected_output[] = { 1367, 42, 13 } auto result = reverse(input);
        for (int i = 0; i < 3; ++i) {
            assert(expected_output[i] == input[i]);
        }
        assert(result == std::end(input));
        assert(ranges::equal(input, expected_output));
    }
}

int main() {
    STATIC_ASSERT((smoke_test(), true));
    smoke_test();
}

struct instantiator {
    template <class Out>
    static void call(Out out = {}) {
        (void) ranges::reverse(out);
        (void) ranges::move(ranges::begin(out), ranges::end(out));
    }
};

template void test_out<instantiator>();
