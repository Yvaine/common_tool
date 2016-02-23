/*
  Timed Mutex Lock

  Shows how to use try_lock on a mutex.  A 'holding' thread idles for a
  short time, then grabs the mutex and holds it for another short time
  before unlocking it.  The second thread is the 'trying' thread, in that it
  idles and then *tries* to acquire a lock on the mutex.  But it specifies a
  timeout by calling the `timed_lock()` method, and can fail if the holding
  thread hasn't released the mutex in time.  If it manages to grab the
  mutex, it holds it for a short time also.  The idle and holding times are
  different, to ensure the threads don't run in lockstep.  Note that
  `unlock()` is only called if the lock succeeds!

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

// NB: printf is used to avoid interleaved I/O with cout

#include <stdio.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/thread.hpp>

#define DELAY_TIME      100

// Mutex representing shared resource
boost::timed_mutex    gMutex;

// Flag to stop threads
static bool gRunning;

void log(const char* msg)
{
    struct timeval sysTime;

    gettimeofday(&sysTime, NULL);

    double sysTimeMillis = sysTime.tv_sec + sysTime.tv_usec/1e6;

    printf("%6.5lf %s\n", sysTimeMillis, msg);
}

void holdingThread()
{
    log("H   1_start");

    while (gRunning)
    {
        log("H   2_idle");

        // Idle before locking
        boost::posix_time::milliseconds unlockedTime(500);
        boost::this_thread::sleep(unlockedTime);

        log("H   3_locking");

        gMutex.lock();

        log("H   5_working");

        // Hold the lock for a little while
        boost::posix_time::milliseconds holdTime(2000);
        boost::this_thread::sleep(holdTime);

        gMutex.unlock();

        log("H   4_unlocked");
    }

    log("H   0_stop");
}

/*
  Holds the mutex for a random period, and releases it
 */
void tryingThread()
{
    log("T   1_start");

    while (gRunning)
    {
        log("T   2_idle");

        // Slow things down a little
        boost::posix_time::milliseconds delayTime(600);
        boost::this_thread::sleep(delayTime);

        // Acquire lock with timeout

        boost::posix_time::time_duration lockTimeout(0, 0, 1); // h,m,s

        log("T   3_locking");

        if (gMutex.timed_lock(lockTimeout))
        {
            log("T   5_working");

            // Hold the lock for a while, pretend we're doing something useful
            boost::posix_time::milliseconds delayTime(400);
            boost::this_thread::sleep(delayTime);

            gMutex.unlock();
            log("T   4_unlocked");
        }
        else
        {
            log("T   0_timedout");
        }
    }

    log("T   0_stop");
}

int main(int argc, char* argv[])
{
    // Start threads
    gRunning = true;

    boost::thread t1(holdingThread);
    boost::thread t2(tryingThread);

    // Let them run for a while

    boost::posix_time::milliseconds workTime(10000);
    boost::this_thread::sleep(workTime);

    // Stop gracefully and wait

    gRunning = false;
    t1.join();
    t2.join();

    return 0;
}
