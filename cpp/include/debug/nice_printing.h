#pragma once

#include<iostream>
#include <vector>

template<typename T>
void print_vector(const std::vector<T>& vec, const std::string& name = "") {
    if (!name.empty()) std::cout << name << " = ";
    std::cout << "{ ";
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << "}\n";
}