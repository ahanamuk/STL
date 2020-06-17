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

    // Validate that copy_backward_result aliases in_out_result
    STATIC_ASSERT(same_as<copy_backward_result<int, double>, ranges::in_out_result<int, double>>);

    // Validate dangling story needed?

    int const input[] = {13, 42, 1729};
    { // Validate range overload
        int output[] = {-2, -2, -2};
        auto result  = copy_backward(move_only_range{input}, move_only_range{output}.end());
        STATIC_ASSERT(same_as<decltype(result),
            copy_backward_result<iterator_t<move_only_range<int const>>, iterator_t<move_only_range<int>>>>);
        assert(result.in == move_only_range{input}.begin());
        assert(result.out == move_only_range{output}.begin());
        assert(ranges::equal(output, input));
    }
    { // Validate iterator + sentinel overload
        int output[] = {-2, -2, -2};
        move_only_range wrapped_input{input};
        auto result = copy_backward(wrapped_input.begin(), wrapped_input.end(), move_only_range{output}.end());
        STATIC_ASSERT(same_as<decltype(result),
            copy_backward_result<iterator_t<move_only_range<int const>>, iterator_t<move_only_range<int>>>>);
        assert(result.in == wrapped_input.begin());
        assert(result.out == move_only_range{output}.begin());
        assert(ranges::equal(output, input));
    }
}

int main() {
    STATIC_ASSERT((smoke_test(), true));
    smoke_test();
}

struct instantiator {
    template <class In, class Out>
    static void call(In&& in = {}, Out out = {}) {
        (void) ranges::copy(in, std::move(out));
        (void) ranges::copy(ranges::begin(in), ranges::end(in), std::move(out));
    }
};

template void test_in_out<instantiator>();
