//
// Created by vasan on 10/5/2019.
//
#include "objectPoolTest.h"
#include <future>
using namespace VObjectPool;

TEST_F(ObjectPoolTest, t1_newAddress) {
    // check if each objects is created at a new address
    ObjectPool<5>* obj1 = new ObjectPool<5>(100);
    cout << "newAddress:: Address of obj1: " << obj1 << endl;
    ObjectPool<5>* obj2 = new ObjectPool<5>(200);
    cout << "newAddress:: Address of obj2: " << obj2 << endl;
    ObjectPool<5>* obj3 = new ObjectPool<5>(300);
    cout << "newAddress:: Address of obj3: " << obj3 << endl;
    ObjectPool<5>* obj4 = new ObjectPool<5>(400);
    cout << "newAddress:: Address of obj4: " << obj4 << endl;
    ObjectPool<5>* obj5 = new ObjectPool<5>(500);
    cout << "newAddress:: Address of obj5: " << obj5 << endl;
    ObjectPool<5>* obj6 = new ObjectPool<5>(600);
    cout << "newAddress:: Address of obj6: " << obj6 << endl;

    EXPECT_NE(obj1, obj2);
    EXPECT_NE(obj2, obj3);
    EXPECT_NE(obj3, obj4);
    EXPECT_NE(obj4, obj5);
    EXPECT_NE(obj5, obj6);

    delete obj1;
    delete obj2;
    delete obj3;
    delete obj4;
    delete obj5;
    delete obj6;

}

TEST_F(ObjectPoolTest, t2_reuseAddress) {
    ObjectPool<5> *obj1 = new ObjectPool<5>(100);
    cout << "reuseAddress:: Address of obj1: " << obj1 << endl;
    ObjectPool<5> *obj2 = new ObjectPool<5>(200);
    cout << "reuseAddress:: Address of obj2: " << obj2 << endl;

    long address2 = (long) obj2;
    delete obj2;
    obj2 = nullptr;

    ObjectPool<5> *obj3 = new ObjectPool<5>(300);
    cout << "reuseAddress:: Address of obj3: " << obj3 << endl;
    EXPECT_EQ(address2, (long) obj3);

    ObjectPool<5> *obj4 = new ObjectPool<5>(400);
    cout << "reuseAddress:: Address of obj4: " << obj4 << endl;
    long address1 = (long) obj1;
    delete obj1;
    obj1 = nullptr;

    ObjectPool<5> *obj5 = new ObjectPool<5>(500);
    cout << "reuseAddress:: Address of obj5: " << obj5 << endl;

    delete obj3;
    delete obj4;
    delete obj5;
}

TEST_F(ObjectPoolTest, t3_holdValues) {
    ObjectPool<5>* obj1 = new ObjectPool<5>(100);
    cout << "holdValues:: Address of obj1: " << obj1 << endl;
    ObjectPool<5>* obj2 = new ObjectPool<5>(200);
    cout << "holdValues:: Address of obj2: " << obj2 << endl;

    int val2 = obj2->get();
    delete obj2;
    obj2 = nullptr;

    ObjectPool<5>* obj3 = new ObjectPool<5>(300);
    cout << "holdValues:: Address of obj3: " << obj3 << endl;
    ObjectPool<5>* obj4 = new ObjectPool<5>(400);
    cout << "holdValues:: Address of obj4: " << obj4 << endl;

    EXPECT_NE(val2, obj3->get());
    EXPECT_NE(obj1->get(), obj3->get());
    EXPECT_NE(obj3->get(), obj4->get());
    EXPECT_NE(obj1->get(), obj4->get());
}

vector<long> threadFunc() {
    ObjectPool<5>* ob1 = new ObjectPool<5>(100);
    ObjectPool<5>* ob2 = new ObjectPool<5>(200);
    ObjectPool<5>* ob3 = new ObjectPool<5>(300);
    ObjectPool<5>* ob4 = new ObjectPool<5>(400);
    ObjectPool<5>* ob5 = new ObjectPool<5>(500);
    ObjectPool<5>* ob6 = new ObjectPool<5>(600);

    cout << "threadFunc: address of ob1: " << ob1 << endl;
    cout << "threadFunc: address of ob2: " << ob2 << endl;
    cout << "threadFunc: address of ob3: " << ob3 << endl;
    cout << "threadFunc: address of ob4: " << ob4 << endl;
    cout << "threadFunc: address of ob5: " << ob5 << endl;
    cout << "threadFunc: address of ob6: " << ob6 << endl;

    vector<long> vec;
    vec.push_back((long)ob1);
    vec.push_back((long)ob2);
    vec.push_back((long)ob3);
    vec.push_back((long)ob4);
    vec.push_back((long)ob5);
    vec.push_back((long)ob6);
    return vec;
}

TEST_F(ObjectPoolTest, t5_multiThread) {
    future<vector<long>> fut = async(launch::async, threadFunc);
    vector<long> vec = fut.get();

    ObjectPool<5>* ob1 = new ObjectPool<5>(100);
    ObjectPool<5>* ob2 = new ObjectPool<5>(200);
    ObjectPool<5>* ob3 = new ObjectPool<5>(300);
    ObjectPool<5>* ob4 = new ObjectPool<5>(400);
    ObjectPool<5>* ob5 = new ObjectPool<5>(500);
    ObjectPool<5>* ob6 = new ObjectPool<5>(600);

    cout << "main: address of ob1: " << ob1 << endl;
    cout << "main: address of ob2: " << ob2 << endl;
    cout << "main: address of ob3: " << ob3 << endl;
    cout << "main: address of ob4: " << ob4 << endl;
    cout << "main: address of ob5: " << ob5 << endl;
    cout << "main: address of ob6: " << ob6 << endl;

    vector<long>::iterator itr;
    itr = find(vec.begin(), vec.end(), (long)ob1);
    EXPECT_EQ(itr, vec.end());
    itr = find(vec.begin(), vec.end(), (long)ob2);
    EXPECT_EQ(itr, vec.end());
    itr = find(vec.begin(), vec.end(), (long)ob3);
    EXPECT_EQ(itr, vec.end());
    itr = find(vec.begin(), vec.end(), (long)ob4);
    EXPECT_EQ(itr, vec.end());
    itr = find(vec.begin(), vec.end(), (long)ob5);
    EXPECT_EQ(itr, vec.end());
    itr = find(vec.begin(), vec.end(), (long)ob6);
    EXPECT_EQ(itr, vec.end());

}