/*
  Bad Reference Counting

  Illustrates a subtle race condition, where two threads releasing a shared
  object may attempt do so simultaneously, and cause a memory leak.

  * Part of "Threading with Boost - Part III: Mutexes", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details

  (This particular sample contains intentional bugs, so you probably
  wouldn't want to copy it as is!)
 */

#include <iostream>

class BadSharedObj
{
public:

    BadSharedObj()
    {
        mRefCount = 1;
    }

    void AddRef()
    {
        // Danger! This is not atomic!

        mRefCount++;
    }

    void Release()
    {
        // Danger! This is not atomic!

        mRefCount--;

        if (mRefCount == 0)
        {
            delete this;
        }
    }

private:

    int mRefCount;
};

int main(int argc, char* argv[])
{
    printf("Intentionally buggy to illustrate how NOT to do reference counting!\n");

    return 0;
}
