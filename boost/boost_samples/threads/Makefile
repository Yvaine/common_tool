
#INCLUDE_PATH+=/opt/local/include
#LIB_PATH+=/opt/local/lib

//BOOST_LIBS=-lboost_thread-mt -lboost_system
BOOST_LIBS=-lboost_thread -lboost_system 
LDFLAGS+=$(BOOST_LIBS)

TARGETS=simple funcarg functor method objthread
OBJS=$(TARGETS:%=%.o)

all:			$(TARGETS)

# Simple thread function example

simple:			simple.cpp

# Thread function with arguments

funcarg:		funcarg.cpp

# Functor

functor:		functor.cpp

# Threaded method

method:			method.cpp

# Object contains thread

objthread:		objthread.cpp

#

clean:
			rm -f $(TARGETS) $(OBJS)
