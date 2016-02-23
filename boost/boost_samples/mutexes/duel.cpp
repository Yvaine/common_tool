/*
  Duelling Threads

  Illustrates a simplistic race condition where two threads are modifying a
  shared counter.  Note that this is intentionally a poor example, as the
  shared resource is not protected by a mutex.  Do not follow this example!

  @todo Make more interesting by having conflicted states.

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

// NB: printf is used to avoid interleaved I/O with cout

#include <stdio.h>
#include <boost/thread.hpp>

#define DELAY_TIME 5

// Unprotected shared resource
long gCounter;

// Flag to tell threads to quit
bool gRunning;

// Verbose flag to print counter while running
bool gVerbose;

void incrementThread()
{
    while (gRunning)
    {
        gCounter ++;

        if (gVerbose)
            printf("++ %ld\n", gCounter);

        // Slow things down a little
        boost::posix_time::milliseconds delayTime(DELAY_TIME);
        boost::this_thread::sleep(delayTime);
    }
}

void decrementThread()
{
    while (gRunning)
    {
        gCounter --;

        if (gVerbose)
            printf("-- %ld\n", gCounter);

        // Slow things down a little
        boost::posix_time::milliseconds delayTime(DELAY_TIME);
        boost::this_thread::sleep(delayTime);
    }
}

int main(int argc, char* argv[])
{
    gVerbose = (argc > 1);

    // Start threads

    gCounter = 0;
    gRunning = true;

    boost::thread t1(incrementThread);
    boost::thread t2(decrementThread);

    // Let them run for a while

    boost::posix_time::milliseconds workTime(5);
    boost::this_thread::sleep(workTime);

    // Stop gracefully and wait

    gRunning = false;
    t1.join();
    t2.join();

    printf("Final counter = %ld\n", gCounter);

    return 0;
}
