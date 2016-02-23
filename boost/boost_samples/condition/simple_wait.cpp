/*
  Simple Condition Variable example

  The simplest possible Condition Variable example.

  * Part of "Threading with Boost - Part V: Condition Variables", published at:

      http://antonym.org/boost

  Copyright (c) 2015 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
*/

#include <cstdio>
#include <queue>

#include <boost/thread.hpp>

boost::condition_variable cond;
boost::mutex cond_mutex;
bool finished = false;

void primary_thread()
{
    printf("primary starting\n");

    // Pretend to do some work
    boost::chrono::milliseconds sleepDuration(500);
    boost::this_thread::sleep_for(sleepDuration);

    {
        boost::unique_lock<boost::mutex> lock(cond_mutex);
        finished = true;
    }

    printf("notify\n");
    cond.notify_one();

    printf("primary done\n");
}

void secondary_thread()
{
    printf("secondary starting\n");

    boost::unique_lock<boost::mutex> lock(cond_mutex);

    while (!finished)
    {
        cond.wait(lock);
    }

    /*
      If your compiler supports C++11 lambda functions, you can do this:

      cond.wait(lock, [](){ return finished; });
    */

    printf("secondary done\n");
}

int main(int argc, char* argv[])
{
    printf("Spawning threads\n");

    boost::thread primary(primary_thread);
    boost::thread secondary(secondary_thread);

    printf("Joining threads\n");

    primary.join();
    secondary.join();

    printf("Done\n");

    return 0;
}
