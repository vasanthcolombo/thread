//
// Created by vasan on 2/22/2020.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <random>

using namespace std;

class Cat {
public:
    Cat(int i) : legs(i){
        cout << "Constructor " << i << endl;
    };
    Cat(const Cat& cat) : legs(cat.legs) {
        cout << "Copy constructor " << legs << endl;
    }
    Cat& operator=(const Cat& cat) {
        if (this != &cat) {
            legs = cat.legs;
        }
        cout << "copy assignment operator " << legs << endl;
        return *this;
    };
    Cat(Cat&& cat) : legs(cat.legs){
        cat.legs = 0;
        cout << "move constructor " << legs << endl;
    }
    Cat& operator=(Cat&& cat) {
        if (this != &cat) {
            legs = cat.legs;
            cat.legs = 0;
        }
        cout << "move assignment operator " << legs << endl;
        return *this;
    };

    int legs;
};

template <class T, class func>
typename vector<T>::iterator part(typename vector<T>::iterator first, typename vector<T>::iterator last, func f) {
    while(first != last) {
        while(f(*first)) {
            ++first;
            if (first == last) {
                return first;
            }
        }

        while(!f(*(--last))) {
            if (first == last)
                return first;
        }

        swap(*first, *last);
        first++;
        //last--;
    }
    return first;
}

template <typename T>
void rotate(typename vector<T>::iterator first, typename vector<T>::iterator middle, typename vector<T>::iterator end) {
    typename vector<T>::iterator next;
    next = middle;
    while(first != next) {
        swap(*first++, *next++);

        if (next == end) {
            next = middle;
        }
        else if (first == middle)
            middle = next;
    }
}

template <typename T, typename F>
void shuff(typename vector<T>::iterator first, typename vector<T>::iterator last, F generator) {
    std::uniform_int_distribution<int> distributor(0, last - first );
    typename vector<T>::iterator current = first;
    while(current != last) {
        swap(*current++, *(first + distributor(generator)));
    }
}

template <typename T>
bool next_perm(T first, T end) {
    if (first == end) {
        return false;
    }
    T last = end - 1;
    if (first == last) {
        return false;
    }
    T elem = end - 1;
    T next_elem = end;

    while (true) {
        if (*--elem < *--next_elem) {
            T bigger_elem = end;

            while(!(*elem < *(--bigger_elem)));

            swap(*elem, *bigger_elem);
            reverse(next_elem, end);
            return true;
        }
        if (elem == first) {
            reverse(first, end);
            return false;
        }
    }
}

Cat getCat() {
    return Cat(10);
}

template <typename T>
void rota(T first, T end) {
    end--;
    while(first < end) {
        swap(*first++, *end--);
    }
}

int main() {
    vector<int> v = {4,6,7,1,2,10};

    rota(v.begin(), v.end());
    for_each(v.begin(), v.end(), [](int i) {cout << " " << i;});
}