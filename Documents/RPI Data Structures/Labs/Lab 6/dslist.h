//
//  dslist.h
//  lab6
//
//  Created by Michelle Psaras on 2/19/19.
//  Copyright © 2019 Jonathan Psaras. All rights reserved.
//

#ifndef dslist_h_
#define dslist_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
    Node() : next_(NULL), prev_(NULL) {}
    Node(const T& v) : value_(v), next_(NULL), prev_(NULL) {}
    
    // REPRESENTATION
    T value_;
    Node<T>* next_;
    Node<T>* prev_;
};

// A "forward declaration" of this class is needed
template <class T> class dslist;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T> class list_iterator {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    list_iterator(Node<T>* p=NULL, Node<T>* g) : ptr_(p) {tailG_ = g;}
    // NOTE: the implicit compiler definitions of the copy constructor,
    // assignment operator, and destructor are correct for this class
    
    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->value_;  }
    
    // increment & decrement operators
    list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
        ptr_ = ptr_->next_;
        return *this;
    }
    list_iterator<T> operator++(int) { // post-increment, e.g., iter++
        list_iterator<T> temp(*this, *this);
        ptr_ = ptr_->next_;
        return temp;
    }
    list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
		if (ptr_ == NULL)
			ptr_ = tailG_;
        ptr_ = ptr_->prev_;
        return *this;
    }
    list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
        list_iterator<T> temp(*this, *this);
		if (ptr_ == NULL){
			ptr_ = tailG_;
			return *this;
		}
        ptr_ = ptr_->prev_;
        return temp;
    }
    // the dslist class needs access to the private ptr_ member variable
    friend class dslist<T>;
    
    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const {
        return ptr_ == r.ptr_; }
    bool operator!=(const list_iterator<T>& r) const {
        return ptr_ != r.ptr_; }
    
private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
	Node<T>* tailG_ = ; //ptr to tail of the node
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T> class dslist {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    dslist() : head_(NULL), tail_(NULL), size_(0) {}
    dslist(const dslist<T>& old) { copy_list(old); }
    dslist& operator= (const dslist<T>& old);
    ~dslist() { destroy_list(); }
    
    typedef list_iterator<T> iterator;
    
    // simple accessors & modifiers
    unsigned int size() const { return size_; }
    bool empty() const { return head_ == NULL; }
    void clear() { destroy_list(); }
    
    // read/write access to contents
    const T& front() const { return head_->value_;  }
    T& front() { return head_->value_; }
    const T& back() const { return tail_->value_; }
    T& back() { return tail_->value_; }
    
    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();
    
    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(NULL); }
	iterator tail() { return iterator(tail_) ;}
    
private:
    // private helper functions
    void copy_list(const dslist<T>& old);
    void destroy_list();
    
    //REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
	
    unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
dslist<T>& dslist<T>::operator= (const dslist<T>& old) {
    // check for self-assignment
    if (&old != this) {
        destroy_list();
        copy_list(old);
    }
    return *this;
}

template <class T>
void dslist<T>::push_front(const T& v) {
    Node<T>* newp = new Node<T>(v);
    if (size_ == 0){
        head_ = tail_ = newp;
    }
    else{
        newp -> next_ = head_;
        head_ = newp;
    }
    size_++;
}

template <class T>
void dslist<T>::pop_front() {
    if (size_ == 0){
        std::cerr << "Empty stack! Cannot execute pop_front function." << std::endl;
        exit(0);
    }
    Node<T>* cur = head_;
    Node<T>* tmp = cur -> next_;
    head_ = tmp;
    delete cur;
    --size_;
}

template <class T>
void dslist<T>::push_back(const T& v) {
    Node<T>* newp = new Node<T>(v);
    if (!tail_){
        head_ = tail_ = newp;
    }
    else{
        newp->prev_ = tail_;
        tail_->next_ = newp;
        tail_ = newp;
    }
    size_++;
}

template <class T>
void dslist<T>::pop_back() {
    if (size_ == 0){
        std::cerr << "Empty stack! Cannot execute pop_back function." << std::endl;
        exit(0);
    }
    else if (head_ == tail_){
        delete head_;
        head_ = tail_ = NULL;
    }
    else{
        Node<T>* cur = tail_;
        tail_ = cur -> prev_;
        tail_ -> next_ = NULL;
        delete cur;
    }
    --size_;
}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (dslist<T>& left, dslist<T>& right) {
    if (left.size() != right.size()) return false;
    typename dslist<T>::iterator left_itr = left.begin();
    typename dslist<T>::iterator right_itr = right.begin();
    // walk over both lists, looking for a mismatched value
    while (left_itr != left.end()) {
        if (*left_itr != *right_itr) return false;
        left_itr++; right_itr++;
    }
    return true;
}

template <class T>
bool operator!= (dslist<T>& left, dslist<T>& right){ return !(left==right); }

template <class T> typename dslist<T>::iterator dslist<T>::erase(iterator itr) {
    assert (size_ > 0);
    --size_;
    iterator result(itr.ptr_->next_);
    // One node left in the list.
    if (itr.ptr_ == head_ && head_ == tail_) {
        head_ = tail_ = 0;
    }
    // Removing the head in a list with at least two nodes
    else if (itr.ptr_ == head_) {
        head_ = head_->next_;
        head_->prev_ = 0;
    }
    // Removing the tail in a list with at least two nodes
    else if (itr.ptr_ == tail_) {
        tail_ = tail_->prev_;
        tail_->next_ = 0;
    }
    // Normal remove
    else {
        itr.ptr_->prev_->next_ = itr.ptr_->next_;
        itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    }
    delete itr.ptr_;
    return result;
}


template <class T> typename dslist<T>::iterator dslist<T>::insert(iterator itr, const T& v) {
    ++size_ ;
    Node<T>* p = new Node<T>(v);
    p->prev_ = itr.ptr_->prev_;
    p->next_ = itr.ptr_;
    itr.ptr_->prev_ = p;
    if (itr.ptr_ == head_)
        head_ = p;
    else
        p->prev_->next_ = p;
    return iterator(p);
}


template <class T>
void dslist<T>::copy_list(const dslist<T>& old) {
    size_ = old.size_;
    // Handle the special case of an empty list.
    if (size_ == 0) {
        head_ = tail_ = 0;
        return;
    }
    // Create a new head node.
    head_ = new Node<T>(old.head_->value_);
    // tail_ will point to the last node created and therefore will move
    // down the new list as it is built
    tail_ = head_;
    // old_p will point to the next node to be copied in the old list
    Node<T>* old_p = old.head_->next_;
    // copy the remainder of the old list, one node at a time
    while (old_p) {
        tail_->next_ = new Node<T>(old_p->value_);
        tail_->next_->prev_ = tail_;
        tail_ = tail_->next_;
        old_p = old_p->next_;
    }
}

template <class T>
void dslist<T>::destroy_list() {
    Node<T>* ptr = head_;
    while (ptr != NULL){
        Node<T>* temp = ptr -> next_;
        delete ptr;
        ptr = temp;
        size_--;
    }
    head_ = NULL;
    tail_ = NULL;
}

#endif
