#pragma once

#include <stdexcept>

template<class T>
class DynamicArray {
private:
    T* data;
    size_t length;

public:
    DynamicArray() : data(nullptr), length(0) {}

    DynamicArray(T* items, int count) : length(count) {
        data = new T[length];
        for (int i = 0; i < count; ++i) {
            data[i] = items[i];
        }
    }

    DynamicArray(int size) : length(size) {
        data = new T[length];
    }

    DynamicArray(const DynamicArray<T>& dynamicArray)
        : length(dynamicArray.length) {
        data = new T[length];
        for (size_t i = 0; i < length; ++i) {
            data[i] = dynamicArray.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    T Get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    int GetSize() const {
        return length;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::length_error("Negative size");
        }

        T* newData = (newSize > 0) ? new T[newSize] : nullptr;
        int elementsToCopy = (newSize > length) ? length : newSize;

        for (int i = 0; i < elementsToCopy; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        length = newSize;
    }

    T& operator[](int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};
