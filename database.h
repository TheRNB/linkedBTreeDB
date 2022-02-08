#ifndef _DATABASE_
#define _DATABASE_

#include "tree.h"
#include "utils/databaseUtils.cpp"

enum Type {STRING=0, INTEGER, DATE};
enum multiCondition {NONE=0, AND, OR};

class database{
public:
	database(std::string, int, Type*, std::string*); //int newName, int sz, Type* newTypes, int* columnNames
	void insert(vector<std::string>&); //int* newValues
	void deleteChunk(Comparisson, std::string, std::string, multiCondition, Comparisson, std::string, std::string);//Comparisson queryType, int firstOperand, int secondOperand
	void updateChunk(Comparisson, std::string, std::string, vector<std::string>&, multiCondition, Comparisson, std::string, std::string);//Comparisson queryType, int firstOperand, int secondOperand, int* data
	std::vector<Node*> select(Comparisson, std::string, long long, multiCondition, Comparisson, std::string, long long);
	void printSelectChunk(Comparisson, std::string, std::string, vector<std::string>&, multiCondition, Comparisson, std::string, std::string); //..., int* columnList, int listSize
	std::string getName();
	void sortVector(std::vector<Node*>&);
private:
	std::string name;
	int columnCount;
	Type* columnTypes;
	BTree** columnTrees;
	minHeap<long long> minAvialableIndex;
	void mergeSort(int, int, std::vector<Node*>&, std::vector<Node*>&);
};

#endif
