/*
  Read-Write Shared Lock

  Shows how three worker threads can co-operate accessing a shared resource,
  where two are reading and the third is writing.  A network thread
  simulates producing data by ading random numbers to a container.  A
  display thread shows the data on screen, and a database thread writes the
  numbers to a file.  The network thread uses an exclusive write lock to
  update the shared data container, while the other two threads use a shared
  read-only lock, which means they can both concurrently access the data
  safely.  If the network thread tries to access the data while either of
  the other two have a read-lock, it has to wait until all threads release
  their shared locks.

  (Normally a producer-consumer setup such as this would use a Condition
  variable to signal when more data is ready, but we're saving that for a
  future installment.)

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2010-2014 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

#include "common.hpp"

#include <vector>
#include <iostream>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

// Flag to tell threads to quit
bool gRunning;

// Shared Read/Write mutex
boost::shared_mutex     sharedDataMutex;

// Shared data is just a list of numbers
std::vector<int>        sharedData;

// Maximum sleep delays (in ms)
static const unsigned kMaxIdleTime = 100;
static const unsigned kMaxProcessingTime = 220;

void randomDelay(unsigned maxTime)
{
    boost::posix_time::milliseconds delayTime(random() % maxTime);
    boost::this_thread::sleep(delayTime);
}

/*
  ~ network ~

  This thread updates the shared data by appending a new random number.
*/
void networkThread()
{
    while ( gRunning )
    {
        log(kLogStdout, "NETWORK  idle\n");
        randomDelay(kMaxIdleTime);

        log(kLogStdout, "NETWORK  lock\n");
        sharedDataMutex.lock();

        int newNumber = random() % 1000;

        sharedData.push_back(newNumber);

        log(kLogStdout, "NETWORK  writing\n");
        randomDelay(kMaxProcessingTime);

        log(kLogStdout, "NETWORK  unlock\n");
        sharedDataMutex.unlock();
    }
}

/*
  ~ display ~

  This thread displays the contents of the shared data.
*/
void displayThread()
{
    while ( gRunning )
    {
        log(kLogStdout, "DISPLAY  idle\n");
        randomDelay(kMaxIdleTime);

        log(kLogStdout, "DISPLAY  lock_shared\n");
        sharedDataMutex.lock_shared();

        log(kLogStdout, "DISPLAY  reading\n");
        randomDelay(kMaxProcessingTime);

        unsigned idx = 0;
        foreach(int& n, sharedData)
        {
            std::cout << "# " << idx++ << " " << n << std::endl;
        }

        log(kLogStdout, "DISPLAY  unlock_shared\n");
        sharedDataMutex.unlock_shared();
    }
}

/*
  ~ database ~

  The database thread saves a snapshot of the shared data to disk.
*/
void databaseThread()
{
    std::ofstream       dataFile("/tmp/sharedlock.dat");

    while ( gRunning )
    {
        log(kLogStdout, "DATABASE idle\n");
        randomDelay(kMaxIdleTime);

        log(kLogStdout, "DATABASE lock_shared\n");
        sharedDataMutex.lock_shared();

        log(kLogStdout, "DATABASE writing\n");
        randomDelay(kMaxProcessingTime);

        dataFile.seekp(0);

        unsigned idx = 0;
        foreach(int& n, sharedData)
        {
            dataFile << idx++ << " " << n << std::endl;
        }

        log(kLogStdout, "DATABASE unlock_shared\n");
        sharedDataMutex.unlock_shared();
    }
}

//

int main(int argc, char* argv[])
{
    std::cout << "tid       timestamp        thread   state" << std::endl;

    // Start threads

    gRunning = true;

    boost::thread network(networkThread);
    boost::thread display(displayThread);
    boost::thread database(databaseThread);

    // Let them run for a while

    boost::posix_time::milliseconds workTime(10000);
    boost::this_thread::sleep(workTime);

    // Stop gracefully and wait

    gRunning = false;
    network.join();
    display.join();
    database.join();

    return 0;
}
