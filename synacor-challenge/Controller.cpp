#include "Controller.h"

#include <iostream>
#include <fstream>

namespace
{
    const char* filename = "../save.txt";
}

namespace SynacorChallenge
{
    Controller::Controller()
    {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line))
        {
            commands.push_back(line + "\n");
        }
    }

    auto Controller::save() -> void
    {
        std::ofstream file(filename, std::ofstream::trunc);
        for (const auto &command : commands)
        {
            file << command;
        }
    }

    auto Controller::processCommand(const std::string& command) -> bool
    {
        if (command == "save\n")
        {
            save();
            std::cout << "Game Saved. Input: " << std::endl;
            return true;
        }

        return false;
    }

    auto Controller::getNextCommand() -> std::string
    {
        if (index < commands.size())
        {
            return commands[index++];
        }

        std::string nextCommand;
        std::getline(std::cin, nextCommand);
        nextCommand += "\n";

        while (processCommand(nextCommand))
        {
            nextCommand = getNextCommand();
        }

        commands.push_back(nextCommand);
        index++;
        return nextCommand;
    }

    auto Controller::input() -> char
    {
        if (in.empty())
        {
            in = getNextCommand();
        }

        char c = in[0];
        in.erase(0, 1);
        return c;
    }

    auto Controller::output(char c) -> void
    {
        std::cout << c;
    }
}