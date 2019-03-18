#include <iostream>
#include <cstdlib>
//#include <deque>
#include "monitor.h"

using namespace std;

#define Buffer_size 10


class Buffer: Monitor {

private:

    Condition prod;
    Condition cons;
    int elements = 0;
    int buffer[Buffer_size];


public:

    Buffer() = default;
    virtual ~Buffer() = default;

    bool isFull()
    {
        if (elements == 10)
            return true;
        return false;
    };
    bool isEmpty()
    {
        if (elements == 0)
            return true;
        return false;
    };

    void pruduce(int number)
    {
        enter();
        int to_produce = rand()%100;
        if (elements == 10)
            wait(cons);
        buffer[elements] = to_produce;
        elements++;
        cout << "Producent poduced "<<to_produce <<" to buffer number "<< number << endl;
        cout <<"Actual elements in buffer "<< number <<": ";
        for (int i = 0; i < elements; i++)
            cout <<buffer[i] <<" ";
        cout << endl;
        signal(prod);
        leave();
    };
    void consume(int number)
    {
        enter();
        while (elements == 0)
            wait(prod);
        cout <<"Consumer consumed: "<< buffer[elements-1]<<" from buffer "<<number<< endl;
        for (int i = 0; i < elements; i++)
            buffer[i] = buffer[i+1];
        elements--;
        signal(cons);
        leave();

    };

};
