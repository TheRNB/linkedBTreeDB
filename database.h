#include "tree.h"
#include "databaseUtils.cpp"

enum Type {STRING=0, INTEGER, DATE};

class database{
public:
	database(int newName, int sz, Type* newTypes, int* columnNames);
	void insert(int* newValues);
private:
	int name;
	int columnCount;
	Type* columnTypes;
	BTree** columnTrees;
	minHeap<int> minAvialableIndex;
};