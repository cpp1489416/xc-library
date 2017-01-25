
BUILD_FLAG = -Wall -std=c++11 -Iinclude
CC = g++

SOURCE_PATH = ../../../Core
INCLUDE_PATH = ../../../Core

vpath %.cpp $(SOURCE_PATH)
vpath %.h $(INCLUDE_PATH)

SOURCES_PATH := $(wildcard *.cpp $(SOURCE_PATH)/*.cpp)
SOURCES_NO_PATH := $(notdir $(SOURCES_PATH))
OBJECTS := $(SOURCES_NO_PATH:%.cpp=%.o)
DOBJECTS := $(SOURCES_NO_PATH:%.cpp=%.d)

# $(warning vpath = $(VPATH), SOURCE_PATH = $(SOURCES_PATH), SOURCE_NO_PATH = $(SOURCES_NO_PATH), OBJECTS = $(OBJECTS))

result: $(OBJECTS)
	g++ -o $@ $(BUILD_FLAG) $<

%.d : %.cpp
	a="$@"; \
	echo $a
	rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.; \
	touch $@; \
	echo -n $@  > $@; \
	echo -n " " >> $@; \
	cat $@. >> $@; \
	echo -n "g++ -c $(BUILD_FLAG) $< > " >> $@; \
	echo ${a/.d/.o}; \
	echo $a

sinclude $(DOBJECTS)

.PHONY: clean
clean:
	rm $(OBJECTS); \
	rm $(DOBJECTS)