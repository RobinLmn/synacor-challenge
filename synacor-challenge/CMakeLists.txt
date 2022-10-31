cmake_minimum_required(VERSION 3.17)
project(synacor_challenge)

set(CMAKE_CXX_STANDARD 14)

add_executable(synacor_challenge main.cpp VirtualMachine.cpp Stack.cpp Memory.cpp Register.cpp)