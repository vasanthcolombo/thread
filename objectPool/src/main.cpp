//
// Created by vasan on 9/28/2019.
//
#include "objectPool.h"
#include <iostream>

using namespace std;
using namespace VObjectPool;

int main() {
    //cout << hex;

    ObjectPool<5>* obj1 = new ObjectPool<5>(100);
    cout << "obj1: " << obj1 << endl;

    ObjectPool<5>* obj2 = new ObjectPool<5>(200);
    cout << "obj2: " << obj2 << endl;

    delete obj2;
    obj2 = nullptr;

    ObjectPool<5>* obj3 = new ObjectPool<5>(300);
    cout << "obj3: " << obj3 << endl;

    ObjectPool<5>* obj4 = new ObjectPool<5>(400);
    cout << "obj4: " << obj4 << endl;

    cout << "value of obj1 " << obj1->get() << endl;
    cout << "value of obj3: " << obj3->get() << endl;
    cout << "value of obj4: " << obj4->get() << endl;
    return 0;
}