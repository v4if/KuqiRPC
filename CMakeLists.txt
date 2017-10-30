cmake_minimum_required(VERSION 3.7)
project(KuqiKV)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -g)


set(Network_SRC
        src/auxiliary/nocopy.hpp
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
        src/network/charbf.cpp
        src/network/charbf.hpp
        src/network/ioctl.cpp
        src/network/ioctl.hpp
        src/network/client.cpp
        src/network/client.hpp)

set(Memory_Leak_SRC
        src/network/charbf.cpp
        src/network/charbf.hpp)

set(Network_Buffer_SRC
        src/network/charbf.cpp
        src/network/charbf.hpp
        )

set(RPC_Server_SRC
        ${Network_SRC}
        src/rpc/rpc_server.hpp
        src/rpc/rpc_server.cpp
        src/kv/db.hpp
        src/kv/db.cpp
        test/rpc_obj.hpp src/rpc/marshal.h src/auxiliary/thr_poll.h src/auxiliary/thr_poll.cc src/auxiliary/fifo.h src/auxiliary/obj_method_thread.h src/rpc/future.h)

set(RPC_Client_SRC
        ${Network_SRC}
        src/kv/db.hpp
        src/kv/db.cpp
        src/rpc/rpc_client.cpp src/rpc/rpc_client.hpp test/rpc_obj.hpp src/rpc/marshal.h src/auxiliary/thr_poll.h src/auxiliary/thr_poll.cc src/auxiliary/fifo.h src/auxiliary/obj_method_thread.h src/rpc/future.h)

add_executable(Network_Test ${Network_SRC} test/network.cpp src/auxiliary/scope_lock.h)
add_executable(Memory_Leak_Test ${Memory_Leak_SRC} test/memory_leak.cpp)
add_executable(Network_Buffer_Test ${Network_Buffer_SRC} test/network_buffer.cpp)
add_executable(RPC_Server_Test ${RPC_Server_SRC} test/rpc_server_test.cpp)
add_executable(RPC_Client_Test ${RPC_Client_SRC} test/rpc_client_test.cpp)

target_link_libraries(RPC_Client_Test pthread)
target_link_libraries(RPC_Server_Test pthread)