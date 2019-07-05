CC = clang++  #compile using clang 
# CC = c++      # compile using UNIX compiler 
# CC = icpc     # compile using INTEL  
# CC = g++      # compile using GCC

TARGET = DiffSolve-2D
all: $(TARGET)
$(TARGET): $(TARGET).cpp
	$(CC) -o $(TARGET) $(TARGET).cpp

all: run

run: $(TARGET)
	./$(TARGET)
.PHONY: all run
