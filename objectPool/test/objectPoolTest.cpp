//
// Created by vasan on 10/5/2019.
//
#include "objectPoolTest.h"

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