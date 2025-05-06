CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = hw2_2.cpp \
       ../Labeled_GPS.cpp \
       ../GPS.cpp \
       ../JvTime.cpp \
       ../Timed_Location.cpp \
       ../Traceable_Person.cpp \
       ../Locatable_Thing.cpp \
       ../Core.cpp \
       ../Thing.cpp \
       ../Personal_Timed_GPS_Record.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = hw2_2

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o
