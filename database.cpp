#include "hashUtils.h"
#include <vector>
#include <iostream>

database::database(int newName, int sz, Type* newTypes, int* columnNames) {
	name = newName;
	columnCount = sz+1;
	columnTypes = new Type[columnCount];
	columnTypes[0] = INTEGER;
	for (int i = 1; i < columnCount; ++i) 
		columnTypes[i] = newTypes[i-1];
	columnTrees = new BTree*[sz+1];
	columnTrees[0] = new BTree(-1); //ID Column
	for (int i = 1; i <= sz; ++i) {
		columnTrees[i] = new BTree(columnNames[i-1]);
	}
	minAvialableIndex.createEmptyTree(1000);
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

void database::deleteChunk(Comparisson queryType, int firstOperand, int secondOperand) {
	for (int i = 0; i < columnCount; ++i) {
		cerr << columnTrees[i]->getName() << " " << firstOperand << endl;
		if (columnTrees[i]->getName() == firstOperand) {
			std::vector<Node*> deleteQueue = columnTrees[i]->search(secondOperand, queryType);
			cerr << "size " << deleteQueue.size() << endl;
			while(deleteQueue.empty() != true) {
				Node* deleting = deleteQueue.back();
				deleteQueue.pop_back();
				for (int j = 0; j < columnCount; ++j) {
					if (columnTrees[i+j]->getName() == -1) {
						minAvialableIndex.add(deleting->data);
					}
					columnTrees[i+j]->deleteNode(deleting, deleting->self);
					deleting = deleting->nextField;
				}
			}
			return;
		}
	}
	return;
}

void database::updateChunk(Comparisson queryType, int firstOperand, int secondOperand, int* newData) {
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperand) {
			std::vector<Node*> deleteQueue = columnTrees[i]->search(secondOperand, queryType);
			for (int j = 0; j < deleteQueue.size(); ++j) {
				Node* tmp = deleteQueue[j];
				for (int k = i; k < columnCount; ++k) {
					tmp = tmp->nextField;
				}
				Node* tmp1 = tmp->nextField;
				Node* tmp2 = tmp1->nextField;
				for (int k = 0; k < columnCount-1; ++k) {
					columnTrees[k+1]->deleteNode(tmp1, tmp1->self);
					tmp->nextField = columnTrees[k+1]->insert(newData[k]);
					tmp = tmp->nextField;
					tmp1 = tmp2;
					tmp2 = tmp2->nextField;
				}
				tmp->nextField = deleteQueue[j];
			}
		}
	}
	return;
}

std::vector<Node*> database::select(Comparisson queryType, int firstOperand, int secondOperand) {
	std::vector<Node*> searchQueue;
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperand) {
			searchQueue = columnTrees[i]->search(secondOperand, queryType);
			for (int j = 0; j < searchQueue.size(); ++j) {
				for (int k = i; k < columnCount; ++k) {
					searchQueue[j] = searchQueue[j]->nextField;
				}
			}
			break;
		}
	}
	return searchQueue;
}

void database::printSelectChunk(Comparisson queryType, int firstOperand, int secondOperand, int* columnList, int listSize) {
	std::vector<Node*> printing = select(queryType, firstOperand, secondOperand);
	for (int i = 0; i < printing.size(); ++i) {
		for (int j = 0; j < columnCount; ++j) {
			for (int k = 0; k < listSize; ++k) {
				if (columnTrees[j]->getName() == columnList[k]) {
					std::cout << deHash(printing[i]->data, columnTypes[j]) << " ";
				}
			}
			if (listSize == 0) {
				std::cout << printing[i]->data << " and " << columnTypes[j] << " ";
			}
			printing[i] = printing[i]->nextField;
		}
		std::cout << "\n";
	}
	return;
}
