cmake_minimum_required(VERSION 3.7)
project(KuqiKV)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -g)


set(Network_SRC
        src/auxiliary/nocopy.h
        src/network/channel.cc
        src/network/channel.h
        src/network/eventloop.cc
        src/network/eventloop.h
        src/network/poller.cc
        src/network/poller.h
        src/network/server.cc
        src/network/server.h
        src/network/socket.cc
        src/network/socket.h
        src/network/charbf.cc
        src/network/charbf.h
        src/network/ioctl.cc
        src/network/ioctl.h
        src/network/client.cc
        src/network/client.h
        src/network/charbf.cc
        src/network/charbf.h)

set(RPC_Server_SRC
        ${Network_SRC}
        src/rpc/rpc_server.h
        src/rpc/rpc_server.cc
        src/kvtest/db.h
        src/kvtest/db.cc
        test/rpc_obj.h src/rpc/marshal.h src/rpc/future.h src/kvtest/kv_protocol.h)

set(RPC_Client_SRC
        ${Network_SRC}
        src/kvtest/db.h
        src/kvtest/db.cc
        src/rpc/rpc_client.cc src/rpc/rpc_client.h test/rpc_obj.h src/rpc/marshal.h src/rpc/future.h src/kvtest/kv_protocol.h)

add_executable(Network_Test ${Network_SRC} test/network.cc src/auxiliary/scope_lock.h)
add_executable(RPC_Server_Test ${RPC_Server_SRC} test/rpc_server_test.cc)
add_executable(RPC_Client_Test ${RPC_Client_SRC} test/rpc_client_test.cc)

add_executable(RPC_KV_Server_Test ${RPC_Server_SRC} test/rpc_kv_server_test.cc)
add_executable(RPC_KV_Client_Test ${RPC_Client_SRC} test/rpc_kv_client_test.cc)

target_link_libraries(RPC_Client_Test pthread)
target_link_libraries(RPC_Server_Test pthread)
target_link_libraries(RPC_KV_Client_Test pthread)
target_link_libraries(RPC_KV_Server_Test pthread)