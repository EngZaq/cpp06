#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer& other) { (void)other; }
Serializer& Serializer::operator=(const Serializer& other) { (void)other; return *this; }
Serializer::~Serializer() {}


uintptr_t Serializer::serialize(Data* ptr) {
    // Take the pointer and treat its raw bits as an integer
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
    // Take the integer and treat its raw bits as a pointer
    return reinterpret_cast<Data*>(raw);
}