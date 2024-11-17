#pragma once

#include "ISorter.h"

template <typename T>
class MergeSort : public ISorter<T> {
private:
    void Merge(Sequence<T>* seq, int left, int mid, int right, int (*cmp)(T, T)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Sequence<T>* leftSeq = seq->GetSubsequence(left, mid);
        Sequence<T>* rightSeq = seq->GetSubsequence(mid + 1, right);

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (cmp(leftSeq->Get(i), rightSeq->Get(j)) <= 0) {
                seq->Set(k++, leftSeq->Get(i++));
            } else {
                seq->Set(k++, rightSeq->Get(j++));
            }
        }

        while (i < n1) {
            seq->Set(k++, leftSeq->Get(i++));
        }

        while (j < n2) {
            seq->Set(k++, rightSeq->Get(j++));
        }

        delete leftSeq;
        delete rightSeq;
    }

    void MergeSortHelper(Sequence<T>* seq, int left, int right, int (*cmp)(T, T)) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSortHelper(seq, left, mid, cmp);
            MergeSortHelper(seq, mid + 1, right, cmp);
            Merge(seq, left, mid, right, cmp);
        }
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        MergeSortHelper(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};
