#include <iostream>
#include <cmath>
#include <vector>

int PARENT(int i) {
    return floor(i/2);
}

const int LEFT(int i) {
    return i << 1;
}

const int RIGHT(int i) {
    return (i << 1) + 1;
}

class MAX_HEAP
{
    size_t heap_size;
    size_t length;
    std::vector<int> data;
};


/* 
* 最大堆化，维护最大对性质的关键
* 时间复杂度O(lgn)
*/
void MAX_HEAPIFY(int i ) {

}

/*
* 从无序的输入数据数组中构造一个最大堆
* 时间复杂度O(n)
*/
void BUILD_MAX_HEAP(MAX_HEAP A) {

}

/*
* 对一个数组进行原址排序
* 复杂度O(nlgn)
*/
void HEAPSORT() {

}

void MAX_HEAP_INSERT() {

}

void HEAP_EXTRACT_MAX() {

}

void HEAP_INCREASE_KEY() {

}

void HEAP_MAXIMUM() {

}

int main() {
    
    return 0;
}