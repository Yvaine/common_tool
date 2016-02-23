/*
  Condition Variables - Many consumers, one producer

  Shows how a condition variable can be used to manage multiple worker
  threads to service a single producer.

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

std::vector<int> work_queue;
boost::mutex work_queue_mutex;

static const unsigned work_unit_limit = 100;

void producer_thread()
{
    printf("+++ producer thread\n");

    for (unsigned work_unit_count = 0; work_unit_count < work_unit_limit; work_unit_count++)
    {
        // Pretend to work

        boost::chrono::milliseconds sleepDuration(5);
        boost::this_thread::sleep_for(sleepDuration);

        // Generate some work
        {
            boost::lock_guard<boost::mutex> lock(work_queue_mutex);
    
            printf("    producer: produced %u...\n", work_unit_count);
            work_queue.push_back(work_unit_count);
        }

        // Let one of the slaves know there's work to be done
        {
            boost::unique_lock<boost::mutex> lock(data_ready_mutex);
            data_ready = true;
        }
        data_ready_cond.notify_one();
    }

    printf("--- producer thread\n");
}

void slave_thread(int id)
{
    printf("    +++ slave thread %d: starting\n", id);

    while (true)
    {
        boost::unique_lock<boost::mutex> lock(data_ready_mutex);
        while (!data_ready)
        {
            data_ready_cond.wait(lock);
        }
        data_ready = false;

        unsigned work_unit;
        {
            boost::lock_guard<boost::mutex> lock(work_queue_mutex);
            if (work_queue.size() == 0)
                abort();
            work_unit = work_queue.back();
            work_queue.pop_back();
        }
        printf("        slave thread %d: got work unit %u\n", id, work_unit);

        // Pretend to work
        boost::chrono::milliseconds sleepDuration(3);
        boost::this_thread::sleep_for(sleepDuration);
    }

    printf("    --- slave thread %d: finished\n", id);
}

int main()
{
    const unsigned N = 10;

    printf("Spawning %u consumer threads...\n", N);

    std::vector<boost::thread*> slaves;

    for (unsigned i = 0; i < N; i++)
    {
        slaves.push_back(new boost::thread(slave_thread, i));
    }

    boost::thread producer(producer_thread);

    printf("Waiting for threads to complete...\n");

    std::vector<boost::thread*>::iterator slave;
    for (slave = slaves.begin(); slave != slaves.end(); ++slave)
    {
        (*slave)->join();
        delete *slave;
    }

    producer.join();

    printf("Done (queue length %ld)\n", work_queue.size());

	return 0;
}
