CC = g++
CFLAGS = -I.
TARGET = main
LIBS = -lEposCmd

all: $(TARGET)

$(TARGET): $(TARGET).cpp motor.cpp leg.cpp
	$(CC) -o $(TARGET) $(TARGET).cpp motor.cpp leg.cpp $(CFLAGS) $(LIBS)

clean:
	$(RM) $(TARGET)
