/*
  Producer/Consumer Pattern with Condition Variables

  One of the most common patterns for cooperating threads is for one to produce
  data and the other to asynchronously consume the data.  When the time required
  to produce or consume the data is indeterminate, this pattern allows the two
  threads to efficiently and safely work together.  This example uses a queue to
  decouple the data interface (protected of course by a mutex).

  * Part of "Threading with Boost - Part IV: Condition Variables", published at:

      http://antonym.org/boost

  Copyright (c) 2012 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
*/

#include <iostream>
#include <queue>

#include <boost/thread.hpp>

class Worker
{
	public:

		Worker(unsigned count)
		: m_dataCount(count), m_dataReady(false) {}

		// Thread-safe data

		void addToQueue(unsigned num);
		unsigned readFromQueue();

		//

		void run();

		// Cooperating threads

		void produce();
		void consume();

	private:

		unsigned					m_dataCount;
		bool						m_dataReady;
		boost::mutex				m_mutex;
		boost::condition_variable	m_cond;

		std::queue<unsigned>		m_queue;
		boost::mutex				m_dataMutex;
};

void Worker::addToQueue(unsigned num)
{
	boost::lock_guard<boost::mutex> lock(m_dataMutex);
	m_queue.push(num);
}

unsigned Worker::readFromQueue()
{
	boost::lock_guard<boost::mutex> lock(m_dataMutex);
	unsigned data = m_queue.front();
	m_queue.pop();
	return data;
}

/*
	Spawn the two cooperating threads and then block,
	waiting for them both to finish.
 */
void Worker::run()
{
	boost::thread producerThread(&Worker::produce, this);
	boost::thread consumerThread(&Worker::consume, this);

	producerThread.join();
	consumerThread.join();
}

/*
	Thread to produce data
 */
void Worker::produce()
{
	for (unsigned i = 0; i < m_dataCount; i++)
	{
		boost::unique_lock<boost::mutex> lock(m_mutex);

		// Wait for consumer to be ready

		while (m_dataReady)
	    {
			m_cond.wait(lock);
		}

		// Now produce!

		std::cout << "producer >>> " << i << std::endl;
		{
			addToQueue(i);
			m_dataReady = true;
		}

        boost::chrono::milliseconds sleepDuration(100);
        boost::this_thread::sleep_for(sleepDuration);

		m_cond.notify_one();
	}
}

/*
	Thread to consume data
 */
void Worker::consume()
{
	for (unsigned i = 0; i < m_dataCount; i++)
	{
        boost::chrono::milliseconds sleepDuration(50);
        boost::this_thread::sleep_for(sleepDuration);

		// Let the producer know we're ready
		m_cond.notify_one();

		// Wait for data
	 	boost::unique_lock<boost::mutex> lock(m_mutex);
	    while (!m_dataReady)
	    {
	        m_cond.wait(lock);
	    }

	    m_dataReady = false;

		unsigned data = readFromQueue();
		std::cout << "consumer <<< " << data << std::endl;
	}
}

int main()
{
	unsigned N = 50;

	Worker w(N);

	w.run();

	return 0;
}
