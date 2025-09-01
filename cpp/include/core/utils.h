#include <initializer_list>
#include <vector>
#include <initializer_list>
#include <type_traits>
#include <stdexcept>
#include <utility>
#include <numeric>

#pragma once

// --- scalar_type<T>: peel nested vectors / init_lists to the scalar ---
template<class T>
struct scalar_type { using type = T; };

template<class U>
struct scalar_type<std::vector<U>> { using type = typename scalar_type<U>::type; };

template<class U>
struct scalar_type<std::initializer_list<U>> { using type = typename scalar_type<U>::type; };

template<class T>
using scalar_t = typename scalar_type<std::decay_t<T>>::type;

// --- is_nestable<T>: true if T is a vector or initializer_list ---
template<class T> struct is_nestable : std::false_type {};
template<class U> struct is_nestable<std::vector<U>> : std::true_type {};
template<class U> struct is_nestable<std::initializer_list<U>> : std::true_type {};
template<class T>
inline constexpr bool is_nestable_v = is_nestable<std::decay_t<T>>::value;

// --- flatten_rec: recurse through containers, collect shape and flat data ---
template<class Nested, class Scalar>
void flatten_rec(const Nested& x, std::vector<Scalar>& out,
                 std::vector<size_t>& shape, size_t depth = 0) {
    if constexpr (is_nestable_v<Nested>) {
        const size_t len = x.size();
        if (shape.size() <= depth) {
            // first time we see this depth → record its length
            shape.push_back(len);
        } else {
            // validate regular (non-ragged) shape
            if (shape[depth] != len) {
                throw std::runtime_error("Ragged array: differing lengths at depth " + std::to_string(depth));
            }
        }
        for (const auto& e : x) {
            flatten_rec<decltype(e), Scalar>(e, out, shape, depth + 1);
        }
    } else {
        // base case: scalar
        if constexpr (std::is_convertible_v<Nested, Scalar>) {
            out.push_back(static_cast<Scalar>(x));
        } else {
            static_assert(std::is_convertible_v<Nested, Scalar>,
                          "Element type is not convertible to the scalar type.");
        }
    }
}

// --- user-facing API: works with init_lists or vectors (any nesting depth) ---
template<class Nested>
auto flatten_and_shape(const Nested& x) {
    using Scalar = scalar_t<Nested>;
    std::vector<Scalar> flat;
    std::vector<size_t> shape;
    flatten_rec<Nested, Scalar>(x, flat, shape, 0);
    return std::pair<std::vector<Scalar>, std::vector<size_t>>{std::move(flat), std::move(shape)};
}


inline size_t numel(const std::vector<size_t>& shape) {
    if (shape.empty()) return 1; // 0-D tensor (scalar)
    return std::accumulate(
            shape.begin(), shape.end(),
            size_t{1},
            [](size_t a, size_t b){ return a * b; }
    );
}