
CXXFLAGS=-std=c++11

# Boost

BOOST_LIBS=-lboost_thread-mt -lboost_system
LDFLAGS=$(BOOST_LIBS)

# condition examples

TARGETS=simple_wait producer_consumer producer_consumer2 many_wait many_consumers
OBJS=$(TARGETS:%=%.o)

all: 			$(TARGETS)

clean:			#
			rm -f $(TARGETS) $(OBJS)
