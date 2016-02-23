/*
  common

  Provides logging facilities to aid in debugging and tracing.

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

#ifndef COMMON_H_INC
#define COMMON_H_INC

enum LogDestination
{
    kLogStdout,
    kLogUDP,
    kLogTCP
};

void log(LogDestination dest, const char* format, ...);

#endif /* COMMON_H_INC */
