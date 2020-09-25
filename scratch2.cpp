//
// Created by vasan on 4/30/2020.
//

#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Points {
    Points(int mi, int ma) : min(mi), max(ma) {};
    int min;
    int max;

};

struct Compare {
    bool operator()(const Points& lhs, const Points&rhs) {
        return lhs.max < rhs.min;
    }
};

int main() {
    vector v = {6, 2, 9, 1};
    make_heap(v.begin(), v.end());

    cout << v.front() << endl;      // 9
    pop_heap(v.begin(), v.end());

    cout << v.front() << endl;      // 6
    pop_heap(v.begin(), v.end() - 1);

    cout << v.front() << endl;      // 2
    pop_heap(v.begin(), v.end() - 2);

    cout << v.front() << endl;      // 1
    pop_heap(v.begin(), v.end() - 3) ;


    for_each(v.begin(), v.end(), [](int i ){cout << i << " ";});
}