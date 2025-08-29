//
// Created by Christoph Barth on 23.08.25.
//

#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>


enum class DType{Float32, Float64, Int32, Int64, UNDEFINED};

inline size_t itemsize(DType dtype){
    switch (dtype) {
        case DType::Float32: return 4;
        case DType::Float64: return 8;
        case DType::Int32: return 4;
        case DType::Int64: return 8;
        case DType::UNDEFINED: return 0;
    }
}

// Allgemeines Template (unvollständig, dient nur als Platzhalter)
template<typename T>
struct CTypeToDType;

// Spezialisierungen für konkrete Typen
template<> struct CTypeToDType<float>   { static constexpr DType value = DType::Float32; };
template<> struct CTypeToDType<double>  { static constexpr DType value = DType::Float64; };
template<> struct CTypeToDType<int32_t> { static constexpr DType value = DType::Int32;   };
template<> struct CTypeToDType<int64_t> { static constexpr DType value = DType::Int64;   };


inline std::string to_string(DType dt) {
    switch (dt) {
        case DType::Float32: return "Float32";
        case DType::Float64: return "Float64";
        case DType::Int32:   return "Int32";
        case DType::Int64:   return "Int64";
        case DType::UNDEFINED:   return "undefined";
    }
    return "Unknown";
}
