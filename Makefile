CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
CPPFLAGS ?= -Inamespaces
SFML_LIBS ?= -lsfml-graphics -lsfml-window -lsfml-system

TARGET := forge2d
SOURCES := src/main.cpp
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(SFML_LIBS)

src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(OBJECTS) $(TARGET) $(TARGET).exe
