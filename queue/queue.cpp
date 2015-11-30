/*************************************************************************
	> File Name: queue.c
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Thu Nov 12 18:20:08 2015
 ************************************************************************/

#include<stdio.h>
#include <queue>
#include <string>

using namespace std;

typedef struct bufferSpeech
{
  char a[6400];
}bufferspeech;


int main()
{
#if 0
	bufferspeech utter[10];
	
	queue<bufferspeech>speech_queue;
	for(int i = 0; i< 10; i++)
	{
		sprintf(utter[i].a, " i am %d ", i);

		speech_queue.push(utter[i]);
	}
	printf("size  %d", speech_queue.size());

	while(!speech_queue.empty())
	{
		printf("%s", speech_queue.front();
	}
#endif
	queue<string>speech_queue;
	char utter[6400];
	for(int i = 0; i< 10; i++)
	{
		sprintf(utter, " i am %d\n ", i);
		string utter_s = utter;

		speech_queue.push(utter_s);
	}
	printf("size  %d \n", speech_queue.size());

	while(!speech_queue.empty())
	{
		printf("%s", speech_queue.front().c_str());
		speech_queue.pop();
	}
	return 0;


}
