#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

template<typename T> class btree;
// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template<typename T>
class btree_iterator{
public:
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    btree_iterator() : pointee(nullptr), lastElem(nullptr) {}
    btree_iterator(typename btree<T>::btreeNode::element *pointee ) : pointee(pointee), lastElem(nullptr) {}
    btree_iterator(typename btree<T>::btreeNode::element *pointee, typename btree<T>::btreeNode::element *lastElem ) : pointee(pointee), lastElem(lastElem) {}
   
    reference operator*() const{ return pointee->value; }
    pointer operator->() const{ return &(operator*()); }
    
    //post increment/decrement
    btree_iterator& operator++(){
        if(pointee->nxt == nullptr){
            this->lastElem = this->pointee;
        }
        pointee = pointee->nxt;
        return *this;
    }
    btree_iterator& operator--(){
        if(pointee == nullptr){
            pointee = lastElem;
            return *this;
        }
        pointee = pointee->pre;
        return *this;
    }
    //pre increment/decrement
    btree_iterator operator++(int){
        if(pointee->nxt == nullptr){
            this->lastElem = this->pointee;
        }
        btree_iterator tmp = *this;
        pointee = pointee->nxt;
        return tmp;
    }
    btree_iterator operator--(int){
        btree_iterator tmp = *this;
        if(pointee == nullptr){
            pointee = lastElem;
            return tmp;
        }
        pointee = pointee->pre;
        return tmp;
    }
    
    //(in)equality
    bool operator==(const btree_iterator &rhs) const{
        return pointee == rhs.pointee;
    }
    bool operator!=(const btree_iterator &rhs) const{
        return !(*this==rhs);
    }

private:
    typename btree<T>::btreeNode::element *pointee;
    typename btree<T>::btreeNode::element *lastElem;

};

template<typename T>
class const_btree_iterator{
public:
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
    
    const_btree_iterator() : pointee(nullptr), lastElem(nullptr) {}
    const_btree_iterator(const typename btree<T>::btreeNode::element *pointee) : pointee(pointee), lastElem(nullptr) {}
    const_btree_iterator(const typename btree<T>::btreeNode::element *pointee, const typename btree<T>::btreeNode::element lastElem) : pointee(pointee), lastElem(lastElem) {} 

    reference operator*() const{ return pointee->value; }
    pointer operator->() const{ return &(operator*()); }

    //post increment/decrement
    const_btree_iterator& operator++(){
        if(pointee->nxt == nullptr){
            this->lastElem = this->pointee;
        }
        pointee = pointee->nxt;
        return *this;
    }
    const_btree_iterator& operator--(){
        if(pointee == nullptr){
            pointee = lastElem;
            return *this;
        }        
        pointee = pointee->pre;
        return *this;
    }
    //pre increment/decrement
    const_btree_iterator operator++(int){
        if(pointee->nxt == nullptr){
            this->lastElem = this->pointee;
        }
        const_btree_iterator tmp = *this;
        pointee = pointee->nxt;
        return tmp;
    }
    const_btree_iterator operator--(int){
        const_btree_iterator tmp  = *this;
        if(pointee == nullptr){
            pointee = lastElem;
            return tmp;
        }
        pointee = pointee->pre;
        return tmp;
    }

private:
    typename btree<T>::btreeNode::element *pointee;
    typename btree<T>::btreeNode::element *lastElem;

};

#endif
