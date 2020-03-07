cmake_minimum_required(VERSION 3.13)
project(annoy)

set(CMAKE_CXX_STANDARD 14)

include_directories(examples)
include_directories(src)

add_executable(annoy
        examples/precision_test.cpp
        examples/cmli_test.cpp
        src/annoygomodule.h
        src/annoygomodule.i
        src/annoylib.h
        src/xannoylib.h
        src/annoyluamodule.cc
        src/annoymodule.cc
        src/kissrandom.h
        src/ConcurrentBitset.cpp
        src/ConcurrentBitset.h
        examples/x_annoy_correctness_test.cpp
        examples/x_annoy_performance_test.cpp
        examples/x_annoy_del_performance_test.cpp
        examples/raw_annoy_index_size_test.cpp
        src/mman.h examples/read_hdf5.cpp examples/raw_annoy_test.cpp examples/new_annoy_test.cpp src/iannoylib.h)

