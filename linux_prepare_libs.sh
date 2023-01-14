#! /usr/bin/bash
git clone https://github.com/nlohmann/json.git
mv json JSON
git clone https://github.com/zeromq/libzmq.git
mkdir ZeroMQ
cd libzmq
cmake -S . -B build -D ZMQ_BUILD_TESTS=OFF -D ENABLE_CPACK=OFF -D CMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PWD/../ZeroMQ
cmake --build ./build
cmake --install ./build
cd ..
git clone https://github.com/zeromq/cppzmq.git
cp cppzmq/zmq.hpp ./ZeroMQ/include
cp cppzmq/zmq_addon.hpp ./ZeroMQ/include


