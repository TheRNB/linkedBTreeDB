#include "utils/hashUtils.h"
#include "validators/validators.h"
#include <vector>
#include <iostream>

database::database(std::string newName, int sz, Type* newTypes, std::string* columnNames) {
	name = newName;
	columnCount = sz+1;
	columnTypes = new Type[columnCount];
	columnTypes[0] = INTEGER;
	for (int i = 1; i < columnCount; ++i) 
		columnTypes[i] = newTypes[i-1];
	columnTrees = new BTree*[sz+1];
	columnTrees[0] = new BTree("id"); //ID Column
	for (int i = 1; i <= sz; ++i) {
		columnTrees[i] = new BTree(columnNames[i-1]);
	}
	minAvialableIndex.createEmptyTree(MAXN);
}

void database::insert(vector<std::string> &inputVector) {
	long long* newValues = new long long [(int)inputVector.size()];
	for (int i = 0; i < (int)inputVector.size(); ++i) {
		validator_inputField(inputVector[i], columnTypes[i+1]);
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

void database::deleteChunk(Comparisson queryType, std::string firstOperandStr, std::string secondOperandStr, multiCondition inclusionType, Comparisson queryTwoType, std::string firstTwoOperand, std::string secondTwoOperand) {
	long long firstOperand = hashh(firstOperandStr, STRING);
	for (int i = 0; i < columnCount; ++i) {
		for (int j = 0; j < columnCount; ++j) {
			if (columnTrees[i]->getName() == firstOperandStr and columnTrees[j]->getName() == firstTwoOperand) {
				std::vector<Node*> deleteQueue = select(queryType, firstOperandStr, hashh(secondOperandStr, columnTypes[i]), inclusionType, queryTwoType, firstTwoOperand, hashh(secondTwoOperand, columnTypes[j]));
				
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
	}
	return;
}

void database::updateChunk(Comparisson queryType, std::string firstOperandStr, std::string secondOperandStr, vector<std::string> &newDataStr, multiCondition inclusionType, Comparisson queryTwoType, std::string firstTwoOperand, std::string secondTwoOperand) {
	long long* newData = new long long [(int)newDataStr.size()];
	long long firstOperand = hashh(firstOperandStr, STRING);
	for (int i = 0; i < (int)newDataStr.size(); ++i)
		newData[i] = hashh(newDataStr[i], columnTypes[i+1]);
	for (int i = 0; i < columnCount; ++i) {
		for (int m = 0; m < columnCount; ++m) {
			if (columnTrees[i]->getName() == firstOperandStr and columnTrees[m]->getName() == firstTwoOperand) {
				std::vector<Node*> deleteQueue = select(queryType, firstOperandStr, hashh(secondOperandStr, columnTypes[i]), inclusionType, queryTwoType, firstTwoOperand, hashh(secondTwoOperand, columnTypes[m]));
				for (int j = 0; j < deleteQueue.size(); ++j) {
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
	}
	return;
}

std::vector<Node*> database::select(Comparisson queryType, std::string firstOperand, long long secondOperand, multiCondition inclusionType, Comparisson queryTwoType, std::string firstTwoOperand, long long secondTwoOperand) {
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
	if (inclusionType == NONE) {
		return searchQueue;
	}
	
	if (inclusionType == AND) {
		std::vector<Node*> finalResult;
		for (int i = 0; i < columnCount; ++i) {
			if (columnTrees[i]->getName() == firstTwoOperand) {
				for (int j = 0; j < searchQueue.size(); ++j) {
					Node* tmp = searchQueue[j];
					for (int k = 0; k < i; ++k)
						tmp = tmp->nextField;

					if (queryTwoType == SMALLER) {
						if (tmp->data < secondTwoOperand)
							finalResult.push_back(searchQueue[j]);
					} else if (queryTwoType == EQUAL) {
						if (tmp->data == secondTwoOperand)
							finalResult.push_back(searchQueue[j]);
					} else if (queryTwoType == BIGGER){
						if (tmp->data > secondTwoOperand)
							finalResult.push_back(searchQueue[j]);
					}
				}
			}
		}
		return finalResult;
	} else if (inclusionType == OR) {
		std::vector<Node*> finalResult;
		for (int i = 0; i < columnCount; ++i) {
			if (columnTrees[i]->getName() == firstTwoOperand) {
				std::vector<Node*> searchTwoQueue = columnTrees[i]->search(secondTwoOperand, queryTwoType);
				for (int j = 0; j < searchTwoQueue.size(); ++j) {
					for (int k = i; k < columnCount; ++k) {
						searchTwoQueue[j] = searchTwoQueue[j]->nextField;
					}
				}

				sortVector(searchQueue);
				sortVector(searchTwoQueue);
				
				int iterOne = 0, iterTwo = 0;
				while (iterOne < searchQueue.size() and iterTwo < searchTwoQueue.size()) {
					if (searchQueue[iterOne]->data < searchTwoQueue[iterTwo]->data) {
						finalResult.push_back(searchQueue[iterOne++]);
					} else if (searchQueue[iterOne]->data > searchTwoQueue[iterTwo]->data) {
						finalResult.push_back(searchQueue[iterTwo++]);
					} else {
						finalResult.push_back(searchQueue[iterOne++]); iterTwo++;
					}
				}
			}
		}
		return finalResult;
	}
}

void database::printSelectChunk(Comparisson queryType, std::string firstOperandStr, std::string secondOperandStr, vector<std::string> &columnListVec, multiCondition inclusionType, Comparisson queryTwoType, std::string firstTwoOperand, std::string secondTwoOperand) {
	int listSize = columnListVec.size();
	std::vector<Node*> printing;
	for (int i = 0; i < columnCount; ++i) {
		if (columnTrees[i]->getName() == firstOperandStr) {
			for (int j = 0; j < columnCount; ++j) {
				if (columnTrees[j]->getName() == secondTwoOperand) {
					printing = select(queryType, firstOperandStr, hashh(secondOperandStr, columnTypes[i]), inclusionType, queryTwoType, firstTwoOperand, hashh(secondTwoOperand, columnTypes[j]));
					sortVector(printing);
					break;
				}
			}
		}
	}
	for (int i = 0; i < printing.size(); ++i) {
		for (int j = 0; j < columnCount; ++j) {
			for (int k = 0; k < listSize; ++k) {
				if (columnTrees[j]->getName() == columnListVec[k], STRING) {
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
