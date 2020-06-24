// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <algorithm>
#include <cassert>
#include <concepts>
#include <range_algorithm_support.hpp>
#include <ranges>
#include <utility>

constexpr void smoke_test() {
    using ranges::copy_backward, ranges::copy_backward_result, ranges::iterator_t;
    using std::same_as;
    using bidi_range = test::range<std::bidirectional_iterator_tag, test : Sized::no, test::CanDifference::no,
        test::Common::no, test::CanCompare::yes, test::ProxyRef::yes>;

    // Validate that copy_backward_result aliases in_out_result
    STATIC_ASSERT(same_as<copy_backward_result<int, double>, ranges::in_out_result<int, double>>);

    // Validate dangling story needed?

    int const input[] = {13, 42, 1729};
    { // Validate range overload
        int output[] = {-2, -2, -2};
        auto result  = copy_backward(bidi_range{input}, bidi_range{output}.end());
        STATIC_ASSERT(same_as<decltype(result),
            copy_backward_result<iterator_t<bidi_range<int const>>, iterator_t<bidi_range<int>>>>);
        assert(result.in == bidi_range{input}.begin());
        assert(result.out == bidi_range{output}.begin());
        assert(ranges::equal(output, input));
    }
    { // Validate iterator + sentinel overload
        int output[] = {-2, -2, -2};
        bidi_range wrapped_input{input};
        auto result = copy_backward(wrapped_input.begin(), wrapped_input.end(), bidi_range{output}.end());
        STATIC_ASSERT(same_as<decltype(result),
            copy_backward_result<iterator_t<bidi_range<int const>>, iterator_t<bidi_range<int>>>>);
        assert(result.in == wrapped_input.begin());
        assert(result.out == bidi_range{output}.begin());
        assert(ranges::equal(output, input));
    }
}

int main() {
    STATIC_ASSERT((smoke_test(), true));
    smoke_test();
}

struct instantiator {
    template <class Bidi1, class Bidi2>
    static void call(Bidi1&& in = {}, Bidi2&& out = {}) {
        (void) ranges::copy_backward(in, ranges::begin(out));
        (void) ranges::copy_backward(ranges::begin(in), ranges::end(in), ranges::begin(out));
    }
};

template void test_bidi_bidi<instantiator>();
