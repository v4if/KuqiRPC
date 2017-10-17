cmake_minimum_required(VERSION 3.7)
project(KuqiKV)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -g)

set(Network_SRC
        src/debug/debug_new.hpp
        src/debug/debug_new.cpp
        src/debug/memcheck.hpp
        src/include/nocopy.hpp
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
        src/network/ioctl.cpp
        src/network/ioctl.hpp
        src/network/client.cpp
        src/network/client.hpp)

set(Memory_Leak_SRC
        src/debug/debug_new.hpp
        src/debug/debug_new.cpp
        src/debug/memcheck.hpp
        src/network/buffer.cpp
        src/network/buffer.hpp)

set(Network_Buffer_SRC
        src/debug/debug_new.hpp
        src/debug/debug_new.cpp
        src/network/buffer.cpp
        src/network/buffer.hpp
        )

set(RPC_Server_SRC
        ${Network_SRC}
        src/rpc/rpc.hpp
        src/rpc/rpc_server.hpp
        src/rpc/rpc_server.cpp
        src/kv/db.hpp
        src/kv/db.cpp
        test/rpc_obj.hpp)

set(RPC_Client_SRC
        ${Network_SRC}
        src/kv/db.hpp
        src/kv/db.cpp
        src/rpc/rpc_client.cpp src/rpc/rpc_client.hpp test/rpc_obj.hpp)

add_executable(Pointer_Plus_Test test/pointer_plus.cpp)
add_executable(Network_Test ${Network_SRC} test/network.cpp src/include/lockguard.hpp)
add_executable(Memory_Leak_Test ${Memory_Leak_SRC} test/memory_leak.cpp)
add_executable(Network_Buffer_Test ${Network_Buffer_SRC} test/network_buffer.cpp)
add_executable(RPC_Server_Test ${RPC_Server_SRC} test/rpc_server_test.cpp)
add_executable(RPC_Client_Test ${RPC_Client_SRC} test/rpc_client_test.cpp)

target_link_libraries( RPC_Client_Test pthread )