cmake_minimum_required(VERSION 3.16)
project(sorting_algorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
add_executable(sorting_algorithms 
        src/ArraySequence.h
        src/BubbleSort.h
        src/DynamicArray.h
        src/functionalTests.h
        src/ISorter.h
        src/LinkedList.h
        src/ListSequence.h
        src/main.cpp
        src/MergeSort.h
        src/QuickSort.h
        src/Sequence.h
        src/ShakerSort.h
)
target_link_libraries(sorting_algorithms Qt6::Widgets Qt6::Charts)