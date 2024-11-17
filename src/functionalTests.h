#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include "ISorter.h"
#include "ArraySequence.h"
#include "BubbleSort.h"
#include "ShakerSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "ListSequence.h"

bool CompareSequences(Sequence<int>* seq1, Sequence<int>* seq2) {
    if (seq1->GetLength() != seq2->GetLength()) {
        return false;
    }
    for (int i = 0; i < seq1->GetLength(); ++i) {
        if (seq1->Get(i) != seq2->Get(i)) {
            return false;
        }
    }
    return true;
}


std::string FTestArraySequence(ISorter<int>* sorter, std::string& method) {
    std::vector<std::vector<int>> testCases = {
        {5, 2, 9, 1, 5, 6},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1},
        {}
    };
    bool all_passed = true;
    for (const auto& testCase : testCases) {
        std::vector<int> expected = testCase;
        std::sort(expected.begin(), expected.end());

        Sequence<int>* sequence = new ArraySequence<int>;
        for(int num: testCase){
            sequence->Append(num);
        }

        sorter->Sort(sequence, [](int a, int b) { return a - b; });

        Sequence<int>* expectedSequence = new ArraySequence<int>;
        for(int num: expected){
            expectedSequence->Append(num);
        }
        bool passed = CompareSequences(sequence, expectedSequence);
        all_passed = all_passed == false ? false : passed;
    }
    std::ostringstream result;
    result << (all_passed ? "PASSED" : "FAILED") << ": " << method << std::endl;
    return result.str();
}

std::string FTestListSequence(ISorter<int>* sorter, std::string& method) {
    std::vector<std::vector<int>> testCases = {
        {5, 2, 9, 1, 5, 6},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1},
        {}
    };
    bool all_passed = true;
    for (const auto& testCase : testCases) {
        std::vector<int> expected = testCase;
        std::sort(expected.begin(), expected.end());

        Sequence<int>* sequence = new ListSequence<int>;
        for(int num: testCase){
            sequence->Append(num);
        }

        sorter->Sort(sequence, [](int a, int b) { return a - b; });

        Sequence<int>* expectedSequence = new ListSequence<int>;
        for(int num: expected){
            expectedSequence->Append(num);
        }
        bool passed = CompareSequences(sequence, expectedSequence);
        all_passed = all_passed == false ? false : passed;
    }
    std::ostringstream result;
    result << (all_passed ? "PASSED" : "FAILED") << ": " << method << std::endl;
    return result.str();
}

void TestAllMethods(){
    std::vector<std::pair<ISorter<int>*, std::string>> methods;
    methods.push_back({new BubbleSort<int>, "Bubble Sort"});
    methods.push_back({new ShakerSort<int>, "Shaker Sort"});
    methods.push_back({new QuickSort<int>, "Quick Sort"});
    methods.push_back({new MergeSort<int>, "Merge Sort"});
    for(auto method: methods){
        std::cout << FTestArraySequence(method.first, method.second) << std::endl;
    }
    for(auto method: methods){
        std::cout << FTestListSequence(method.first, method.second) << std::endl;
    }
}