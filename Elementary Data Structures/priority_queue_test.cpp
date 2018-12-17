#include "my_priority_queue.hpp"
#include <iostream>
#include <functional>

template <typename T>
struct cmp : std::binary_function<T, T, bool>
{
    bool operator()(T a, T b) const { return a > b; }
};

auto comp = [](const int& lhs, const int& rhs) { return lhs > rhs; };

int main()
{
    using miracle_shadow::priority_queue;

    priority_queue<int> pq_l;
    for (int i = 1; i <= 8; i++) {
        pq_l.push(rand()%20);
    }

    std::cout << "pq_l.top() = " << pq_l.top() << std::endl;
    std::cout << "pq_l.size() = " << pq_l.size() << std::endl;
    std::cout << "pq_l: ";

    while (!pq_l.empty()) {

        std::cout << pq_l.top() << " ";
        pq_l.pop();
    }
    std::cout << std::endl << std::endl;


    std::vector<int> vi;
    for (int i = 1; i <= 16; ++i)
        vi.push_back(rand()%100);
    
    priority_queue<int, std::vector<int>, std::greater<int>> pq_g(vi);

    std::cout << "pq_g.top() = " << pq_g.top() << std::endl;
    std::cout << "pq_g.size() = " << pq_g.size() << std::endl;
    std::cout << "pq_g: ";

    while (!pq_g.empty()) {

        std::cout << pq_g.top() << " ";
        pq_g.pop();
    }

    return 0;
}