#include "../BinarySearch.hpp"
#include <iostream>  // std::cout

int main()
{
    int myints[] = {10, 20, 30, 30, 20, 10, 10, 20};
    std::vector<int> v(myints, myints + 8); // 10 20 30 30 20 10 10 20

    std::sort(v.begin(), v.end()); // 10 10 10 20 20 20 30 30

    std::vector<int>::iterator low, up;
    low = miracle_shadow::lower_bound(v.begin(), v.end(), 20);
    up = miracle_shadow::upper_bound(v.begin(), v.end(), 20);

    std::cout << "lower_bound at position " << (low - v.begin()) << '\n';
    std::cout << "upper_bound at position " << (up - v.begin()) << '\n';

    if (miracle_shadow::binary_search(v.begin(), v.end(), 15))
        std::cout << "'15' found!\n";
    else
        std::cout << "'15' not found.\n";
    if (miracle_shadow::binary_search(v.begin(), v.end(), 20))
        std::cout << "'20' found!\n";
    else
        std::cout << "'20' not found.\n";

    // std::pair<std::vector<int>::iterator, std::vector<int>::iterator> bounds;
    auto bounds = miracle_shadow::equal_range(v.begin(), v.end(), 20);
    std::cout << "bounds at positions " << (bounds.first - v.begin())
              << " and " << (bounds.second - v.begin()) << '\n';
    return 0;
}
