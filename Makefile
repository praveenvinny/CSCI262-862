CC = g++
TARGET = A3
CFLAGS = -Wall -Wextra
DEBUG = -g

.PHONY: default all clean

default: $(TARGET)
all: default

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cpp=.o)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(DEBUG) -c $<

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)

