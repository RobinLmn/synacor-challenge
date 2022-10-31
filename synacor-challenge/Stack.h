#pragma once

#include <vector>

namespace SynacorChallenge
{
    class Stack
    {
    public:
        auto push(uint16_t data) -> void;
        auto pop() -> uint16_t;
        auto isEmpty() -> bool;

    private:
        std::vector<uint16_t> stack;
    };
}

