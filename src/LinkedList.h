#pragma once

#include <stdexcept>
#include <cstddef>

template<class T>
class LinkedListNode {
public:
    T value;
    LinkedListNode<T>* next;

    LinkedListNode(const T& value, LinkedListNode<T>* next = nullptr)
        : value(value), next(next) {}
};

template<class T>
class LinkedList {
private:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    size_t length;

    void Clear() {
        while (head != nullptr) {
            LinkedListNode<T>* current = head;
            head = head->next;
            delete current;
        }
        tail = nullptr;
        length = 0;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(const T* items, int count) : head(nullptr), tail(nullptr), length(0) {
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), length(0) {
        LinkedListNode<T>* current = list.head;
        while (current != nullptr) {
            Append(current->value);
            current = current->next;
        }
    }

    ~LinkedList() {
        Clear();
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= this->length) {
            throw std::out_of_range("Index out of range");
        }
        auto* subList = new LinkedList<T>();
        LinkedListNode<T>* current = this->head;
        for (int i = 0; i < startIndex; ++i) {
            current = current->next;
        }
        for (int i = startIndex; i <= endIndex; ++i) {
            subList->Append(current->value);
            current = current->next;
        }
        return subList;
    }

    void Append(T item) {
        LinkedListNode<T>* node = new LinkedListNode<T>(item, nullptr);
        if (tail == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        length++;
    }

    void Prepend(T item) {
        LinkedListNode<T>* newNode = new LinkedListNode<T>(item, head);
        head = newNode;
        if (length == 0) {
            tail = newNode;
        }
        length++;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > length) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            Prepend(item);
            return;
        }
        if (index == length) {
            Append(item);
            return;
        }
        LinkedListNode<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        LinkedListNode<T>* newNode = new LinkedListNode<T>(item, current->next);
        current->next = newNode;
        length++;
    }

    size_t GetLength() const {
        return length;
    }

    T GetFirst() const {
        if (head == nullptr) throw std::out_of_range("LinkedList is empty");
        return head->value;
    }

    T GetLast() const {
        if (tail == nullptr) throw std::out_of_range("LinkedList is empty");
        return tail->value;
    }

    T Get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        LinkedListNode<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    void Set(int index, const T& value) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        LinkedListNode<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->value = value;
    }
};
