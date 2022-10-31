#include "Stack.h"

namespace SynacorChallenge
{
    auto Stack::push(uint16_t data) -> void
    {
        stack.emplace_back(data);
    }

    auto Stack::pop() -> uint16_t
    {
        uint16_t data = stack.back();
        stack.pop_back();
        return data;
    }

    auto Stack::isEmpty() -> bool
    {
        return stack.empty();
    }
}