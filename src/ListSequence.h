#pragma once

#include "Sequence.h"
#include "LinkedList.h"
#include <stdexcept>

template<class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> list;

public:
    ListSequence();
    ListSequence(const T* items, int count);
    ListSequence(const ListSequence<T>& sequence);
    ListSequence(const LinkedList<T>& list);

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;
    void Append(const T& item) override;
    void Prepend(const T& item) override;
    void InsertAt(const T& item, int index) override;
    void Set(int index, const T& item) override;
    Sequence<T>* Concat(Sequence<T>* list) const override;
};

template<class T>
ListSequence<T>::ListSequence() : list() {}

template<class T>
ListSequence<T>::ListSequence(const T* items, int count) : list(items, count) {}

template<class T>
ListSequence<T>::ListSequence(const ListSequence<T>& sequence) : list(sequence.list) {}

template<class T>
ListSequence<T>::ListSequence(const LinkedList<T>& list) : list(list) {}

template<class T>
T ListSequence<T>::GetFirst() const {
    if (list.GetLength() == 0) throw std::out_of_range("Sequence is empty");
    return list.GetFirst();
}

template<class T>
T ListSequence<T>::GetLast() const {
    if (list.GetLength() == 0) throw std::out_of_range("Sequence is empty");
    return list.GetLast();
}

template<class T>
T ListSequence<T>::Get(int index) const {
    if (index < 0 || index >= list.GetLength()) throw std::out_of_range("Sequence is empty");
    return list.Get(index);
}

template<class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= list.GetLength() || startIndex > endIndex)
        throw std::out_of_range("Invalid indices");

    ListSequence<T>* subList = new ListSequence<T>();
    for (int i = startIndex; i <= endIndex; ++i) {
        subList->Append(list.Get(i));
    }
    return subList;
}

template<class T>
int ListSequence<T>::GetLength() const {
    return list.GetLength();
}

template<class T>
void ListSequence<T>::Append(const T& item) {
    list.Append(item);
}

template<class T>
void ListSequence<T>::Prepend(const T& item) {
    list.Prepend(item);
}

template<class T>
void ListSequence<T>::InsertAt(const T& item, int index) {
    list.InsertAt(item, index);
}

template<class T>
void ListSequence<T>::Set(int index, const T& item) {
    if (index < 0 || index >= list.GetLength()) {
        throw std::out_of_range("Invalid index");
    }
    list.Set(index, item);
}

template<class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* otherList) const {
    ListSequence<T>* result = new ListSequence<T>();
    for (int i = 0; i < this->GetLength(); i++) {
        result->Append(this->Get(i));
    }
    for (int i = 0; i < otherList->GetLength(); i++) {
        result->Append(otherList->Get(i));
    }
    return result;
}
