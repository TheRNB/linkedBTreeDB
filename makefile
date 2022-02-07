# -*- MakeFile -*-

target: dependencies
	action

all: driverProgram

driverProgram: driverProgram.o database.o hashUtils.o tree.o node.o hashUtils.o
	g++ driverProgram.o database.o tree.o node.o hashUtils.o -o driverProgram

hashUtils.o: hashUtils.cpp
	g++ -c hashUtils.cpp

driverProgram.o: driverProgram.cpp database.h hashUtils.h
	g++ -c driverProgram.cpp

database.o: hashUtils.h database.h database.cpp databaseUtils.cpp tree.o
	g++ -c database.cpp

tree.o: tree.h tree.cpp
	g++ -c tree.cpp

node.o: node.h node.cpp
	g++ -c node.cpp


clean:
	rm -f *.o driverProgram

