#include <iostream>
#include <Thread.h>

using namespace VThread;

class Account {
public:
    Account(long lBalance) : _lBalance(lBalance) {
        cout << "Account constructed" << endl;
    }
    virtual ~Account() {
        cout << "Account destroyed" << endl;
    }
    void deposit(long lAmount) {
      _lBalance += lAmount;
        cout << "Deposit " << lAmount << ", balance " << _lBalance << endl;
    };

    long withdraw(long lAmount) {
        if (_lBalance >= lAmount) {
            _lBalance -= lAmount;
            cout << "Withdraw " << lAmount << ", balance " << _lBalance << endl;
            return lAmount;
        } else {
            return 0;
        }
    };
private:
    long _lBalance;
};
class DepositHandler : public Thread {
public:
    DepositHandler(shared_ptr<Account> oAcc, int iThreadId, int iLoop) : Thread(iThreadId), _oAccount(oAcc), _iLoop(iLoop){};
    virtual ~DepositHandler(){};

    void run() {
        cout << "Deposit handler running.." << endl;
        for (int i = 0; i < _iLoop; ++i) {
            _oAccount->deposit(1000);
        }
    };
private:
    shared_ptr<Account> _oAccount;
    int _iLoop;
};

class WithdrawHandler : public Thread {
public:
    WithdrawHandler(shared_ptr<Account> oAcc, int iThreadId, int iLoop) : Thread(iThreadId), _oAccount(oAcc), _iLoop(iLoop){};
    virtual ~WithdrawHandler(){};

    void run() {
        cout << "Withdraw handler running.." << endl;
        for (int i = 0; i < _iLoop; ++i) {
            _oAccount->withdraw(1000);
        }
    };
private:
    shared_ptr<Account> _oAccount;
    int _iLoop;
};


int main() {
    shared_ptr<Account> oAcc = make_shared<Account>(1000);
    DepositHandler oDep(oAcc, 1, 5);
    WithdrawHandler oWith(oAcc, 2, 5);

    oDep.start();
    oWith.start();

    oDep.join();
    oWith.join();
    //this_thread::sleep_for(chrono::seconds(10));
    return 0;
}
