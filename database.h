#ifndef _DATABASE_
#define _DATABASE_

#include "tree.h"
#include "databaseUtils.cpp"

enum Type {STRING=0, INTEGER, DATE};

class database{
public:
	database(long long, int, Type*, long long*); //int newName, int sz, Type* newTypes, int* columnNames
	void insert(vector<std::string>&); //int* newValues
	void deleteChunk(Comparisson, std::string, std::string);//Comparisson queryType, int firstOperand, int secondOperand
	void updateChunk(Comparisson, std::string, std::string, vector<std::string>&);//Comparisson queryType, int firstOperand, int secondOperand, int* data
	std::vector<Node*> select(Comparisson, long long, long long);
	void printSelectChunk(Comparisson, std::string, std::string, vector<std::string>&); //..., int* columnList, int listSize
	long long getName();
private:
	long long name;
	int columnCount;
	Type* columnTypes;
	BTree** columnTrees;
	minHeap<long long> minAvialableIndex;
};

#endif
