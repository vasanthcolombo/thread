//
// Created by vasan on 10/19/2019.
//
#include "messagePipe.h"
#include "consumer.h"
#include "producer.h"

template <class T>
class MessagePipe;

class Number {
public:
    Number(int l) : value(l){};
    int getValue() {
        return value;
    }
private:
    int value;
};

class NumberProducer : public Producer<Number>, public Thread {
public:
    NumberProducer(std::shared_ptr<MessagePipe<Number>> pipe) : Producer<Number>(pipe){};

private:
    void run() {
        for (int i = 0; i < 10; i++) {
            put(move(make_unique<Number>(i)));
        }
    }
};

class NumberConsumer : public Consumer<Number>, public Thread {
public:
    NumberConsumer(std::shared_ptr<MessagePipe<Number>> pipe) : Consumer<Number>(pipe){};

private:
    void run() {
        for (int i = 0; !is_stopped(); ++i) {
            cout << get()->getValue() << endl;
        }
    }
};
int main() {
    std::shared_ptr<MessagePipe<Number>> pipe = std::make_shared<MessagePipe<Number>>();

    NumberProducer producer(pipe);
    NumberConsumer consumer(pipe);

    producer.start();
    consumer.start();

    producer.join();
    consumer.stop();
    consumer.join();
}