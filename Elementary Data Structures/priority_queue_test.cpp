#include <iostream>
#include "my_priority_queue.hpp"

int main()
{
    using miracle_shadow::priority_queue;
    priority_queue<int> pq;
    pq.push(1);
    std::cout << "pq.top() = " << pq.top() << std::endl;
    std::cout << "pq.size() = " << pq.size() << std::endl;
    pq.pop();
    std::cout << "pq.top() = " << pq.top() << std::endl;
    std::cout << "pq.size() = " << pq.size() << std::endl;
    return 0;
}