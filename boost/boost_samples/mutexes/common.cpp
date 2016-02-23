/*
  common

  Provides logging facilities to aid in debugging and tracing.

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

#include "common.hpp"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <pthread.h>

#define UDP_LOG_PORT        5252
#define TCP_LOG_PORT        5252

static void logToUDP(const char* msg);
static void logToTCP(const char* msg);

void log(LogDestination dest, const char* format, ...)
{
    va_list             args;
    char                buf[512];
    struct timeval      sysTime;
    double              sysTimeMillis;
    int                 offset;

    va_start(args, format);

    gettimeofday(&sysTime, NULL);
    sysTimeMillis = sysTime.tv_sec + sysTime.tv_usec/1e6;

    offset = snprintf(buf, sizeof(buf), "%08lx %6.5lf ",
                      (unsigned long)pthread_self(),
                      sysTimeMillis);

    if (offset && offset < (int)sizeof(buf))
        vsnprintf(buf+offset, sizeof(buf)-offset, format, args);
    else
        fprintf(stderr, "log fail: offset=%d\n", offset);

    switch (dest)
    {
        case kLogStdout:
            printf("%s", buf);
            fflush(stdout);
            break;
        case kLogUDP:
            logToUDP(buf);
            break;
        case kLogTCP:
            logToTCP(buf);
            break;
    }

    va_end(args);
}

void logToUDP(const char* msg)
{
    static int          udpSocket = 0;
    int                 sockError = 0;

    if (udpSocket == 0)
    {
        udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (udpSocket < 0)
        {
            fprintf(stderr, "Failed to upen UDP socket: %d: %s\n",
                    errno, strerror(errno));
            exit(-1);
        }

        struct sockaddr_in sockname = { 0 };
        sockname.sin_len = sizeof(struct sockaddr_in);
        sockname.sin_family = AF_INET;
        sockname.sin_port = htons(UDP_LOG_PORT);
        sockname.sin_addr.s_addr = inet_addr("127.0.0.1");

        sockError = connect(udpSocket, (sockaddr*)&sockname, sizeof(sockname));
        if (sockError < 0)
        {
            fprintf(stderr, "Failed to connect to UDP socket: %d: %s\n",
                    errno, strerror(errno));
            exit(-1);
        }
    }

    sockError = send(udpSocket, msg, strlen(msg), 0);
    if (sockError < 0)
    {
        fprintf(stderr, "Failed sending log entry: %d: %s\n",
                errno, strerror(errno));
        exit(-1);
    }
}

void logToTCP(const char* msg)
{
    static int          tcpSocket = 0;
    int                 sockError = 0;

    if (tcpSocket == 0)
    {
        tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (tcpSocket < 0)
        {
            fprintf(stderr, "Failed to open TCP socket: %d: %s\n",
                    errno, strerror(errno));
            exit(-1);
        }

        struct sockaddr_in sockname = { 0 };
        sockname.sin_len = sizeof(struct sockaddr_in);
        sockname.sin_family = AF_INET;
        sockname.sin_port = htons(TCP_LOG_PORT);
        sockname.sin_addr.s_addr = inet_addr("127.0.0.1");

        sockError = connect(tcpSocket, (sockaddr*)&sockname, sizeof(sockname));
        if (sockError < 0)
        {
            fprintf(stderr, "Failed to connect to TCP socket: %d: %s\n",
                    errno, strerror(errno));
            exit(-1);
        }
    }

    sockError = send(tcpSocket, msg, strlen(msg), 0);
    if (sockError < 0)
    {
        fprintf(stderr, "Failed sending log entry: %d: %s\n",
                errno, strerror(errno));
        exit(-1);
    }
}
