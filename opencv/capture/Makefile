CC=g++ 
CFLAGS=-O3
CFLAGS+=-DUSE_OPENCV
INC= -I/usr/local/include 

LDFLAGS=-L/usr/local/lib -lopencv_core -lopencv_features2d -lopencv_flann\
		-lopencv_imgproc -lopencv_highgui \
		-lopencv_legacy -lopencv_nonfree -lrt -lpthread

TARGET=capture

all:$(TARGET)

$(TARGET):capture.o
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LDFLAGS)

capture.o:capture.cpp
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -fr $(TARGET)
	rm -fr *.o
	rm -fr *.~
