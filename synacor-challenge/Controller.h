#pragma once

#include <string>
#include <queue>

namespace SynacorChallenge
{
    class Controller
    {
    public:
        Controller();
        auto input() -> char;
        static auto output(char c) -> void;

    private:
        auto save() -> void;

        auto getNextCommand() -> std::string;
        auto processCommand(const std::string& command) -> bool;

    private:
        std::vector<std::string> commands = {};
        std::string in;
        int index = 0;
    };
}