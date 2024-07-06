CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lstdc++
SRC = FileSystem.cpp FileSystemTest.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = filesystem_test

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

test: $(EXEC)
	./$(EXEC)
