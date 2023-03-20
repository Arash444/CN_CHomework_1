CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)

EXECUTABLE_FILE = server.out
OBJECTS = \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/cmdHandler.o \
	$(BUILD_DIR)/jsonReader.o \
	$(BUILD_DIR)/room.o \
	$(BUILD_DIR)/user.o \
	$(BUILD_DIR)/Date.o
	
userSensitivityList = \
	$(SRC_DIR)/user.cpp

jsonReaderSensitivityList = \
	$(SRC_DIR)/jsonReader.cpp \
	$(INCLUDE_DIR)/jsonReader.hpp

cmdHandlerSensitivityList = \
	$(SRC_DIR)/cmdHandler.cpp

serverSensitivityList = \
	$(SRC_DIR)/server.cpp \
	$(INCLUDE_DIR)/cmdHandler.hpp 

mainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/server.hpp \

ConfigReaderSensitivityList = \
	$(SRC_DIR)/jsonReader.cpp \
	$(INCLUDE_DIR)/user.hpp

dateSensitivityList = \
	$(SRC_DIR)/Date.cpp \
	$(INCLUDE_DIR)/Date.hpp

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/room.o: $(roomSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/room.cpp -o $(BUILD_DIR)/room.o

$(BUILD_DIR)/main.o: $(mainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/server.o: $(serverSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/cmdHandler.o: $(cmdHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cmdHandler.cpp -o $(BUILD_DIR)/cmdHandler.o

$(BUILD_DIR)/jsonReader.o: $(ConfigReaderSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jsonReader.cpp -o $(BUILD_DIR)/jsonReader.o

$(BUILD_DIR)/user.o: $(UserSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/Date.o: $(dateSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Date.cpp -o $(BUILD_DIR)/Date.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out