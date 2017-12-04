//Arunav N Sarkar 2017s2 ass3 z5061286
//TO MARKER:
//This code is incomplete and broken. I am ashamed to submit this and wish I had time to restart and redesign, or had realised I needed to earlier.
//I'm sorry to make you read this

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <memory>
#include <vector>
// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)

template <typename T> 
class btree {
class element;
class btreeNode;
public:
    friend class btree_iterator<T>;
    friend class const_btree_iterator<T>;

    typedef btree_iterator<T> iterator;
    typedef const_btree_iterator<const T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  /**
   * Constructs an empty btree.  Note that
   * the elements stored in your btree must
   * have a well-defined copy constructor and destructor.
   * The elements must also know how to order themselves
   * relative to each other by implementing operator<
   * and operator==. (These are already implemented on
   * behalf of all built-ins: ints, doubles, strings, etc.)
   * 
   * @param maxNodeElems the maximum number of elements
   *        that can be stored in each B-Tree node
   */

    btree(){ maxNodeElems = 40; root = nullptr; };

    btree(size_t maxNodeElems) : maxNodeElems(maxNodeElems) {root = nullptr;}

    /**
   * The copy constructor and  assignment operator.
   * They allow us to pass around B-Trees by value.
   * Although these operations are likely to be expensive
   * they make for an interesting programming exercise.
   * Implement these operations using value semantics and 
   * make sure they do not leak memory.
   */

  /** 
   * Copy constructor
   * Creates a new B-Tree as a copy of original.
   *
   * @param original a const lvalue reference to a B-Tree object
   */
    btree(const btree<T>& original);

  /** 
   * Move constructor
   * Creates a new B-Tree by "stealing" from original.
   *
   * @param original an rvalue reference to a B-Tree object
   */
    btree(btree<T>&& original);
  
  
  /** 
   * Copy assignment
   * Replaces the contents of this object with a copy of rhs.
   *
   * @param rhs a const lvalue reference to a B-Tree object
   */
    btree<T>& operator=(const btree<T>& rhs);

  /** 
   * Move assignment
   * Replaces the contents of this object with the "stolen"
   * contents of original.
   *
   * @param rhs a const reference to a B-Tree object
   */
    btree<T>& operator=(btree<T>&& rhs);

  /**
   * Puts a breadth-first traversal of the B-Tree onto the output
   * stream os. Elements must, in turn, support the output operator.
   * Elements are separated by space. Should not output any newlines.
   *
   * @param os a reference to a C++ output stream
   * @param tree a const reference to a B-Tree object
   * @return a reference to os
   */
   // friend std::ostream& operator<< <T> (std::ostream& os, const btree<T>& tree);

  /**
   * The following can go here
   * -- begin() 
   * -- end() 
   * -- rbegin() 
   * -- rend() 
   * -- cbegin() 
   * -- cend() 
   * -- crbegin() 
   * -- crend() 
   */

    iterator begin();
    iterator begin() const;
    iterator end();
    iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rbegin() const;
    reverse_iterator rend();
    reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cbegin();
    const_iterator cend() const;
    const_iterator cend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crbegin();
    const_reverse_iterator crend() const;
    const_reverse_iterator crend();

  /**
    * Returns an iterator to the matching element, or whatever 
    * the non-const end() returns if the element could 
    * not be found.  
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already 
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
    iterator find(const T& elem);
    
  /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
    const_iterator find(const T& elem) const;
      
  /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.  
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The 
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's copy constructor,
    * and if these things aren't available, 
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field 
    *         stores true if and only if the element needed to be added 
    *         because no matching element was there prior to the insert call.
    */
    std::pair<iterator, bool> insert(const T& elem);

  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation. 
    * Check that your implementation does not leak memory!
    */
    ~btree(){ root.reset(); }

    typename btree<T>::btreeNode::element* leftmost() const;
    typename btree<T>::btreeNode::element* rightmost() const;
  
private:

    class btreeNode {
    class element;
    public:
        btreeNode(size_t maxNodeElems, btree<T>::btreeNode::element* leftParentElement, btree<T>::btreeNode::element* rightParentElement) :
         maxNodeElems(maxNodeElems), leftParentElement(leftParentElement), rightParentElement(rightParentElement) {}

        ~btreeNode(){ 
            leftParentElement = nullptr;
            rightParentElement = nullptr;
        }
        
        std::pair<iterator, bool> insert(const T& value);
        btree<T>::btreeNode::element* findElement(const T& value);
        btree<T>::btreeNode* getAppropriateChild(const T& value);

    private:

        class element {
        public:
            element(const T& elem, btree<T>::btreeNode::element* nxt, btree<T>::btreeNode::element* pre) : value(elem), nxt(nxt), pre(pre) {}
            ~element(){
                nxt = nullptr;
                pre = nullptr;
            }

