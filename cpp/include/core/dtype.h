//
// Created by Christoph Barth on 23.08.25.
//

#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>

/*
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

template<DType dt>
struct DTypeToCType;
template<> struct DTypeToCType<DType::Float32> { using type = float; };


inline std::string to_string(DType dt) {
    switch (dt) {
        case DType::Float32: return "Float32";
        case DType::Float64: return "Float64";
        case DType::Int32:   return "Int32";
        case DType::Int64:   return "Int64";
        case DType::UNDEFINED:   return "undefined";
    }
    return "Unknown";
}*/

//-------- switched Code to Preprocessor Magic --------------

// 1) Central registry
#define FOR_EACH_DTYPE(X)      \
  X(float,   Float32)          \
  X(double,  Float64)          \
  X(int32_t, Int32)            \
  X(int64_t, Int64)

// 2) Enum
enum class DType {
#define MAKE_ENUM(_, Name) Name,
    FOR_EACH_DTYPE(MAKE_ENUM)
#undef MAKE_ENUM
    UNDEFINED
};

// 3) CType -> DType
template<typename T> struct CTypeToDType;
#define MAKE_C2D(Cpp, Name) \
  template<> struct CTypeToDType<Cpp> { static constexpr DType value = DType::Name; };
FOR_EACH_DTYPE(MAKE_C2D)
#undef MAKE_C2D

// 4) DType -> CType
template<DType dt> struct DTypeToCType;
#define MAKE_D2C(Cpp, Name) \
  template<> struct DTypeToCType<DType::Name> { using type = Cpp; };
FOR_EACH_DTYPE(MAKE_D2C)
#undef MAKE_D2C

// 5) to_string()
inline std::string to_string(DType dt) {
    switch (dt) {
#define MAKE_TO_STRING(_, Name) case DType::Name: return #Name;
        FOR_EACH_DTYPE(MAKE_TO_STRING)
#undef MAKE_TO_STRING
        case DType::UNDEFINED: return "UNDEFINED";
    }
    return "Unknown";
}

// 6) itemsize
inline size_t itemsize(DType dtype){
    switch (dtype) {
#define MAKE_ITEMSIZE(Cpp, Name) case DType::Name: return sizeof(Cpp);
        FOR_EACH_DTYPE(MAKE_ITEMSIZE)
#undef MAKE_ITEMSIZE
        case DType::UNDEFINED: return 0;
    }
    return 0;
}