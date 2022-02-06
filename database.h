#include "tree.h"

enum Type {STRING=0, INTEGER, DATE};

class database{
public:
	database(int sz, Type* newTypes, int* columnNames) {
		columnCount = sz;
		columnTypes = newTypes;
		columnTrees = new BTree*[sz];
		for (int i = 0; i < sz; ++i) {
			columnTrees[i] = new BTree(columnNames[i]);
		}
	}
private:
	int columnCount;
	Type* columnTypes;
	BTree** columnTrees;
};