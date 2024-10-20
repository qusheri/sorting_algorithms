cmake_minimum_required(VERSION 3.16)
project(lab2_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Укажите путь к Qt, если он не находится в стандартных путях
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")

# Найдите необходимые компоненты Qt
find_package(Qt6 COMPONENTS Core Gui Widgets Charts REQUIRED)

# Добавьте пути к заголовочным файлам, если необходимо
include_directories(DataStructures)

# Определите ваши исходные и заголовочные файлы
set(DATA_STRUCTURES
        DataStructures/ArraySequence.h
        DataStructures/ArraySequence.tpp
        DataStructures/DynamicArray.h
        DataStructures/DynamicArray.tpp
        DataStructures/ImmutableArraySequence.h
        DataStructures/ImmutableArraySequence.tpp
        DataStructures/ImmutableSequence.h
        DataStructures/LinkedList.h
        DataStructures/LinkedList.tpp
        DataStructures/ListSequence.h
        DataStructures/ListSequence.tpp
        DataStructures/Sequence.h
)

add_executable(lab2_3
        main.cpp
        ISorter.h
        HeapSorter.h
        MergeSorter.h
        interface.h
        interface.cpp
        test.h
        test.cpp
        display_charts.cpp
        display_charts.h
        ${DATA_STRUCTURES}
)

target_link_libraries(lab2_3 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts)
