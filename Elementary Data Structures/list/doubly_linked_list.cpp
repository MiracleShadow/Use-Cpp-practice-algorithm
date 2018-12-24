#include <iostream>
#include <memory>       // for unique_ptr

template <typename T>
class doublyLinkedList      // 构造一个双向链表
{
private:
    struct node;
    using node_ptr = std::unique_ptr<node>;
    using node_raw_ptr = node *;
    
    struct node 
    {
        explicit node( const T &value, node_raw_ptr prev, node_ptr &&next ) 
            : value_( value ), previous_( prev ), next_( std::move( next ) )
        {  
        }

        explicit node( T &&value, node_raw_ptr prev, node_ptr &&next ) 
            : value_( std::move( value ) ), previous_( prev ), next_( std::move( next ) ) 
        {  
        }

        explicit node( const T &value = T{} ) 
            : value_( value ), previous_( nullptr ), next_( nullptr ) 
        { 
        }
        
        node( const node & ) = delete;
        node &operator=( const node & ) = delete;
        
        node( node && ) = default;
        node &operator=( node && ) = default;

        T value_;
        node_raw_ptr previous_;                        // raw pointer points to the previous node
        node_ptr     next_;                            // smart pointer points to the next node
    };
public:
    doublyLinkedList();
    bool push_back(T data);    // 尾插
    bool push_front(T data);   // 头插
    T pop_back();              // 尾出
    T pop_front();             // 头出
    node_raw_ptr insert(node_raw_ptr p, T key);
    node_raw_ptr erase(node_raw_ptr p);
    bool empty();
    size_t size();
    T front();
    T back();
};
