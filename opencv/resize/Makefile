CC=g++ 
CFLAGS=-O0 -g -mfpu=neon
CFLAGS+=-DUSE_OPENCV -mfpu=neon
INC= -I/usr/local/include 

LDFLAGS=-L/usr/local/lib -lopencv_core -lopencv_features2d -lopencv_flann\
		-lopencv_imgproc -lopencv_highgui \
		-lopencv_legacy -lopencv_nonfree -lrt -lpthread

TARGET=resize

all:$(TARGET)

$(TARGET):resize.o
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LDFLAGS)

resize.o:resize1.cpp
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -fr $(TARGET)
	rm -fr *.o
	rm -fr *.~
