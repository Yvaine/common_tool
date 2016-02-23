/*
  Condition Variables - Many waiting threads

  Shows how one condition variable can be used to notify multiple threads
  that a condition has occured.

  * Part of "Threading with Boost - Part IV: Condition Variables", published at:

      http://antonym.org/boost

  Copyright (c) 2015 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
*/

#include <cstdio>

#include <boost/thread.hpp>

boost::condition_variable data_ready_cond;
boost::mutex data_ready_mutex;
bool data_ready = false;

void master_thread()
{
    printf("+++ master thread\n");

    // Pretend to work
    printf("    master sleeping...\n");
    boost::chrono::milliseconds sleepDuration(750);
    boost::this_thread::sleep_for(sleepDuration);

    // Let other threads know we're done
    printf("    master notifying...\n");
    {
        boost::unique_lock<boost::mutex> lock(data_ready_mutex);
        data_ready = true;
    }
    data_ready_cond.notify_all();

    printf("--- master thread\n");
}

void slave_thread(int id)
{
    printf("+++ slave thread: %d\n", id);

    boost::unique_lock<boost::mutex> lock(data_ready_mutex);
    while (!data_ready)
    {
        data_ready_cond.wait(lock);
    }

    printf("--- slave thread: %d\n", id);
}

int main()
{
    printf("Spawning threads...\n");

    boost::thread slave_1(slave_thread, 1);
    boost::thread slave_2(slave_thread, 2);
    boost::thread slave_3(slave_thread, 3);
    boost::thread slave_4(slave_thread, 4);

    boost::thread master(master_thread);

    printf("Waiting for threads to complete...\n");

    slave_1.join();
    slave_2.join();
    slave_3.join();
    slave_4.join();
    master.join();

    printf("Done\n");

	return 0;
}
