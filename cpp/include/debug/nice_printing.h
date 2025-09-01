#pragma once
#include<iostream>
#include <vector>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


template<typename T>
std::string vec_to_str(const std::vector<T>& vec) {
    std::ostringstream oss;
    for (std::size_t i = 0; i < vec.size(); ++i) {
        if (i) oss << ' ';     // Trennzeichen
        oss << vec[i];         // nutzt operator<< für T
    }
    return oss.str();
}

template<typename T>
void print_vector(const std::vector<T>& vec, const std::string& name = "") {
    if (!name.empty()) std::cout << name << " = ";
    std::cout << "{ " << vec_to_str(vec) << " }\n";
}
