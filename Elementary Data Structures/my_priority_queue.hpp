#ifndef MY_PRIORITY_QUEUE
#define MY_PRIORITY_QUEUE

#include <functional>
#include <iostream>
#include <vector>

namespace miracle_shadow
{
inline size_t PARENT(size_t i) { return i > 0 ? (i - 1) / 2 : 0;}

inline size_t LEFT(size_t i) { return i * 2 + 1;}

inline size_t RIGHT(size_t i) { return i * 2 + 2;}

template <typename T>
bool compare_com(T a, T b) { return a < b;}
template <typename T, class Compare>
void heapify(std::vector<T> &A, size_t i, Compare comp)
{
    size_t l = LEFT(i), r = RIGHT(i);
    size_t largest = i;
    if (l < A.size() && comp(A[largest], A[l])) {
        largest = l;
    }
    if (r < A.size() && comp(A[largest], A[r])) {
        largest = r;
    }
    if(largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, largest, comp);
    }
}

/*
* Rearranges the elements in the vector in such a way that they form a heap.
*/
template <typename T, class Compare>
void make_heap(std::vector<T> &A, Compare comp)
{
    if(A.size() == 0) {
        return;
    }
    for (size_t i = PARENT(A.size() - 1); i >= 0; --i) {
        heapify(A, i, comp);
    }
}

/* 
* Given a heap in the vector, 
* this function extends the range considered a heap to size()+1 
* by placing the value in size() into its corresponding location within it.
*/
template <typename T, class Compare>
void push_heap(std::vector<T> &A, T t, Compare comp)
{
    A.push_back(t);
    size_t i = A.size() - 1;
    while(1 > 0 && comp(A[PARENT(i)], A[i])) {
        std::swap(A[i], A[PARENT(i)]);
        i = PARENT(i);
    }
}

/*
* the heap is shortened by one
*/
template <typename T, class Compare>
void pop_heap(std::vector<T> &A, Compare comp)
{
    if(A.size() == 0) {
        std::cerr << "heap underflow" << std::endl;
        return;
    }
    A[0] = A[A.size() - 1];
    A.pop_back();
    heapify(A, 0, comp);
}


template <typename T, 
          typename Container = std::vector<T>, 
          typename Compare = std::less<typename Container::value_type> >
class priority_queue
{
  public:
    typedef T value_type;

    /*
        * push对应INSERT
        * top对应MAXIMUM
        * pop对应EXTRACT-MAX
        */
    priority_queue(const Container &ctnr = Container(), const Compare &comp = Compare())
        :comp_(comp), cont_(ctnr) {
        make_heap(cont_, comp_);
    };
    size_t size() {
        return cont_.size();
    };
    bool empty() {
        return cont_.size() == 0;
    };
    void push(const value_type &v) {
        push_heap(cont_, v, comp_);
    };
    void pop() {
        pop_heap(cont_, comp_);
    };
    value_type top() {
        if(cont_.size() > 0)
            return cont_[0];
        else
            std::cerr << "heap is empty!" << std::endl;
        exit(-1);
    };

  private:
    Compare comp_; //比较规则
    Container cont_; //内部容器
};
} // namespace miracle_shadow

#endif // MY_PRIORITY_QUEUE