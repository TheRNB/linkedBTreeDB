#include "database.h"

database::database(int newName, int sz, Type* newTypes, int* columnNames) {
	name = newName;
	columnCount = sz+1;
	columnTypes = newTypes;
	columnTrees = new BTree*[sz+1];
	columnTrees[0] = new BTree(0); //ID Column
	for (int i = 1; i <= sz; ++i) {
		columnTrees[i] = new BTree(columnNames[i]);
	}
}

void database::insert(int* newValues) {
	int newId = columnTrees[0]->size();
	if (minAvialableIndex.isEmpty() == false) {
		newId = minAvialableIndex.removeRoot();
	}
	Node** newLinkedList = new Node* [columnCount];
	newLinkedList[0] = columnTrees[0]->insert(newId);
	for (int i = 1; i < columnCount; ++i) {
		newLinkedList[i] = columnTrees[i]->insert(newValues[i-1]);
	}
	for(int i = 0; i < columnCount; ++i) {
		newLinkedList[i]->nextField = newLinkedList[(i+1)%columnCount];
	}
	return;
}

