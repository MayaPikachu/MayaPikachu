SRC := ./trab_4.cpp
TARGET := ./trab_4

all:
	g++ $(SRC) -o $(TARGET) -ggdb

release:
	g++ $(SRC) -o $(TARGET)

clean:
	touch $(TARGET)
	rm $(TARGET)
