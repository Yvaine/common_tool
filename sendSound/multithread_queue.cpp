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
int flag;

void* en_queue(void *args)
{
	char utter[6400];
	for(int i = 0; i< 10; i++)
	{
		sprintf(utter, " in queue i am %d\n ", i);
		string utter_s = utter;
  
		speech_queue.push(utter_s);
        //pthread_mutex_lock(&lock);
		flag++;
		//pthread_mutex_unlock(&lock);
	}
	return ((void*)0);
}

void* out_queue(void *args)
{
	while(1){
		if(!speech_queue.empty() )
		{
			printf("%s", speech_queue.front().c_str());
			// send to socket
			speech_queue.pop();
		}
		else{
			// no enter to the queue
			if(flag == 0){
				printf("not enter queue\n");
				sleep(1);
				continue;
			}
			else{
				// fetch out empty
				printf("fetch all of queue\n");
				sleep(1);
				continue;
				//break;
			}
		}
	}
	return ((void*)0);
}

int main()
{
	flag = 0;
	pthread_t thread_id1;
	pthread_t thread_id2;
	int err;
	void *tret;
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
