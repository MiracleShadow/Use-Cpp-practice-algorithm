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
    for (int i = PARENT(A.size() - 1); i >= 0; --i) {
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

// template <typename T, class Compare>
// void sort_heap(std::vector<T> &A, Compare comp)
// {
//     std::vector<T> B;
//     make_heap(A, comp);
    
//     for(int i = A.size(); i >= 1; --i)
//     {
//         B.push_back(A[A.size() - 1]);
//         A[0] = A[A.size() - 1];
//         A.pop_back();
//         heapify(A, 0, comp);
//     }
//     A = B;
// }

template <typename T, 
          typename Container = std::vector<T>, 
          typename Compare = std::less<typename Container::value_type> >
class priority_queue
{
  public:
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
    
  private:
    Container cont_;    //内部容器
    Compare comp_;      //比较规则

  public:
    priority_queue() :cont_(){}

    // explicit 指定这个构造器只能被明确的调用/使用，不能作为类型转换操作符被隐含的使用
    explicit priority_queue(const Compare &comp) :cont_(), comp_(comp) {}

    priority_queue(const Container &cont, const Compare &comp)
        : cont_(cont), comp_(comp) {
        make_heap(cont_, comp_);
    };

    priority_queue(const Container &cont)
        : cont_(cont) {
        make_heap(cont_, comp_);
    };

    /*
    * push对应INSERT
    * top对应MAXIMUM
    * pop对应EXTRACT-MAX
    */
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
};
} // namespace miracle_shadow

#endif // MY_PRIORITY_QUEUE