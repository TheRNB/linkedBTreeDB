#ifndef _DATABASE_
#define _DATABASE_

#include "tree.h"
#include "databaseUtils.cpp"

enum Type {STRING=0, INTEGER, DATE};

class database{
public:
	database(int, int, Type*, int*); //int newName, int sz, Type* newTypes, int* columnNames
	void insert(int*); //int* newValues
	void deleteChunk(Comparisson, int, int);//Comparisson queryType, int firstOperand, int secondOperand
	void updateChunk(Comparisson, int, int, int*);//Comparisson queryType, int firstOperand, int secondOperand, int* data
	std::vector<Node*> select(Comparisson, int, int);
	void printSelectChunk(Comparisson, int, int, int*, int); //..., int* columnList, int listSize

	int name;
	int columnCount;
	Type* columnTypes;
	BTree** columnTrees;
	minHeap<int> minAvialableIndex;
};

#endif
