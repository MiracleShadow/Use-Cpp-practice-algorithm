#include <iostream>
#include <cmath>
#include <vector>

namespace zzh {
    template <typename T>
    class priority_queue
    {
        public:
        typedef size_t handle_type;
        typedef T value_type;

        /*
        * push对应INSERT
        * top对应MAXIMUM
        * pop对应EXTRACT-MAX
        * update对应INCREASE-KEY
        * 不过update没有INCREASE-KEY的新数据比旧数据更优先的限制
        * 新数据既可以比旧数据优先，也可以不比旧数据优先
        */
        priority_queue(std::function<bool(value_type &, value_type &)> comp);
        size_t size();
        bool empty();
        handle_type push(const value_type &v);
        value_type pop();
        value_type top();
        handle_type topHandle();
        value_type value(handle_type const &handle);
        void update(handle_type const &handle, value_type const &v);

    }
}
