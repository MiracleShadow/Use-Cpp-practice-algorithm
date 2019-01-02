#ifndef MY_Map
#define MY_Map

#include <iostream> // use ostream

namespace miracle_shadow
{
template <typename KEY, typename T>
class Map
{
  private:
    struct Elem
    {
        KEY key;
        T data;
        Elem *left;
        Elem *right;
        int height;
        bool rightThread; // normal right child link or a thread link
    };
    Elem *_root; // a dummy root sentinel
    int _size;

    // helper method for inserting record into tree.
    bool insert(Elem *&root, const KEY &key, const T &data, Elem *lastLeft);

    // helper method for print tree
    void printTree(ostream &out, int level, Elem *p) const;

    // common code for deallocation
    void destructCode(Elem *&p);

    // common code for copy tree; not required.
    void copyCode(Elem *&newRoot, Elem *origRoot);

    // common code for deep copying threaded tree
    void addToMap(Elem *root, Map<KEY, Elem *> &keyElemMap);

    void copyThread(Elem *&newRoot, Elem *origRoot);

    int height(Elem *root);

    // single right rotation
    void rotateRight(Elem *&);

    // single left rotation
    void rotateLeft(Elem *&);

    // double right rotation
    void doubleRotateRight(Elem *&);

    // double left rotation
    void doubleRotateLeft(Elem *&);

  public:
    // a simple Iterator, traverse the collection in one direction
    class Iterator
    {
      public:
        Iterator() {}

        explicit Iterator(Elem *cur) : _cur(cur) {}

        Elem &operator*();

        Elem *operator->();

        Iterator operator++(int);

        bool operator==(Iterator it);

        bool operator!=(Iterator it);

      private:
        Elem *_cur;
    };

    Iterator begin() const;

    Iterator end() const;

    // constructs empty Map
    Map();

    // copy constructor
    Map(const Map &rhs);

    // destructor
    ~Map();

    // assignment operator
    Map &operator=(const Map &rhs);

    // insert an element into the Map; return true if successful
    bool insert(KEY, T);

    // remove an element from the Map; return true if successful
    bool erase(KEY);

    // return size of the Map
    int size() const;

    // return an iterator pointing to the end if the element is not found,
    // otherwise, return an iterator to the element
    Iterator find(KEY) const;

    // overloaded subscript operator
    T &operator[](KEY);

