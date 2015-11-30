/*************************************************************************
	> File Name: udp_client2.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Thu Nov 12 11:12:47 2015
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <string>
#include <unistd.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define SPEECHSIZE 640
#define RECOGSIZE 640
#define NUM 5
int main(int argc, char **argv)
{
	int client_sockfd;
	int sendlen, recvlen;
	struct sockaddr_in remote_addr;// server network struct
	int sin_size;
	char speechbuf[SPEECHSIZE];
	char recogbuf[RECOGSIZE];
	memset(&remote_addr, 0, sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr("10.0.1.30");
	remote_addr.sin_port = htons(8888);
	socklen_t addrlen = sizeof(struct sockaddr);
	if((client_sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket failed");
		return -1;
	}
	for(int i = 0; i < NUM; i++)
	{
		sprintf(speechbuf, "SPEECH %04d", i);
		//printf("sending : '%s' \n", speechbuf);

		if((sendlen = sendto(client_sockfd, speechbuf, strlen(speechbuf), 0, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)))< 0)
		{
			perror("sendto faild\n");
			return -1;
		}
		if(recvlen = recvfrom(client_sockfd, recogbuf, RECOGSIZE, 0, (struct sockaddr *)&remote_addr, &addrlen) > 0)
		{
			printf("recv %s from %s \n", recogbuf, inet_ntoa(remote_addr.sin_addr));
		}
	}
	close(client_sockfd);
	return 0;
}
