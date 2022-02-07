#include "hashUtils.h"
#include <vector>
#include <iostream>

database::database(std::string newName, int sz, Type* newTypes, long long* columnNames) {
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
	minAvialableIndex.createEmptyTree(MAXN);
}

void database::insert(vector<std::string> &inputVector) {
	long long* newValues = new long long [(int)inputVector.size()];
	for (int i = 0; i < (int)inputVector.size(); ++i) {
		newValues[i] = hashh(inputVector[i], columnTypes[i+1]);
	}
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

void database::deleteChunk(Comparisson queryType, std::string firstOperandStr, std::string secondOperandStr) {
	long long firstOperand = hashh(firstOperandStr, STRING);
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperand) {
			long long secondOperand = hashh(secondOperandStr, columnTypes[i]);
			std::vector<Node*> deleteQueue = columnTrees[i]->search(secondOperand, queryType);
			for (int j = 0; j < deleteQueue.size(); ++j) {
				for (int k = i; k < columnCount; ++k) {
					deleteQueue[j] = deleteQueue[j]->nextField;
				}
			}
			while(deleteQueue.empty() != true) {
				Node* deleting = deleteQueue.back();
				deleteQueue.pop_back();
				for (int j = 0; j < columnCount; ++j) {
					if (j == 0) {
						minAvialableIndex.add(deleting->data);
					}
					columnTrees[j]->deleteNode(deleting, deleting->self);
					deleting = deleting->nextField;
				}
			}
			return;
		}
	}
	return;
}

void database::updateChunk(Comparisson queryType, std::string firstOperandStr, std::string secondOperandStr, vector<std::string> &newDataStr) {
	long long* newData = new long long [(int)newDataStr.size()];
	long long firstOperand = hashh(firstOperandStr, STRING);
	for (int i = 0; i < (int)newDataStr.size(); ++i)
		newData[i] = hashh(newDataStr[i], columnTypes[i+1]);
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperand) {
			long long secondOperand = hashh(secondOperandStr, columnTypes[i]);
			std::vector<Node*> deleteQueue = columnTrees[i]->search(secondOperand, queryType);
			for (int j = 0; j < deleteQueue.size(); ++j) {
				for (int k = i; k < columnCount; ++k) {
					deleteQueue[j] = deleteQueue[j]->nextField;
				}
				Node* tmp = deleteQueue[j];
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

std::vector<Node*> database::select(Comparisson queryType, long long firstOperand, long long secondOperand) {
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

void database::printSelectChunk(Comparisson queryType, std::string firstOperandStr, std::string secondOperandStr, vector<std::string> &columnListVec) {
	int listSize = columnListVec.size();
	std::vector<Node*> printing;
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == hashh(firstOperandStr, STRING)) {
			printing = select(queryType, hashh(firstOperandStr, STRING), hashh(secondOperandStr, columnTypes[i]));
			sortVector(printing);
			break;
		}
	}
	for (int i = 0; i < printing.size(); ++i) {
		for (int j = 0; j < columnCount; ++j) {
			for (int k = 0; k < listSize; ++k) {
				if (columnTrees[j]->getName() == hashh(columnListVec[k], STRING)) {
					std::cout << deHash(printing[i]->data, columnTypes[j]) << " ";
				}
			}
			if (listSize == 0) {
				if (j == 0) 
					std::cout << deHash(((printing[i]->data)+1), columnTypes[j]) << " "; //ID is 1based but stored 0base
				else
					std::cout << deHash(printing[i]->data, columnTypes[j]) << " ";
			}
			printing[i] = printing[i]->nextField;
		}
		std::cout << "\n";
	}
	return;
}

std::string database::getName() {
	return name;
}

void database::sortVector(std::vector<Node*> &input) {
	std::vector<Node*> tmp;
	tmp.resize((int)input.size());
	mergeSort(0, (int)input.size(), input, tmp);
}

void database::mergeSort(int begin, int end, std::vector<Node*> &input, std::vector<Node*> &tmp) {
	if (end - begin <= 1)
		return;
	
	int mid = begin + ((end-begin)/2);
	mergeSort(begin, mid, input, tmp);
	mergeSort(mid, end, input, tmp);

	for (int i = begin; i < end; ++i)
		tmp[i] = input[i];
	
	int itFirst = begin, itSecond = mid, index = begin;
	while (itFirst < mid and itSecond < end)
		if (tmp[itFirst]->data <= tmp[itSecond]->data)
			input[index++] = tmp[itFirst++];
		else
			input[index++] = tmp[itSecond++];
	while(itFirst < mid)
		input[index++] = tmp[itFirst++];
	while (itSecond < end)
		input[index++] = tmp[itSecond++];
	
	return;
}
