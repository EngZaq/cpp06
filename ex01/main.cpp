#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
    // 1. Initialize our non-empty Data structure
    Data originalData;
    originalData.id = 42;
    originalData.name = "CPP06 Serialization Test";
    originalData.level = 4.2f;

    // 2. Display the original memory address and its contents
    std::cout << "--- ORIGINAL STATE ---" << std::endl;
    std::cout << "Pointer Address : " << &originalData << std::endl;
    std::cout << "Data ID         : " << originalData.id << std::endl;
    std::cout << "Data Name       : " << originalData.name << std::endl;
    std::cout << "Data Level      : " << originalData.level << std::endl;
    std::cout << "----------------------\n" << std::endl;

    // 3. Serialize: Convert the Data* pointer into a raw uintptr_t integer
    uintptr_t rawInteger = Serializer::serialize(&originalData);

    std::cout << "--- SERIALIZATION ---" << std::endl;
    std::cout << "Serialized (Dec) : " << rawInteger << std::endl;
    std::cout << "Serialized (Hex) : 0x" << std::hex << rawInteger << std::dec << std::endl;
    std::cout << "---------------------\n" << std::endl;

    // 4. Deserialize: Convert the raw uintptr_t integer back into a Data* pointer
    Data* deserializedData = Serializer::deserialize(rawInteger);

    std::cout << "--- DESERIALIZED STATE ---" << std::endl;
    std::cout << "Pointer Address : " << deserializedData << std::endl;
    std::cout << "Data ID         : " << deserializedData->id << std::endl;
    std::cout << "Data Name       : " << deserializedData->name << std::endl;
    std::cout << "Data Level      : " << deserializedData->level << std::endl;
    std::cout << "--------------------------\n" << std::endl;

    // 5. The absolute proof for the evaluator
    if (&originalData == deserializedData)
    {
        std::cout << "[SUCCESS] The pointers match exactly. No data was lost." << std::endl;
    }
    else
    {
        std::cout << "[FATAL ERROR] Pointers do not match! Memory corruption occurred." << std::endl;
    }

    return 0;
}