    // output the underlying BST
    ostream &dump(ostream &out) const;
};

template <typename KEY, typename T>
ostream &operator<<(ostream &, const Map<KEY, T> &);

template <typename KEY, typename T>
Map<KEY, T>::Map()
{
    // create a dummy root node
    _root = new Elem;
    _root->left = _root; // empty tree
    _root->right = NULL;
    _root->rightThread = false;
    _size = 0;
    _root->height = 0;
}

// copy constructor
template <typename KEY, typename T>
Map<KEY, T>::Map(const Map<KEY, T> &v)
{
    // if empty tree
    if (v._root == v._root->left)
    {
        _root = new Elem;
        _root->left = _root; // empty tree
        _root->right = NULL;
        _root->height = 0;
        _size = 0;
    }
    else
    {
        _root = new Elem;
        _root->left = _root;
        _root->right = NULL;
        _root->height = 0;
        copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes
        copyThread(_root, v._root);           // to copy the threading; must pass dummy nodes to complete the threads
        _size = v._size;
    }
}

// construct a key-element Map to rethread the new tree
// the Map contains all nodes key values and their corresonding elem node address
// for furture lookup in setting up threads
template <typename KEY, typename T>
void Map<KEY, T>::addToMap(Elem *root, Map<KEY, Elem *> &keyElemMap)
{
    if (root)
    {
        keyElemMap[root->key] = root;
        addToMap(root->left, keyElemMap);
        if (!root->rightThread)
            addToMap(root->right, keyElemMap);
    }
}

// common copy code for thread copying
template <typename KEY, typename T>
void Map<KEY, T>::copyThread(Elem *&newRoot, Elem *origRoot)
{
    // construct the key-element Map for new and orig tree
    Map<KEY, Elem *> newKeyElemMap;
    Map<KEY, Elem *> origKeyElemMap;
    addToMap(newRoot->left, newKeyElemMap);
    addToMap(origRoot->left, origKeyElemMap);

    // start at the last element in the tree, which threads to root
    typename miracle_shadow::Map<KEY, Elem *>::reverse_iterator it = origKeyElemMap.rbegin();
    newKeyElemMap[it->first]->rightThread = true;
    newKeyElemMap[it->first]->right = newRoot;

    // then thread the rest of the tree backwardly
    it++;
    while (it != origKeyElemMap.rend())
    {
        if (it->second->rightThread)
        {
            newKeyElemMap[it->first]->rightThread = true;
            newKeyElemMap[it->first]->right = newKeyElemMap[origKeyElemMap[it->first]->right->key];
        }
        it++;
    }
}

// common copy code for deep copy a tree without copying threads
template <typename KEY, typename T>
void Map<KEY, T>::copyCode(Elem *&newRoot, Elem *origRoot)
{
    if (origRoot == 0)
        newRoot = 0;
    else
    {
        newRoot = new Elem;
        newRoot->height = origRoot->height;
        newRoot->key = origRoot->key;
        newRoot->data = origRoot->data;
        newRoot->rightThread = origRoot->rightThread;
        copyCode(newRoot->left, origRoot->left);
        if (!origRoot->rightThread)
            copyCode(newRoot->right, origRoot->right);
    }
}

template <typename KEY, typename T>
Map<KEY, T>::~Map()
{
    if (_root->left != _root) // not an empty tree
        destructCode(_root->left);
    delete _root;
}

template <typename KEY, typename T>
void Map<KEY, T>::destructCode(Map::Elem *&p)
{
    if (p == p->left)
    {
        return;
    }
    if (p->left != nullptr)
    {
        destructCode(p->left);
    }

    if (!p->rightThread)
    {
        destructCode(p->right);
    }
    delete p;
    return;
}

//need to change
template <typename KEY, typename T>
bool Map<KEY, T>::insert(KEY key, T value)
{
    if (insert(_root->left, key, value, _root))
    {
        _size++;
        return true;
    }
    return false;
}

template <typename KEY, typename T>
Map<KEY, T> &Map<KEY, T>::operator=(const Map<KEY, T> &rhs)
{
    if (_root->left != _root)
    {
        destructCode(_root->left);
        _root->left = _root;
    }

    if (rhs._root != rhs._root->left)
    {
        copyCode(_root->left, rhs._root->left);
        copyThread(_root, rhs._root);
        _size = rhs._size;
    }
    return *this;
}

// single right rotation
template <typename KEY, typename T>
void Map<KEY, T>::rotateRight(Elem *&node)
{
    Elem *k1 = node->left;
    node->left = k1->rightThread ? NULL : k1->right;
    k1->right = node;
    k1->rightThread = false;
    node->height = max(height(node->left), node->rightThread ? 0 : height(node->right)) + 1;
    k1->height = max(height(k1->left), node->height) + 1;
    node = k1;
}

// single left rotation
template <typename KEY, typename T>
void Map<KEY, T>::rotateLeft(Elem *&node)
{
    // you fill in here
    Elem *k2 = node->right;
    if (k2->left == NULL)
    {
        node->rightThread = true;
        node->right = k2;
    }
    else
    {
        node->right = k2->left;
        node->rightThread = false;
    }
    k2->left = node;

    node->height = max(height(node->left), node->rightThread ? 0 : height(node->right)) + 1;
    k2->height = max(k2->rightThread ? 0 : height(k2->right), node->height) + 1;
    node = k2;
}

// double right rotation
template <typename KEY, typename T>
void Map<KEY, T>::doubleRotateRight(Elem *&node)
{
    // you fill in here
    rotateLeft(node->left);
    rotateRight(node);
}

// double left rotation
template <typename KEY, typename T>
void Map<KEY, T>::doubleRotateLeft(Elem *&node)
{
    rotateRight(node->right);
    rotateLeft(node);
}

template <typename KEY, typename T>
bool Map<KEY, T>::insert(Map<KEY, T>::Elem *&cur, const KEY &key, const T &data, Map<KEY, T>::Elem *lastLeft)
{
    if (cur == _root || cur == 0)
    {
        cur = new Elem;
        cur->data = data;
        cur->key = key;
        cur->left = 0;
        cur->right = lastLeft;
        cur->rightThread = true;
        cur->height = 1;
        return true;
    }

    if (key == cur->key)
    {
        return false;
    }
    // insert at left
    if (key < cur->key)
    {
        bool res = insert(cur->left, key, data, cur);
        Elem *&p = cur;
        int leftHeight = height(p->left);
        int rightHeight = p->rightThread ? 0 : height(p->right);
        if (leftHeight - rightHeight >= 2)
        {
            int lh = height(p->left->left);
            int rh = p->left->rightThread ? 0 : height(p->left->right);
            if (lh >= rh)
            {
                rotateRight(p);
            }
            else
            {
                doubleRotateRight(p);
            }
        }
        cur->height = max(height(cur->left), cur->rightThread ? 0 : height(cur->right)) + 1;
        return res;
    }

    // insert at right
    if (!cur->rightThread)
    {
        bool res = insert(cur->right, key, data, lastLeft);
        Elem *&p = cur;
        int leftHeight = height(p->left);
        int rightHeight = height(p->right);
        if (rightHeight - leftHeight >= 2)
        {
            int lh = height(p->right->left);
            int rh = p->right->rightThread ? 0 : height(p->right->right);
            if (rh >= lh)
            {
                rotateLeft(p);
            }
            else
            {
                doubleRotateLeft(p);
            }
        }
        cur->height = max(height(cur->left), cur->rightThread ? 0 : height(cur->right)) + 1;
        return res;
    }
    else
    { // current's right is a thread; add a new node
        cur->rightThread = false;
        cur->right = new Elem;
        cur->right->key = key;
        cur->right->data = data;
        cur->right->left = 0;
        cur->right->right = lastLeft;
        cur->right->rightThread = true;
        cur->right->height = 1;
        cur->height = max(height(cur->left), cur->right->height) + 1;
        return true;
    }
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() const
{ // return the left most (smallest) tree node
    // fill in here
    Elem *p;
    Map::Iterator iter;

    p = _root->left;
    if (p == _root)
    {
        Map::Iterator iter(p);
        return iter;
    }

    while (p->left != nullptr)
    {
        p = p->left;
    }

    Iterator iter2(p);
    return iter2;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::find(KEY key) const
{
    Elem *p;

    if (_root->left == _root) //empty tree
    {
        return end();
    }
    p = _root->left;
    while (1)
    {
        if (p == _root)
        {
            return end();
        }
        if (p == nullptr)
        {
            return end();
        }
        else if (p->key == key)
        {
            Iterator iter(p);
            return iter;
        }
        else if (p->key > key)
        {
            // find from left tree
            p = p->left;
        }
        else if (p->key < key && !p->rightThread)
        {
            // find from right tree
            p = p->right;
        }
        else if (p->key < key && p->rightThread)
        {
            return end();
        }
    }
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const
{ // return the dummy root node
    // fill in here
    Iterator iter(_root);
    return iter;
}

template <typename KEY, typename T>
int Map<KEY, T>::height(Map<KEY, T>::Elem *node)
{
    if (node == NULL || node == _root)
    {
        return 0;
    }
    return node->height;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int)
{
    // fill in here
    Elem *node;

    if (_cur != nullptr)
    {
        if (_cur->rightThread && !_cur->right->right)
        {
            _cur = _cur->right;

            return Iterator(_cur);
        }
        else if (_cur->rightThread && _cur->right->right)
        {
            _cur = _cur->right;

            return Iterator(_cur);
        }
        else if (!_cur->rightThread && _cur->right)
        {
            node = _cur->right;
            while (node->left != nullptr)
            {
                node = node->left;
            }
            _cur = node;
            return Iterator(_cur);
        }
    }
    else if (_cur == NULL)
    {
        return Iterator(NULL);
    }
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem &Map<KEY, T>::Iterator::operator*()
{
    return *_cur; // fill in here
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem *Map<KEY, T>::Iterator::operator->()
{
    // fill in here
    return _cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator!=(Map::Iterator it)
{
    return _cur != it._cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator==(Map::Iterator it)
{
    return _cur == it._cur;
}

template <typename KEY, typename T>
int Map<KEY, T>::size() const
{
    return _size;
}

template <typename KEY, typename T>
T & ::Map<KEY, T>::operator[](KEY key)
{

    Map::Iterator iter;
    iter = find(key);
    if (iter == end())
    {
        insert(key, iter->data);
        iter = find(key);
        return iter->data;
    }

    return iter->data;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream &out, int level, Elem *p) const
{
    int i;
    if (p)
    {
        if (p->right && !p->rightThread)
            printTree(out, level + 1, p->right);
        for (i = 0; i < level; i++)
        {
            out << "\t";
        }
        out << p->key << " " << p->data << "(" << p->height - 1 << ")" << '\n';
        printTree(out, level + 1, p->left);
    }
}

// outputs information in tree in inorder traversal order
template <typename KEY, typename T>
ostream &Map<KEY, T>::dump(ostream &out) const
{
    if (_root == _root->left)
    { // tree empty
        return out;
    }
    printTree(out, 0, _root->left); // print tree structure
    return out;
}

// outputs using overloaded << operator
template <typename KEY, typename T>
ostream &operator<<(ostream &out, const Map<KEY, T> &v)
{
    v.dump(out);
    return out;
}
}; // namespace miracle_shadow

#endif // MY_Map
