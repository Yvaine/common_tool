/*
  Recursive Lock

  Illustrates recursively locking a mutex.  A singleton class,
  ResourceManager, can register and unregister clients.  Since this may be
  called from the context of any worker thread, it uses a mutex when
  accessing the dictionary of client information.  Since retain/release
  management also requires the mutex be held during updates, this serves as
  an illustration of recursive locking.  These methods can be called
  individually, or from within the register/unregister methods, which also
  hold the mutex.  For example:

      registerClient()                  lockCount = 0
          mMutex.lock()                 lockCount = 1
          retainClient()                lockCount = 1
              mMutex.lock()             lockCount = 2
              mMutex.unlock()           lockCount = 1
          mMutex.unlock()               lockCount = 0

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

// NB: printf is used to avoid interleaved I/O with cout

#include <stdio.h>
#include <stdarg.h>

#include <map>
#include <sstream>
#include <iostream>

#include <boost/thread.hpp>

// Maximum sleep delay
static const unsigned kMaxSleepTime_ms = 500;

void log(const char* msg, ...)
{
    va_list             args;
    char                buf[512];
    struct timeval      sysTime;
    double              sysTimeMillis;
    int                 offset;

    va_start(args, msg);

    gettimeofday(&sysTime, NULL);
    sysTimeMillis = sysTime.tv_sec + sysTime.tv_usec/1e6;

    offset = snprintf(buf, sizeof(buf), "%08lx %6.5lf: ",
                      (unsigned long)pthread_self(),
                      sysTimeMillis);

    if (offset && offset < (int)sizeof(buf))
        vsnprintf(buf+offset, sizeof(buf)-offset, msg, args);
    else
        fprintf(stderr, "log fail: offset=%d\n", offset);

    printf("%s", buf);

    va_end(args);
}

// Singleton that may be called from multiple threads
class ResourceManager
{
public:

    struct client_info_t
    {
        std::string     name;
        uint32_t        refCount;

        client_info_t()
        {
            refCount = 0;
        }

        client_info_t(const std::string& n, uint32_t rc)
                : name(n), refCount(rc)
        {
        }
    };

    ResourceManager() : mNextClientNo(0) {}

    uint32_t registerClient(const std::string& name)
    {
        uint32_t id;

        log("registerClient: %s\n", name.c_str());

        mMutex.lock();

        id = mNextClientNo++;

        mClients[id] = client_info_t(name, 0);

        retainClient(id);

        mMutex.unlock();

        return id;
    }
    
    void unregisterClient(uint32_t id)
    {
        log("unregisterClient: %u\n", id);

        mClients.erase(id);
    }

    void retainClient(uint32_t id)
    {
        log("retainClient: %u\n", id);

        mMutex.lock();

        mClients[id].refCount++;

        mMutex.unlock();
    }
    
    void releaseClient(uint32_t id)
    {
        mMutex.lock();

        uint32_t rc = mClients[id].refCount--;

        if (rc == 0)
        {
            unregisterClient(id);
        }

        mMutex.unlock();

        log("releaseClient: %u refs=%u\n", id, mClients[id].refCount);
    }

    typedef std::map<uint32_t, client_info_t>   client_dict_t;

private:

    uint32_t                mNextClientNo;
    client_dict_t           mClients;
    boost::recursive_mutex  mMutex;
};


// Flag to tell threads to quit
bool gRunning;

// Singleton
ResourceManager     gResourceManager;

void randomDelay()
{
    boost::posix_time::milliseconds delayTime(random() % kMaxSleepTime_ms);
    boost::this_thread::sleep(delayTime);
}

// Exercises the resource manager
void clientThread()
{
    unsigned        localClientNo = 0;

    while (gRunning)
    {
        // Idle for a short time
        boost::posix_time::milliseconds delayTime1(50);
        boost::this_thread::sleep(delayTime1);

        // Create a dummy name
        long                threadId = (long)pthread_self();
        std::stringstream   ss;

        ss << "Client " <<  threadId << "." << localClientNo++;

        std::string         name(ss.str());

        // Exercise singleton

        uint32_t id = gResourceManager.registerClient(name);

        randomDelay();

        gResourceManager.retainClient(id);

        randomDelay();

        gResourceManager.releaseClient(id);

        randomDelay();

        gResourceManager.releaseClient(id);
    }
}

int main(int argc, char* argv[])
{
    // Start threads

    gRunning = true;

    boost::thread t1(clientThread);
    boost::thread t2(clientThread);
    boost::thread t3(clientThread);
    boost::thread t4(clientThread);

    // Let them run for a while

    boost::posix_time::milliseconds workTime(5000);
    boost::this_thread::sleep(workTime);

    // Stop gracefully and wait

    gRunning = false;
    t1.join();
    t2.join();

    return 0;
}
