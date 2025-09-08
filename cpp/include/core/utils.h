#pragma once
#include <vector>
#include <initializer_list>
#include <cstddef>
#include "core/type.h"   // defines: using num = float;
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <cstddef>
#include <string>
#include <numeric>
#include <iostream>

namespace christorch {

// Flatten nested num containers into flat data + shape
    template <typename T> struct is_std_vector            : std::false_type {};
    template <typename T, typename A>
    struct is_std_vector<std::vector<T, A>>              : std::true_type {};

    template <typename T> struct is_std_init_list         : std::false_type {};
    template <typename T>
    struct is_std_init_list<std::initializer_list<T>>    : std::true_type {};

    template <typename T>
    struct is_supported_container
            : std::bool_constant<is_std_vector<std::decay_t<T>>::value ||
                                 is_std_init_list<std::decay_t<T>>::value> {};

    template <typename T, typename = void>
    struct container_value_type { using type = void; };

    template <typename T>
    struct container_value_type<T, std::enable_if_t<is_std_vector<std::decay_t<T>>::value>>
    {
        using type = typename std::decay_t<T>::value_type;
    };

    template <typename T>
    struct container_value_type<T, std::enable_if_t<is_std_init_list<std::decay_t<T>>::value>>
    {
        // std::initializer_list<T>::value_type ist T (meist const T)
        using type = typename std::decay_t<T>::value_type;
    };

    template <typename T>
    using container_value_type_t = typename container_value_type<T>::type;

// Helfer für sauberere static_asserts in unerreichten Zweigen
    template <typename...> struct dependent_false : std::false_type {};

// -------------------- Rekursive Flatten-Implementierung --------------------

    template <typename Nested>
    void flatten_rec(const Nested& x,
                     std::vector<float>& out,
                     std::vector<std::size_t>& shape,
                     std::size_t depth = 0)
    {
        using X = std::decay_t<Nested>;
        static_assert(is_supported_container<X>::value,
                      "flatten_rec: only std::vector<...> and std::initializer_list<...> are supported at each level.");

        using Elem = std::remove_cv_t<std::remove_reference_t<container_value_type_t<X>>>;

        if constexpr (is_supported_container<Elem>::value)
        {
            // Rekursive Ebene: x ist Container von (weiteren) Containern
            const std::size_t this_dim = x.size();
            if (shape.size() <= depth) {
                shape.push_back(this_dim);
            } else if (shape[depth] != this_dim) {
                throw std::runtime_error("Ragged array detected at depth " + std::to_string(depth));
            }

            for (const auto& e : x) {
                flatten_rec(e, out, shape, depth + 1);
            }
        }
        else if constexpr (std::is_arithmetic_v<Elem>)
        {
            // Basis-Ebene: x ist Container von arithmetischen Werten (int/float/double/...)
            const std::size_t this_dim = x.size();
            if (shape.size() <= depth) {
                shape.push_back(this_dim);
            } else if (shape[depth] != this_dim) {
                throw std::runtime_error("Ragged array detected at depth " + std::to_string(depth));
            }

            for (const auto& v : x) {
                out.push_back(static_cast<float>(v));
            }
        }
        else
        {
            static_assert(dependent_false<X>::value,
                          "flatten_rec: unsupported leaf type (expected arithmetic scalar).");
        }
    }


    template <typename Nested,
            std::enable_if_t<is_supported_container<std::decay_t<Nested>>::value, int> = 0>
    std::pair<std::vector<float>, std::vector<std::size_t>>
    flatten_and_shape(const Nested& x)
    {
        std::vector<float> flat;
        std::vector<std::size_t> shape;
        flatten_rec(x, flat, shape, 0);
        return {std::move(flat), std::move(shape)};
    }

// numel: total number of elements for a given shape
    inline size_t numEl(const std::vector<size_t>& shape) {
        if (shape.empty()) return 1; // 0-D tensor (scalar)
        size_t s = std::accumulate(
                shape.begin(), shape.end(),
                size_t{1},
                [](size_t a, size_t b){ return a * b; }
        );
        return s;
    }

} // namespace christorch
