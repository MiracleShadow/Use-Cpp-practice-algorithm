#ifndef BinarySearch_HPP
#define BinarySearch_HPP

#include <algorithm> // std::sort
#include <iterator>  // std::iterator_traits
#include <vector>    // std::vector

namespace miracle_shadow
{
/*
    * 返回指向范围中第一个元素的迭代器，该元素[first,last)不会比val小。
    * 该函数通过比较排序范围的非连续元素来优化执行的比较次数，这对随机访问迭代器特别有效。
    * 不像UPPER_BOUND，此函数返回的迭代器指向的值也可能等于val，而不仅仅是更大的值。
    */
template <class ForwardIterator, class T>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T &val)
{
    ForwardIterator it;
    typename std::iterator_traits<ForwardIterator>::difference_type count, step;
    count = distance(first, last);
    while (count > 0)
    {
        it = first;
        step = count / 2;
        advance(it, step);
        if (*it < val)
        { // or: if (comp(*it,val)), for version (2)
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }
    return first;
}

/*
    * Returns an iterator pointing to the first element in the range [first,last) which compares greater than val.
    * The function optimizes the number of comparisons performed by comparing non-consecutive elements of the sorted range, 
    *     which is specially efficient for random-access iterators.
    * Unlike lower_bound, the value pointed by the iterator returned by this function cannot be equivalent to val, only greater.
    */
template <class ForwardIterator, class T>
ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T &val)
{
    ForwardIterator it;
    typename std::iterator_traits<ForwardIterator>::difference_type count, step;
    count = std::distance(first, last);
    while (count > 0)
    {
        it = first;
        step = count / 2;
        std::advance(it, step);
        if (!(val < *it)) // or: if (!comp(val,*it)), for version (2)
        {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }
    return first;
}

/*
    * Returns true if any element in the range [first,last) is equivalent to val, and false otherwise.
    * 该函数通过比较排序范围的非连续元素来优化执行的比较次数，这对随机访问迭代器特别有效。
    */
template <class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T &val)
{
    first = miracle_shadow::lower_bound(first, last, val);
    return (first != last && !(val < *first));
}

/*
    * 返回包含范围的所有元素的子范围的边界，其[first,last)值等于val。
    * 如果VAL不等同于在范围内的任何值时，子范围返回具有零的长度，
    *     与两个迭代器指向最接近的值大于VAL，如果有的话，或者持续，如果VAL比较比在所有元素更大范围。
    */
template <class ForwardIterator, class T>
std::pair<ForwardIterator, ForwardIterator>
    equal_range(ForwardIterator first, ForwardIterator last, const T &val)
{
    ForwardIterator it = miracle_shadow::lower_bound(first, last, val);
    return std::make_pair(it, miracle_shadow::upper_bound(it, last, val));
}
}; // namespace miracle_shadow

#endif // BinarySearch_HPP
