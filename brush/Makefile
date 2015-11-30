CC=g++ 
CFLAGS=-O0 -g 
CFLAGS+=-DUSE_OPENCV -mfpu=neon
INC= -I/usr/local/include 

LDFLAGS=-L/usr/local/lib -lopencv_core -lopencv_features2d -lopencv_flann\
		-lopencv_imgproc -lopencv_highgui \
		-lopencv_legacy -lopencv_nonfree -lrt -lpthread

TARGET=brush

all:$(TARGET)

$(TARGET):brush.o
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LDFLAGS)

brush.o:brush.cpp
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -fr $(TARGET)
	rm -fr *.o
	rm -fr *.~
