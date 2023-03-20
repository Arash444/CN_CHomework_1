CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)

EXECUTABLE_FILE = client.out
OBJECTS = \
	$(BUILD_DIR)/client.o \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/jsonReader.o

all: $(BUILD_DIR) $(EXECUTABLE_FILE)


$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/client.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o


$(BUILD_DIR)/client.o: $(SRC_DIR)/client.cpp $(INCLUDE_DIR)/client.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/client.cpp -o $(BUILD_DIR)/client.o

$(BUILD_DIR)/jsonReader.o: $(SRC_DIR)/jsonReader.cpp $(INCLUDE_DIR)/jsonReader.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jsonReader.cpp -o $(BUILD_DIR)/jsonReader.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out