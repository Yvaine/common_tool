/*
  Thread Function with Arguments

  * Part of "Threading with Boost - Part I: Creating Threads", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

#include <iostream>
#include <boost/thread.hpp>

void workerFunc(const char* msg, float delay_ms)
{
    boost::posix_time::milliseconds workTime(delay_ms);

    std::cout << "Worker: running, message = " << msg << std::endl;

    // Pretend to do something useful...
    boost::this_thread::sleep(workTime);

    std::cout << "Worker: finished" << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "main: startup" << std::endl;

    boost::thread workerThread(workerFunc, "Hello, Boost!", 2.5e3);

    std::cout << "main: waiting for thread" << std::endl;

    workerThread.join();

    std::cout << "main: done" << std::endl;

    return 0;
}
