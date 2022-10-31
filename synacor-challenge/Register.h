#pragma once

#include <cstdint>

namespace SynacorChallenge
{
    class Register
    {
    public:
        auto set(uint16_t newData) -> void;
        auto read() const -> uint16_t;

    private:
        uint16_t data = 0;
    };
}

