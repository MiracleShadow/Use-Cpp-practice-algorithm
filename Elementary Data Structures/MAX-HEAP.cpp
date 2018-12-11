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
public:
    size_t heap_size;   /* 堆元素个数，有效数据 */
    size_t length;      /* 数组长度 */
    std::vector<int> data;
    MAX_HEAP(std::vector<int> t);
};

MAX_HEAP::MAX_HEAP(std::vector<int> t) {
    this->data = t;
    this->length = t.size()-1;
    // this->heap_size = t.size()-1;
}

/* 
* 最大堆化，维护最大对性质的关键
* 时间复杂度O(lgn)
*/
void MAX_HEAPIFY(MAX_HEAP &heap, int i) {
    int l = LEFT(i), r = RIGHT(i);
    int largest = i;
    if(l <= heap.heap_size && heap.data[l] > heap.data[i]) {
        largest = l;
    }
    if(r <= heap.heap_size && heap.data[r] > heap.data[largest]) {
        largest = r;
    }
    if(largest != i) {
        std::swap(heap.data[i], heap.data[largest]);
        MAX_HEAPIFY(heap, largest);
    }
}

/*
* 从无序的输入数据数组中构造一个最大堆
* 时间复杂度O(n)
*/
void BUILD_MAX_HEAP(MAX_HEAP &heap) {
    heap.heap_size = heap.length;
    for (int i = floor(heap.length / 2); i >= 1; --i) {
        MAX_HEAPIFY(heap, i);
    }
}

/*
* 对一个数组进行原址排序
* 时间复杂度O(nlgn)
*/
void HEAPSORT(std::vector<int> &a) {
    MAX_HEAP heap(a);
    BUILD_MAX_HEAP(heap);
    
    for(size_t i = heap.length; i >= 2; --i) {
        std::swap(heap.data[1], heap.data[i]);
        heap.heap_size--;
        MAX_HEAPIFY(heap, 1);
    }
    a = heap.data;
}

/*
* 返回max-heap中具有最大键字的元素
* 时间复杂度O(1)
*/
int HEAP_MAXIMUM(MAX_HEAP heap) {
    return heap.data[1];
}

/*
* 去掉并返回max-heap中具有最大键字的元素
* 时间复杂度O(lgn)
*/
int HEAP_EXTRACT_MAX(MAX_HEAP &heap) {
    if(heap.heap_size < 1) {
        std::cerr << "heap underflow" << std::endl;
        return -1;
    }
    int maxn = heap.data[1];
    heap.data[1] = heap.data[heap.heap_size];
    heap.heap_size--;
    MAX_HEAPIFY(heap, 1);
    return maxn;
}

/*
* 将max-heap中的第i个元素的关键字增大到key(key >= 第i个元素的值)
* 时间复杂度O(lgn)
*/
void HEAP_INCREASE_KEY(MAX_HEAP &heap, size_t i, int key) {
    if(key < heap.data[i]) {
        std::cerr << "new key is smaller than current key" << std::endl;
        return;
    }
    heap.data[i] = key;
    while(i > 1 && heap.data[PARENT(i)] < heap.data[i]) {
        std::swap(heap.data[i], heap.data[PARENT(i)]);
        i = PARENT(i);
    }
}

/*
* 实现insert操作
* 时间复杂度O(lgn)
*/
void MAX_HEAP_INSERT(MAX_HEAP &heap, int key) {
    heap.heap_size++;
    heap.data[heap.heap_size] = _I32_MIN;
    HEAP_INCREASE_KEY(heap, heap.heap_size, key);
}

int main() {
    std::vector<int> t(1, 0);
    int n, num;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> num;
        t.push_back(num);
    }
    MAX_HEAP heap(t);
    std::cout << "myheap.length=" << heap.length << std::endl;
    for (int i = 1; i <= heap.length; ++i)
    {
        std::cout << heap.data[i] << " ";
    }
    std::cout << std::endl;
    BUILD_MAX_HEAP(heap);
    for (int i = 1; i <= heap.heap_size; ++i)
    {
        std::cout << heap.data[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
