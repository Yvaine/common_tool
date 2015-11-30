/*************************************************************************
	> File Name: queue.c
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Thu Nov 12 18:20:08 2015
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <queue>
#include <string>
#include <string.h>
#include <pthread.h>

using namespace std;

queue<string>speech_queue;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* en_queue(void *args)
{
	char utter[6400];
	for(int i = 0; i< 10; i++)
	{
		sprintf(utter, " in queue i am %d\n ", i);
		string utter_s = utter;
  
        pthread_mutex_lock(&lock);
		speech_queue.push(utter_s);
		pthread_mutex_unlock(&lock);
	}
	return ((void*)0);

}

void* out_queue(void *args)
{
	pthread_mutex_lock(&lock);
	while(!speech_queue.empty() )
	{
		printf("%s", speech_queue.front().c_str());
		speech_queue.pop();
	}
	pthread_mutex_unlock(&lock);
	return ((void*)0);

}

int main()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	int err;
	void *tret;
	char utter[6400];
	sprintf(utter, " in queue 0 am \n " );
	string utter_s = utter;

	pthread_mutex_lock(&lock);
	speech_queue.push(utter_s);
	pthread_mutex_unlock(&lock);
	err = pthread_create(&thread_id1, NULL, &en_queue, NULL);
	if(err != 0)
	{
		printf("pthread_create 1 error : %s \n", strerror(err));
	    return -1;
	}

	err = pthread_create(&thread_id2, NULL, &out_queue, NULL);
	if(err != 0)
	{
		printf("pthread_create 2 error : %s \n", strerror(err));
	    return -1;
	}

	err  = pthread_join(thread_id1, &tret);
	if(err != 0)
	{
		printf("can not join thread 1 : %s \n", strerror(err));
	    exit(-1);
	}
	err = pthread_join(thread_id2, &tret);
	if(err != 0)
	{
		printf("can not join thread 1 : %s \n", strerror(err));
	    exit(-1);
	}
	return 0;
}
