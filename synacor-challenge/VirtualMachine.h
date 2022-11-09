#pragma once

#include "Memory.h"
#include "Stack.h"
#include "Register.h"
#include "Controller.h"
#include <array>

namespace SynacorChallenge
{
    class VirtualMachine
    {
    public:
        auto run(const char* filename) -> void;

    private:
        auto execute(uint16_t data) -> bool;
        auto getNextArgument() -> uint16_t;
        auto getNextRegister() -> uint16_t;

    private:
        std::array<Register, 8> registers;
        Stack stack;
        Memory memory;
        Controller controller;
    };
}