#include "VirtualMachine.h"
#include <iostream>

namespace SynacorChallenge
{
    auto VirtualMachine::run(const char *filename) -> void
    {
        memory.load(filename);
        while (execute(memory.next())) {}
    }

    auto VirtualMachine::execute(uint16_t data) -> bool
    {
        switch (data)
        {
            case 0:
            {
                return false;
            }
            case 1:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                registers[a].set(b);
                return true;
            }
            case 2:
            {
                uint16_t a = getNextArgument();
                stack.push(a);
                return true;
            }
            case 3:
            {
                uint16_t a = getNextRegister();

                if (stack.isEmpty()) throw std::invalid_argument("Empty stack!");

                registers[a].set(stack.pop());
                return true;
            }
            case 4:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                uint16_t c = getNextArgument();

                uint16_t val = b == c ? 1 : 0;
                registers[a].set(val);
                return true;
            }
            case 5:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                uint16_t c = getNextArgument();

                uint16_t val = b > c ? 1 : 0;
                registers[a].set(val);
                return true;
            }
            case 6:
            {
                uint16_t a = getNextArgument();
                memory.jump(a);
                return true;
            }
            case 7:
            {
                uint16_t a = getNextArgument();
                uint16_t b = getNextArgument();

                if (a != 0) memory.jump(b);
                return true;
            }
            case 8:
            {
                uint16_t a = getNextArgument();
                uint16_t b = getNextArgument();

                if (a == 0) memory.jump(b);
                return true;
            }
            case 9:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                uint16_t c = getNextArgument();

                registers[a].set((b+c)%32768);
                return true;
            }
            case 10:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                uint16_t c = getNextArgument();

                registers[a].set((b*c)%32768);
                return true;
            }
            case 11:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                uint16_t c = getNextArgument();

                registers[a].set((b%c));
                return true;
            }
            case 12:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                uint16_t c = getNextArgument();

                registers[a].set((b&c));
                return true;
            }
            case 13:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();
                uint16_t c = getNextArgument();

                registers[a].set((b|c));
                return true;
            }
            case 14:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();

                uint16_t val = ~b & ~(1 << 15);
                registers[a].set(val);
                return true;
            }
            case 15:
            {
                uint16_t a = getNextRegister();
                uint16_t b = getNextArgument();

                uint16_t val = memory.read(b);
                registers[a].set(val);
                return true;
            }
            case 16:
            {
                uint16_t a = getNextArgument();
                uint16_t b = getNextArgument();

                memory.write(a, b);
                return true;
            }
            case 17:
            {
                stack.push(memory.currentAddress() + 1);
                uint16_t a = getNextArgument();
                memory.jump(a);
                return true;
            }
            case 18:
            {
                if (stack.isEmpty()) return false;

                uint16_t a = stack.pop();
                memory.jump(a);
                return true;
            }
            case 19:
            {
                uint16_t a = getNextArgument();
                std::cout << static_cast<char>(a);
                return true;
            }
            case 20:
            {
                if (in.empty())
                {
                    std::getline(std::cin, in);
                    in += "\n";
                }

                char c = in[0];
                in.erase(0, 1);

                uint16_t a = getNextRegister();
                registers[a].set(c);
                return true;
            }
            case 21:
            {
                return true;
            }
            default:
            {
                throw std::invalid_argument("Unsupported Operation");
            }
        }
    }

    auto VirtualMachine::getNextRegister() -> uint16_t
    {
        uint16_t data = memory.next();

        if (8 <= data && data < 32768 || data >= 32768 + 8)
        {
            throw std::invalid_argument("Wrong register index");
        }

        return data <= 8 ? data : data % 32768;
    }

    auto VirtualMachine::getNextArgument() -> uint16_t
    {
        uint16_t data = memory.next();

        if (data <= 32767)
        {
            return data;
        }

        if (data >= 32776)
        {
            throw std::invalid_argument("Argument >= 32776");
        }

        return registers[data % 32768].read();
    }
}