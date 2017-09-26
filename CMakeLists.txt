cmake_minimum_required(VERSION 3.7)
project(KuqiKV)

set(CMAKE_CXX_STANDARD 11)

set(Network_SRC
        src/network/channel.cpp
        src/network/channel.hpp
        src/network/eventloop.cpp
        src/network/eventloop.hpp
        src/network/poller.cpp
        src/network/poller.hpp
        src/network/server.cpp
        src/network/server.hpp
        src/network/socket.cpp
        src/network/socket.hpp
        src/network/buffer.cpp
        src/network/buffer.hpp
        src/include/nocopy.hpp)

set(Rpc_SRC
        src/rpc/proto.h
        src/rpc/rpc.cpp
        src/rpc/rpc.h)


add_executable(KuqiKV test/All.cpp test/rpc.cpp src/include/debug_new.hpp)
add_executable(Routine_Test test/routine.cpp)

add_executable(Network_Buffer_Test test/network_buffer.cpp src/network/buffer.cpp src/network/buffer.hpp)
add_executable(Network_Test ${Network_SRC} test/network.cpp)
add_executable(Rpc_Test ${Network_SRC} test/rpc.cpp)

add_executable(Memory_Leak_Test src/include/debug_new.hpp test/memory_leak.cpp)