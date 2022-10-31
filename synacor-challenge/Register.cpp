#include "Register.h"

namespace SynacorChallenge
{
    auto Register::read() const -> uint16_t
    {
        return data;
    }

    auto Register::set(uint16_t newData) -> void
    {
        data = newData;
    }
}