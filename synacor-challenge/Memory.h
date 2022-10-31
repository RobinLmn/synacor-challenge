#pragma once

#include <cstdint>

namespace SynacorChallenge
{
    class Memory
    {
    public:
        auto load(const char* filename) -> void;
        auto next() -> uint16_t;
        auto jump(uint16_t dest) -> void;
        auto write(uint16_t index, uint16_t data) -> void;
        auto read(uint16_t index) const -> uint16_t;
        auto currentAddress() const -> uint16_t;

        ~Memory();

    private:
        uint16_t* memory = nullptr;
        uint16_t pc = 0;
    };
}
