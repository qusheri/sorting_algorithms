#pragma once

#include "ISorter.h"

template <typename T>
class QuickSort : public ISorter<T> {
private:
    int Partition(Sequence<T>* seq, int low, int high, int (*cmp)(T, T)) {
        T pivot = seq->Get(high);
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (cmp(seq->Get(j), pivot) <= 0) {
                ++i;
                T temp = seq->Get(i);
                seq->Set(i, seq->Get(j));
                seq->Set(j, temp);
            }
        }
        T temp = seq->Get(i + 1);
        seq->Set(i + 1, seq->Get(high));
        seq->Set(high, temp);
        return i + 1;
    }

    void QuickSortHelper(Sequence<T>* seq, int low, int high, int (*cmp)(T, T)) {
        if (low < high) {
            int pi = Partition(seq, low, high, cmp);
            QuickSortHelper(seq, low, pi - 1, cmp);
            QuickSortHelper(seq, pi + 1, high, cmp);
        }
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        QuickSortHelper(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};
