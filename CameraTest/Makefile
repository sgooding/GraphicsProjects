
INCDIR=/OpenCV/install/include
CXX=g++
CFLAGS=-I$(INCDIR)

LIBS=-L/OpenCV/install/lib

TARGET=CameraTest
SRCS=CameraTest.cpp
OBJ=$(subst .cpp,.o,$(SRCS))
LIBS+=-lopencv_core240 -lopencv_features2d240 -lopencv_highgui240

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CXX)  -c -o $@ $< $(CFLAGS)

clean: 
	@rm *.exe *.o



