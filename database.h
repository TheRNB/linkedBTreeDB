#include "tree.h"
#include "databaseUtils.cpp"

enum Type {STRING=0, INTEGER, DATE};

class database{
public:
	database(int newName, int sz, Type* newTypes, int* columnNames);
	void insert(int* newValues);
	void deleteChunk(Comparisson queryType, int firstOperand, int secondOperand);
	void updateChunk(Comparisson queryType, int firstOperand, int secondOperand, int* newData);
	std::vector<Node*> select(Comparisson queryType, int firstOperand, int secondOperand);
	void printSelectChunk(Comparisson queryType, int firstOperand, int secondOperand, int* columnList, int listSize);
private:
	int name;
	int columnCount;
	Type* columnTypes;
	BTree** columnTrees;
	minHeap<int> minAvialableIndex;
};