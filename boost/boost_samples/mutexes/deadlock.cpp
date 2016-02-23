/*
  Deadlock!

  Illustrates two threads which will eventually enter a deadlock.  This is
  how NOT to write locks!

  The correct way is for each thread to lock the threads in the same order,
  and release them in the same reversed order.  Doing so is left as an
  exercise to the reader.

  The Maximum sleep delay parameters need to be tuned on your machine to
  reliably deadlock, as the deadlocking depends on the relative timing of
  events between the threads.

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details

  Note: you really don't want to copy this code as is, since it
  intentionally contains a fundamental design flaw!
 */

// NB: printf is used to avoid interleaved I/O with cout

#include <map>
#include <sstream>
#include <iostream>

#include <boost/thread.hpp>

#include "common.hpp"

// Flag to tell threads to quit
bool gRunning;

boost::mutex mutexA;
boost::mutex mutexB;

// Maximum sleep delays (in ms)
static const unsigned kMaxIdleTime = 25;
static const unsigned kMaxProcessingTime = 10;

void randomDelay(unsigned maxTime)
{
    boost::posix_time::milliseconds delayTime(random() % maxTime);
    boost::this_thread::sleep(delayTime);
}

// Lock order: A,B
void threadOne()
{
    while ( gRunning )
    {
        printf("ONE idle\n");
        randomDelay(kMaxIdleTime);

        printf("ONE wait_A\n");
        mutexA.lock();
        printf("ONE wait_B\n");
        mutexB.lock();

        printf("ONE processing\n");
        randomDelay(kMaxProcessingTime);

        printf("ONE unlock_B\n");
        mutexB.unlock();
        printf("ONE unlock_A\n");
        mutexA.unlock();
    }
}

// Lock order: B,A
void threadTwo()
{
    while ( gRunning )
    {
        printf("TWO idle\n");
        randomDelay(kMaxIdleTime);

        printf("TWO wait_B\n");
        mutexB.lock();
        printf("TWO wait_A\n");
        mutexA.lock();

        printf("TWO processing\n");
        randomDelay(kMaxProcessingTime);

        printf("TWO unlock_A\n");
        mutexA.unlock();
        printf("TWO unlock_B\n");
        mutexB.unlock();
    }
}

int main(int argc, char* argv[])
{
    // Start threads

    gRunning = true;

    boost::thread t1(threadOne);
    boost::thread t2(threadTwo);

    // Let them run for a while

    boost::posix_time::milliseconds workTime(5000);
    boost::this_thread::sleep(workTime);

    // Stop gracefully and wait

    gRunning = false;
    t1.join();
    t2.join();

    return 0;
}
