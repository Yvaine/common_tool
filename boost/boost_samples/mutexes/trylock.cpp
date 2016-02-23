/*
  Trylock with Queueing Threads

  Illustrates two cooperating threads: a producer placing work items in a
  queue, and a consumer which removes work items from the queue.  The shared
  queue is protected by a mutex.  Each thread locks the mutex when pushing
  or pulling work items, to protect against concurrent access.  Work items
  are arbitrarily represented by random numbers.  Each thread holds the lock
  for a random time delay to simulate processing.

  Since the producer may be holding the lock when the consumer wants to
  access the queue (or vice versa), the consumer performs a `try_lock` on
  the mutex.  So instead of blocking until the mutex is free (as a regular
  call to `lock()` would), the call fails immediately if the mutex is
  already locked, and the thread resumes.

  Each thread prints out the stage it is executing, to enable analysis of
  the interaction.

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

// NB: printf is used to avoid interleaved I/O with cout

#include <stdio.h>
#include <vector>
#include <boost/thread.hpp>

// Maximum sleep delay
static const unsigned kMaxSleepTime_ms = 500;

// Work queue, a shared resource protected by a mutex
typedef std::vector<long>   workqueue_t;
workqueue_t                 gWorkQueue;
boost::mutex                gWorkQueueMutex;

// Flag to tell threads to quit
bool gRunning;

// Consumes items in work queue
void consumerThread()
{
    while (gRunning)
    {
        if (gWorkQueueMutex.try_lock())
        {
            if (gWorkQueue.size())
            {
                long val = gWorkQueue.back();
                gWorkQueue.pop_back();

                printf("vvv %ld\n", val);
            }

            // Hold the mutex for a little while
            boost::posix_time::milliseconds delayTime(50);
            boost::this_thread::sleep(delayTime);

            gWorkQueueMutex.unlock();
        }
        else
        {
            printf("v==\n");
        }

        // Slow things down a little
        boost::posix_time::milliseconds delayTime(random() % kMaxSleepTime_ms);
        boost::this_thread::sleep(delayTime);
    }
}

// Produces work items for queue
void producerThread()
{
    while (gRunning)
    {
        if (gWorkQueueMutex.try_lock())
        {
            long val = random();

            gWorkQueue.push_back(val);

            printf("^^^ %ld\n", val);

            // Hold the mutex for a little while
            boost::posix_time::milliseconds delayTime(15);
            boost::this_thread::sleep(delayTime);

            gWorkQueueMutex.unlock();
        }
        else
        {
            printf("^==\n");
        }

        // Slow things down a little
        boost::posix_time::milliseconds delayTime(random() % kMaxSleepTime_ms);
        boost::this_thread::sleep(delayTime);
    }
}

int main(int argc, char* argv[])
{
    // Start threads

    gRunning = true;

    boost::thread t1(producerThread);
    boost::thread t2(consumerThread);

    // Let them run for a while

    boost::posix_time::milliseconds workTime(5000);
    boost::this_thread::sleep(workTime);

    // Stop gracefully and wait

    gRunning = false;
    t1.join();
    t2.join();

    return 0;
}
