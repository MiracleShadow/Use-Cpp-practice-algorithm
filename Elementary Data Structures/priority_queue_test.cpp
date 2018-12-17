#include "my_priority_queue.hpp"
#include <iostream>
#include <functional>

template <typename T>
struct cmp : std::binary_function<T, T, bool>
{
    bool operator()(T a, T b) const { return a > b; }
};

int main()
{
    using miracle_shadow::priority_queue;
    priority_queue<int> pq;

    for (int i = 1; i <= 8; i++) {
        pq.push(i);
    }

    std::cout << "pq.top() = " << pq.top() << std::endl;
    std::cout << "pq.size() = " << pq.size() << std::endl;

    while (!pq.empty()) {

        std::cout << pq.top() << " ";
        pq.pop();
    }

    // priority_queue<int, std::less<int> > pq;
    
    return 0;
}