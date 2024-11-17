#pragma once

#include "Sequence.h"
#include "DynamicArray.h"

template<class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* data;
    int length;
    int capacity;

    void ensureCapacity(int minCapacity) {
    if (minCapacity > capacity) {
        int newCapacity = capacity * 2;
        if (newCapacity < minCapacity) {
            newCapacity = minCapacity;
        }
        data->Resize(newCapacity);
        capacity = newCapacity;
    }
}

public:
    ArraySequence() : data(new DynamicArray<T>(10)), length(0), capacity(10) {}

    ArraySequence(const T* items, int count) : data(new DynamicArray<T>(count)), length(count), capacity(count) {
        for (int i = 0; i < count; ++i) {
            data->Set(i, items[i]);
        }
    }

    ArraySequence(const ArraySequence<T>& arraySequence)
            : data(new DynamicArray<T>(arraySequence.capacity)), length(arraySequence.length), capacity(arraySequence.capacity) {
        for (int i = 0; i < length; ++i) {
            data->Set(i, arraySequence.data->Get(i));
        }
    }

    ~ArraySequence() {
        delete data;
    }

    T GetFirst() const {
        if (length == 0) {
            throw std::out_of_range("Array is empty");
        }
        return data->Get(0);
    }

    T GetLast() const {
        if (length == 0) {
            throw std::out_of_range("Array is empty");
        }
        return data->Get(length - 1);
    }

    T Get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data->Get(index);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex) {
            throw std::out_of_range("Index out of range");
        }
        int subLength = endIndex - startIndex + 1;
        T* items = new T[subLength];
        for (int i = 0; i < subLength; ++i) {
            items[i] = data->Get(startIndex + i);
        }
        Sequence<T>* subsequence = new ArraySequence<T>(items, subLength);
        delete[] items;
        return subsequence;
    }

    int GetLength() const {
        return length;
    }

    void Append(const T& item) {
        ensureCapacity(length + 1);
        data->Set(length, item);
        length++;
    }

    void Prepend(const T& item) {
        ensureCapacity(length + 1);
        for (int i = length; i > 0; --i) {
            data->Set(i, data->Get(i - 1));
        }
        data->Set(0, item);
        length++;
    }

    void InsertAt(const T& item, int index) {
        if (index < 0 || index > length) {
            throw std::out_of_range("Index out of range");
        }
        ensureCapacity(length + 1);
        for (int i = length; i > index; --i) {
            data->Set(i, data->Get(i - 1));
        }
        data->Set(index, item);
        length++;
    }

    void Set(int index, const T& item) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        data->Set(index, item);
    }

    Sequence<T>* Concat(Sequence<T>* list) const {
        int newLength = length + list->GetLength();
        T* newArray = new T[newLength];
        for (int i = 0; i < length; ++i) {
            newArray[i] = data->Get(i);
        }
        for (int i = 0; i < list->GetLength(); ++i) {
            newArray[length + i] = list->Get(i);
        }
        Sequence<T>* newSequence = new ArraySequence<T>(newArray, newLength);
        delete[] newArray;
        return newSequence;
    }
};