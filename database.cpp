#include "database.h"
#include <vector>
#include <algorithm>
#include <iostream>


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

void database::deleteChunk(Comparisson queryType, int firstOperand, int secondOperand) {
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperand) {
			std::vector<Node*> deleteQueue = columnTrees[i]->search(secondOperand, queryType);
			while(deleteQueue.empty() != true) {
				Node* deleting = deleteQueue.back();
				deleteQueue.pop_back();
				for (int j = 0; j < columnCount; ++j) {
					if (columnTrees[i+j]->getName() == 0) {
						minAvialableIndex.add(deleting->data);
					}
					columnTrees[i+j]->deleteSingleNode(deleting, deleting->self);
					deleting = deleting->nextField;
				}
			}
		}
	}
	return;
}

void database::updateChunk(Comparisson queryType, int firstOperand, int secondOperand, int* newData) {
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperand) {
			std::vector<Node*> deleteQueue = columnTrees[i]->search(secondOperand, queryType);
			while(deleteQueue.empty() != true) {
				Node* prevNode = deleteQueue.back();
				Node* deleting = prevNode->nextField;
				deleteQueue.pop_back();

				for (int j = 1; j < columnCount; ++j) {
					if (columnTrees[i+j]->getName() == 0) {
						minAvialableIndex.add(deleting->data);
					}
					columnTrees[i+j]->deleteSingleNode(deleting, deleting->self);
					deleting = deleting->nextField;
					prevNode = columnTrees[i+j]->insert(newData[i+j % (columnCount-1)]);
					prevNode = prevNode->nextField;
				}
			}
		}
	}
	return;
}

std::vector<Node*> database::select(Comparisson queryType, int firstOperand, int secondOperand) {
	std::vector<Node*> sortQueue;
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperand) {
			std::vector<Node*> searchQueue = columnTrees[i]->search(secondOperand, queryType);
			while(searchQueue.empty() != true) {
				Node* node = searchQueue.back();
				searchQueue.pop_back();
				for (int j = i; j < columnCount; ++j) {
					node = node->nextField;
				}
				sortQueue.push_back(node);
			}
		}
	}
	sort(sortQueue.begin(), sortQueue.end());
	return sortQueue;
}

void database::printSelectChunk(Comparisson queryType, int firstOperand, int secondOperand, int* columnList, int listSize) {
	std::vector<Node*> printing = select(queryType, firstOperand, secondOperand);
	for (int i = 0; i < printing.size(); ++i) {
		for (int j = 0; j < columnCount; ++j) {
			for (int k = 0; k < listSize; ++k) {
				if (listSize == 0 or columnTrees[j]->getName() == columnList[k]) {
					//SHOULD DEHASH THE DATA TO PRINT LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					std::cout << printing[i]->data << " ";
					break;
				}
			}
		}
		std::cout << "\n";
	}
	return;
}
