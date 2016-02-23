/*
  Thread Functor

  * Part of "Threading with Boost - Part I: Creating Threads", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

#include <iostream>
#include <boost/thread.hpp>

/*
  NOTE: The functor is copied by-value (_not_ by-reference) when passed to
  the thread constructor!  So instances of this class must be safe to copy,
  and you should take care of memory management issues in the copy
  constructor.
 */
class Worker
{
public:
    
    Worker(unsigned N, float guess, unsigned iter) 
            : m_Number(N),
              m_Guess(guess),
              m_Iterations(iter)
    {
    }

    void operator()()
    {
        std::cout << "Worker: calculating sqrt(" << m_Number
                  << "), itertations = " << m_Iterations << std::endl;

        // Use Newton's Method
        float   x;
        float   x_last = m_Guess;

        for (unsigned i=0; i < m_Iterations; i++)
        {
            x = x_last - (x_last*x_last-m_Number)/(2*x_last);
            x_last = x;

            std::cout << "Iter " << i << " = " << x << std::endl;
        }

        std::cout << "Worker: Answer = " << x << std::endl;
    }

private:

    unsigned    m_Number;
    float       m_Guess;
    unsigned    m_Iterations;
};

int main(int argc, char* argv[])
{
    std::cout << "main: startup" << std::endl;

    Worker w(612, 10, 5);
    boost::thread workerThread(w);

    std::cout << "main: waiting for thread" << std::endl;

    workerThread.join();

    std::cout << "main: done" << std::endl;

    return 0;
}
