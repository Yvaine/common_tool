
#INCLUDE_PATH+=/usr/local/local/include
#LIB_PATH+=/usr/local/lib

BOOST_LIBS=-lboost_thread-mt -lboost_system
LDFLAGS+=$(BOOST_LIBS)

TARGETS=duel refcount timedlock trylock reclock deadlock sharedlock
OBJS=$(TARGETS:%=%.o)

all:		$(TARGETS)

# Duelling threads example

duel:		duel.cpp

# Bad Reference Counting example

refcount: 	refcount.cpp

# Timed mutexes

timedlock:	timedlock.cpp

# Queueing example

trylock:	trylock.cpp

# Recursive lock example

reclock:	reclock.cpp

# Deadlock example

deadlock:	deadlock.cpp

# Shared Read/Write example

sharedlock:	sharedlock.cpp common.cpp

#

clean:
		rm -f $(TARGETS) $(OBJS)