        private:
            T value;
            btree<T>::btreeNode::element* nxt;
            btree<T>::btreeNode::element* pre;
            btree<T>::btreeNode* containerNode;

        friend class btree;
        friend class btreeNode;
        friend class btree_iterator<T>;
        friend class const_btree_iterator<T>;
        };

        size_t maxNodeElems;
        std::vector<btree<T>::btreeNode::element> elements;
        element* leftParentElement;
        element* rightParentElement;

    friend class btree;
    friend class element;
    friend class btree_iterator<T>;
    friend class const_btree_iterator<T>;
    };

    std::unique_ptr<btreeNode> root;
    size_t maxNodeElems;
};

/*traverse tree down left side. checks at each node whether there are any
 *children nodes. if not then we are at last node and get first element in node
 */
template<typename T>
typename btree<T>::btreeNode::element* btree<T>::leftmost() const{
    if(root->elements.empty()) return nullptr;
    typename btree<T>::btreeNode::element* current = &root->elements.at(0);
    while(current->pre != nullptr){
        current = &current->pre->containerNode->elements.at(0);
    }
    return current;
}

/* use the iterator to iterate through till the element pointed to by the iterator 
 * has no next value. this is being used for end() so cannot use 
 * while(it != *this.end()) etc
 */
template<typename T>
typename btree<T>::btreeNode::element* btree<T>::rightmost() const{
    if(root->elements.empty()) return nullptr;
    typename btree<T>::btreeNode::element* current = &root->elements.back();
    while(current->nxt != nullptr){
        current = &current->nxt->containerNode->elements.back();
    }
    return current;
}

template<typename T>
typename btree<T>::iterator btree<T>::begin(){
    return iterator(this->leftmost());
}

template<typename T>
typename btree<T>::iterator btree<T>::begin() const{
    return iterator(this->leftmost());
}

template<typename T>
typename btree<T>::iterator btree<T>::end(){
    return iterator(nullptr, this->rightmost());
}

template<typename T>
typename btree<T>::iterator btree<T>::end() const{
    return iterator(nullptr, this->rightmost());
}


template<typename T>
typename btree<T>::reverse_iterator btree<T>::rbegin(){
    return reverse_iterator(this->end());
}

template<typename T>
typename btree<T>::reverse_iterator btree<T>::rbegin() const{
    return reverse_iterator(this->end());
}

template<typename T>
typename btree<T>::reverse_iterator btree<T>::rend(){
    return reverse_iterator(this->begin());
}

template<typename T>
typename btree<T>::reverse_iterator btree<T>::rend() const{
    return reverse_iterator(this->begin());
}

template<typename T>
typename btree<T>::const_iterator btree<T>::cbegin() const{
    return const_iterator(this->leftmost());
}

template<typename T>
typename btree<T>::const_iterator btree<T>::cbegin() {
    return const_iterator(this->leftmost());
}


template<typename T>
typename btree<T>::const_iterator btree<T>::cend() const{
    return const_iterator(nullptr, this->rightmost());
}

template<typename T>
typename btree<T>::const_iterator btree<T>::cend() {
    return const_iterator(nullptr, this->rightmost());
}

template<typename T>
typename btree<T>::const_reverse_iterator btree<T>::crbegin() const{
    return const_reverse_iterator(this->cend());
}

template<typename T>
typename btree<T>::const_reverse_iterator btree<T>::crbegin() {
    return const_reverse_iterator(this->cend());
}

template<typename T>
typename btree<T>::const_reverse_iterator btree<T>::crend() const{
    return const_reverse_iterator(this->cbegin());
}

template<typename T>
typename btree<T>::const_reverse_iterator btree<T>::crend() {
    return const_reverse_iterator(this->cbegin());
}

/* insert will traverse through the tree and place element in the correct node and 
 * order in the tree. it will go to a node, check if it is filled. if it is filled 
 * it will go to the appropriate child node. if it is not filled it will insert
 * element in the right place.
 */
template<typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::insert(const T& elem){
    btreeNode* current = this->root.get();
    if(current == nullptr){
        this->root = std::make_unique<btreeNode>(this->maxNodeElems, nullptr, nullptr);
        return this->root->insert(elem);
    }
    while(current != nullptr){
        typename btree<T>::btreeNode::element* hasElem = current->findElement(elem);
        if(hasElem != nullptr){
            return std::pair<iterator, bool>(iterator(hasElem), false);
        } else if(current->elements.size() == this->maxNodeElems){
            current = current->getAppropriateChild(elem);
        } else {
            return current->insert(elem);
        }
    }
    return std::pair<iterator, bool>(iterator(nullptr), false);
}

