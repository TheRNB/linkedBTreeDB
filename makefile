# -*- MakeFile -*-

target: dependencies
	action

all: driverProgram

driverProgram: driverProgram.o database.o tree.o node.o hashUtils.o validators.o
	g++ driverProgram.o database.o tree.o node.o hashUtils.o validators.o -o driverProgram

hashUtils.o: utils/hashUtils.cpp
	g++ -c utils/hashUtils.cpp

driverProgram.o: driverProgram.cpp database.h utils/hashUtils.h
	g++ -c driverProgram.cpp

database.o: utils/hashUtils.h database.h database.cpp utils/databaseUtils.cpp tree.o
	g++ -c database.cpp

tree.o: tree.h tree.cpp
	g++ -c tree.cpp

node.o: node.h node.cpp
	g++ -c node.cpp

validators.o: utils/hashUtils.cpp validators/validators.cpp
	g++ -c validators/validators.cpp -o validators.o

test: test/test-main.o test/catch.o test/hashUtils-test.o test/node-test.o test/tree-test.o
	g++ -std=c++20 test/test-main.o test/catch.o test/hashUtils-test.o test/node-test.o test/tree-test.o -o test/testFile
	test/./testFile

catch.o: test/catch.cpp
	g++ -std=c++20 -c test/catch.cpp -o test/catch.o

test-main.o: test/test-main.cpp
	g++ -std=c++20 -c test/test-main.cpp -o test/test-main.o

hashUtils-test.o: test/hashUtils-test.cpp utils/hashUtils.h
	g++ -std=c++20 -c test/hashUtils-test.cpp -o test/hashUtils-test.o -o test/hashUtils-test.o 

node-test.o: test/node-test.cpp node.h
	g++ -std=c++20 -c test/node-test.cpp -o test/board-test.o -o test/node-test.o

tree-test.o: test/tree-test.o tree.h
	g++ -std=c++20 -c test/tree-test.cpp -o test/tree-test.o -o test/tree-test.o


clean:
	rm -f *.o driverProgram validators/*.o utils/*.o

testClean:
	rm -f test/*.o test/test-main.o test/testFile
