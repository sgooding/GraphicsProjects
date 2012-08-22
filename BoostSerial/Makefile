
INCDIR=
CXX=g++
CFLAGS=

LIBS=-lboost_system -lboost_thread -lpthread

TARGET=BoostSerial
SRCS=BoostSerial.cpp
OBJ=$(subst .cpp,.o,$(SRCS))

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CXX)  -c -o $@ $< $(CFLAGS)

clean: 
	@rm *.exe *.o



