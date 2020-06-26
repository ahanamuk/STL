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
    using bidi_range_input = test::range<std::bidirectional_iterator_tag, int, test::Sized::no, test::CanDifference::no,
        test::Common::no, test::CanCompare::yes, test::ProxyRef::yes>;

    { // Validate iterator + sentinel overload
        int input[]           = {13, 42, 1367};
        int expected_output[] = {1367, 42, 13};
        bidi_range_input wrapped_input{input};
        auto result = reverse(wrapped_input.begin(), wrapped_input.end());
        for (int i = 0; i < 3; ++i) {
            assert(expected_output[i] == input[i]);
        }
        assert(result == wrapped_input.end());
        assert(ranges::equal(input, expected_output));
    }
    // {  // Validate range overload
    //     int input[]           = {13, 42, 1367};
    //     int expected_output[] = {1367, 42, 13};
    //     auto result           = reverse(input);
    //     for (int i = 0; i < 3; ++i) {
    //         assert(expected_output[i] == input[i]);
    //     }
    //     assert(result == std::end(input));
    //     assert(ranges::equal(input, expected_output));
    // }
}

int main() {
    // STATIC_ASSERT((smoke_test(), true));
    smoke_test();
}

struct instantiator {
    template <class Bidi>
    static void call(Bidi bidi = {}) {
        (void) ranges::reverse(bidi);
        (void) ranges::move(ranges::begin(bidi), ranges::end(bidi));
    }
};

template void test_bidi<instantiator>();
