#include "Memory.h"

#include <iostream>
#include <fstream>

namespace SynacorChallenge
{
    auto Memory::load(const char* filename) -> void
    {
        std::ifstream file(filename, std::ifstream::binary);
        memory = new uint16_t[32768];
        char buffer[2];

        for (int i = 0; file; ++i)
        {
            file.read(buffer, 2);
            unsigned char high = buffer[1];
            unsigned char low = buffer[0];

            memory[i] = (high << 8) | low;
        }
    }

    auto Memory::next() -> uint16_t
    {
        return memory[pc++];
    }

    auto Memory::skip() -> void
    {
        pc++;
    }

    auto Memory::jump(uint16_t dest) -> void
    {
        pc = dest;
    }

    auto Memory::read(uint16_t index) const -> uint16_t
    {
        return memory[index];
    }

    auto Memory::write(uint16_t index, uint16_t data) -> void
    {
        memory[index] = data;
    }

    auto Memory::currentAddress() const -> uint16_t
    {
        return pc;
    }

    Memory::~Memory()
    {
        delete[] memory;
    }
}