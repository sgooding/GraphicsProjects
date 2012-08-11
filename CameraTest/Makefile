
INCDIR=/OpenCV/install/include
CXX=g++
CFLAGS=-I$(INCDIR) -I. -I/OpenCV/install/include/opencv 

LIBS=-L/OpenCV/install/lib  -L.

TARGET=CameraTest
SRCS=CameraTest.cpp DetectedObject.cpp
OBJ=$(subst .cpp,.o,$(SRCS))
LIBS+=-lopencv_core240 -lopencv_features2d240 -lopencv_highgui240 -lopencv_imgproc240 

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CXX)  -c -o $@ $< $(CFLAGS)

clean: 
	@rm *.exe *.o



