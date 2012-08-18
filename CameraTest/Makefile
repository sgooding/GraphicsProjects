
DEBUG=-g
INCDIR=/OpenCV/install/include
CXX=g++
CFLAGS=-I$(INCDIR) -I. `pkg-config --cflags opencv` $(DEBUG)

LIBS=`pkg-config --libs opencv`

TARGET=CameraTest
SRCS=CameraTest.cpp DetectedObject.cpp
OBJ=$(subst .cpp,.o,$(SRCS))

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CXX)  -c -o $@ $< $(CFLAGS)

clean: 
	@rm *.exe *.o