/* this is the insert for the node class. it is only called once it is verified that we can insert the value in here
 * i.e we have prechecks for if the node has the max number of elements or if the node already has an element of its
 * value in it.
 */
template<typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::btreeNode::insert(const T& elem){
    //this first block will insert an element to an empty node. it connects to the left and right parent elements of the node   
    if(this->elements.size() == 0){
        btree<T>::btreeNode::element newElem = element(elem, this->rightParentElement, this->leftParentElement);
        newElem.containerNode = this;
        this->elements.push_back(newElem);
        if(this->rightParentElement != nullptr) this->rightParentElement->pre = &newElem;
        if(this->leftParentElement != nullptr) this->leftParentElement->nxt = &newElem;
        return std::pair<iterator, bool>(iterator(&newElem), true);
    }
    // if there are already elements we will sweep through them and determine where the new element shall go. we rearrange the
    // next and pre pointers arond the element to place it in our doubly linked list of elements 
    for(size_t i = 0; i < this->elements.size(); ++i){
        if(i == this->elements.size()-1 && elem > this->elements.at(i).value){
            //case for if elem is greater than all the elements in the node
            btree<T>::btreeNode::element newElem = element(elem, this->elements.at(i).nxt, &this->elements.at(i));
            newElem.containerNode = this;
            if(this->elements.at(i).nxt != nullptr) this->elements.at(i).nxt->pre = &newElem;
            this->elements.at(i).nxt = &newElem;
            this->elements.push_back(newElem);
            return std::pair<iterator, bool>(iterator(&newElem), true);
        } else if(i == 0 && elem < this->elements.at(i).value){
            //case for if elem is smaller than all the elements in the node
            btree<T>::btreeNode::element newElem = element(elem, &this->elements.at(i), this->elements.at(i).pre);
            newElem.containerNode = this;
            if(this->elements.at(i).pre != nullptr) this->elements.at(i).pre->nxt = &newElem;
            this->elements.at(i).pre = &newElem;
            this->elements.insert(this->elements.begin(), newElem);
            return std::pair<iterator, bool>(iterator(&newElem), true);
        } else if(i < this->elements.size()-1 && elem > this->elements.at(i).value && elem < this->elements.at(i+1).value){
            //case for if elem shall be placed in between two elements in the Node
            btree<T>::btreeNode::element newElem = element(elem, &this->elements.at(i+1), &this->elements.at(i));
            newElem.containerNode = this;
            this->elements.at(i).nxt = &newElem;
            this->elements.at(i+1).pre = &newElem;
            this->elements.insert(this->elements.begin()+i+1, newElem);
            return std::pair<iterator, bool>(iterator(&newElem), true);
        } else {
            continue;
        }
    }
    return std::pair<iterator, bool>(iterator(nullptr), false);
}

//finds if the element exists in the Node
template<typename T>
typename btree<T>::btreeNode::element* btree<T>::btreeNode::findElement(const T& elem) {
    if(this->elements.empty()) return nullptr;
    for(int i = 0; i < this->elements.size(); ++i){
        if(this->elements.at(i).value == elem) return &(this->elements[i]);
    }
    return nullptr;
}

//chooses the appropirate child of a node to go to when inserting an element and a node is full
template<typename T>
typename btree<T>::btreeNode* btree<T>::btreeNode::getAppropriateChild(const T& elem) {
    for(size_t i = 0; i < this->elements.size(); ++i){
        for(size_t test = 0; test < this->elements.size(); ++test)
        if(i == 0 && elem < this->elements.at(i).value){
            if(this->elements.at(i).pre != nullptr){
                return this->elements.at(i).pre->containerNode;
            } else {
                btree<T>::btreeNode* newNode = new btreeNode(this->maxNodeElems, nullptr, &this->elements.at(i));
                return newNode;
            }
        } else if(i == this->elements.size()-1 && elem > this->elements.at(i).value){
            if(this->elements.at(i).nxt != nullptr){
                return this->elements.at(i).nxt->containerNode;
            } else {
                btree<T>::btreeNode* newNode = new btreeNode(this->maxNodeElems, &this->elements.at(i), nullptr);
                return newNode;
            }
        } else if(i < this->elements.size()-1 && elem > this->elements.at(i).value && elem < this->elements.at(i+1).value){
            if(this->elements.at(i).nxt->containerNode->findElement(this->elements.at(i).value) == nullptr){
                return this->elements.at(i).nxt->containerNode;
            } else {
                btree<T>::btreeNode* newNode = new btreeNode(this->maxNodeElems, &this->elements.at(i), &this->elements.at(i+1));
                return newNode;
            }
        } else {
            continue;
        }
    }
    return nullptr;
}









#endif
