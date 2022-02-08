#ifndef _DATABASE_UTILS_
#define _DATABASE_UTILS_

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename DataType>
class minHeap {
public:
	minHeap() {
		array = NULL;
		iterator = 0;
	}
	void createEmptyTree(int newSize) {
		array = new DataType [newSize];
		iterator = 0;
		maxSize = newSize;
	}
	void add(DataType newNode) {
		if (iterator == maxSize)
			throw std::invalid_argument("Array is full");

		array[iterator] = newNode;
		int tmp = iterator;
		while (((tmp-1)/2) >= 0 and array[tmp] < array[(tmp-1)/2]) {
			swap(array[tmp], array[(tmp-1)/2]);
			tmp = (tmp-1)/2;
		}
		iterator++;
		return;
	}
	DataType removeRoot() {
		if (iterator <= 0)
			throw std::invalid_argument("Array is empty");

		DataType result = array[0];
		swap(array[0], array[iterator-1]);
		int tmp = 0;
		iterator--;
		while(tmp < iterator) {
			if (2*tmp+1 < iterator and array[tmp] > array[2*tmp+1] and (2*tmp+2 >= iterator or array[2*tmp+2] >= array[2*tmp+1])) {
				swap(array[tmp], array[2*tmp+1]);
				tmp = 2*tmp+1;
			} else if (2*tmp+2 < iterator and array[tmp] > array[2*tmp+2] and array[2*tmp+2] < array[2*tmp+1]) {
				swap(array[tmp], array[2*tmp+2]);
				tmp = 2*tmp+2;
			} else {
				break;
			}
		}
		return result;
	}
	int size() {
		return iterator;
		;
	}
	bool isEmpty() {
		return ((iterator == 0)?true: false);
		;
	}
	void levelOrderTraverse(int curr = 0) {
		for (int i = 0; i < iterator; ++i) {
			cout << array[i] << " " << i << " " << endl;
		}
		return;
	}
private:
	DataType* array;
	int iterator;
	int maxSize;
};
#endif