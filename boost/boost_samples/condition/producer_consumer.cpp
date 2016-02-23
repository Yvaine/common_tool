/*
  Producer/Consumer Pattern with Condition Variables

  One of the most common patterns for cooperating threads is for one to produce
  data and the other to asynchronously consume the data.  When the time required
  to produce or consume the data is indeterminate, this pattern allows the two
  threads to efficiently and safely work together.  This example uses a queue to
  decouple the data interface (protected of course by a mutex).

  * Part of "Threading with Boost - Part V: Condition Variables", published at:

      http://antonym.org/boost

  Copyright (c) 2012 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
*/

#include <cstdio>
#include <queue>

#include <boost/thread.hpp>

class Worker
{
	public:

		Worker(unsigned count)
		: m_dataCount(count), m_dataPending(0) {}

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
		unsigned					m_dataPending;
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
	assert(m_queue.size() > 0);
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
		// Pretend this is working hard
        boost::chrono::milliseconds sleepDuration(5);
        boost::this_thread::sleep_for(sleepDuration);

        addToQueue(i);

		printf("producer >>> %u\n", i);
		{
			boost::lock_guard<boost::mutex> lock(m_mutex);
			m_dataPending++;
		}
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
	 	boost::unique_lock<boost::mutex> lock(m_mutex);
	    while (m_dataPending > 0)
	    {
	        m_cond.wait(lock);
	    }
	    m_dataPending--;

		unsigned data = readFromQueue();
		printf("consumer <<< %u\n", data);
	}
}

int main()
{
	unsigned N = 100;

	Worker w(N);

	w.run();

	return 0;
}
