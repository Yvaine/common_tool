/*************************************************************************
	> File Name: sendsound.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Fri Nov 13 11:22:02 2015
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <queue>
#include <string>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<iostream>

using namespace std;

#define SPEECHSIZE 6400
#define RECOGSIZE 6400
#define NUM 100
int port = 9001;

queue<string>speech_queue;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int flag;

void* en_queue(void *args)
{
	char utter[SPEECHSIZE];
	for(int i = 0; i< NUM; i++)
	{
		sprintf(utter, " in queue i am %d\n ", i);
		string utter_s = utter;
  
        pthread_mutex_lock(&lock);
		speech_queue.push(utter_s);
		flag = 1;
		pthread_mutex_unlock(&lock);
	}
	return ((void*)0);
}

void* out_queue(void *args)
{
	int client_sockfd;
	int sendlen, recvlen;
	struct sockaddr_in remote_addr;// server network struct
	int sin_size;
	//char speechbuf[SPEECHSIZE];
	char *speechbuf = (char *)malloc(sizeof(char) * SPEECHSIZE);
	char recogbuf[RECOGSIZE];
	memset(&remote_addr, 0, sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr("10.0.1.30");
	remote_addr.sin_port = htons(port);
	socklen_t addrlen = sizeof(struct sockaddr);
	if((client_sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket failed");
		return ((void *)-1);
	}
	while(1){
		if(!speech_queue.empty() )
		{
			printf("send to server is %s", speech_queue.front().c_str());
			pthread_mutex_lock(&lock);
			speechbuf = (char *)speech_queue.front().data(); 
			if((sendlen = sendto(client_sockfd, speechbuf, SPEECHSIZE, 0, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)))< 0)
			{
				perror("sendto faild\n");
				break;
			}
			// send to socket
			speech_queue.pop();
			pthread_mutex_unlock(&lock);
		}
		else{
			// no enter to the queue
			continue;
		}
	}
	close(client_sockfd);
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

