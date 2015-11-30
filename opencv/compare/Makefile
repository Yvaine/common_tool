CC=g++ 
CFLAGS=-O3
CFLAGS+=-DUSE_OPENCV -mfpu=neon
INC= -I/usr/local/include 

LDFLAGS=-L/usr/local/lib -lopencv_core -lopencv_features2d -lopencv_flann\
		-lopencv_imgproc -lopencv_highgui \
		-lopencv_legacy -lopencv_nonfree -lrt -lpthread

TARGET=compare_opencv

all:$(TARGET)

$(TARGET):compare.o
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LDFLAGS)

compare.o:compare.cpp
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -fr $(TARGET)
	rm -fr *.o
	rm -fr *.~
