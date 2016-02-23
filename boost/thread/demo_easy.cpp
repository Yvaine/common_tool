/*
 *  2016.2.23 21:22
 *  author: lengjing
 */

#include <boost/thread/thread.hpp>
#include <iostream>

void hello()
{
    std::cout << "hello world , I am a thread" << std::endl;
}

int main(int argc, char *argv[])
{
    boost::thread thrd(&hello);
    thrd.join();
    return 0;
}


