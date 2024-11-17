#pragma once

#include "ISorter.h"

template <typename T>
class ShakerSort : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        int left = 0, right = seq->GetLength() - 1;
        while (left < right) {
            for (int i = left; i < right; ++i) {
                if (cmp(seq->Get(i), seq->Get(i + 1)) > 0) {
                    T temp = seq->Get(i);
                    seq->Set(i, seq->Get(i + 1));
                    seq->Set(i + 1, temp);
                }
            }
            --right;

            for (int i = right; i > left; --i) {
                if (cmp(seq->Get(i - 1), seq->Get(i)) > 0) {
                    T temp = seq->Get(i);
                    seq->Set(i, seq->Get(i - 1));
                    seq->Set(i - 1, temp);
                }
            }
            ++left;
        }
        return seq;
    }
};
