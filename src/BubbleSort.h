#pragma once

#include "ISorter.h"

template <typename T>
class BubbleSort : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        int n = seq->GetLength();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (cmp(seq->Get(j), seq->Get(j + 1)) > 0) {
                    T temp = seq->Get(j);
                    seq->Set(j, seq->Get(j + 1));
                    seq->Set(j + 1, temp);
                }
            }
        }
        return seq;
    }
};
