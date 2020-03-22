//
// Created by vasan on 10/19/2019.
//
#include "pcFW.h"
#include "consumer.h"
#include "producer.h"

template <class T>
class PCFW;

class Number {
public:
    Number(int l) : value(l){};
    int getValue() {
        return value;
    }
private:
    int value;
};

class NumberProducer : public Producer<Number> {
public:
    NumberProducer(PCFW<Number>& fw) : Producer<Number>(fw){};

private:
    void run() {
        for (int i = 0; i < 10; i++) {
            put(move(make_unique<Number>(i)));
        }
    }
};

class NumberConsumer : public Consumer<Number> {
public:
    NumberConsumer(PCFW<Number>& fw) : Consumer<Number>(fw){};

private:
    void run() {
        for (int i = 0; i < 10; ++i) {
            cout << Consumer<Number>::get()->getValue() << endl;
        }
    }
};
int main() {
    PCFW<Number> num;

    NumberProducer producer(num);
    NumberConsumer consumer(num);

    producer.start();
    consumer.start();

    producer.join();
    consumer.join();
}