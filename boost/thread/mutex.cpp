/*
 *  2016.2.23 21:22
 *  author: lengjing
 */

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

#include <iostream>

boost::mutex mutex;
using namespace std;

long num = 0;

void get()
{
    for(int i = 0; i < 4 ; i++){
    mutex.lock();
    num++;
    cout << "get thread "<<num << endl;
    mutex.unlock();

}
}

int main(int argc, char *argv[])
{
    int number = 0;
    boost::thread thrd(get);
    for(int i = 0; i < 4 ; i++){
        mutex.lock();
        num--;
        cout << " main "<<num << endl;
        mutex.unlock();

    }
    thrd.join();

    return 0;
}
