// File: list.h
// List<T> template class
// From Wittenberg, Data Structures and Algorithms in C++ Pocket Primer
// Ch. 3

#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <algorithm>

template <typename T>
class List {  // uppercase L to distinguish from STL list
   private: // private type declarations
     // #include "dnode.h"  // doubly-linked Node struct
   
      template <typename U>  // iterator template class
      class Iter {
	 private:
	    Node *curr;
	    friend class List<T>;  // allows List<T> access to curr
	 public:
	    Iter(Node *p) : curr(p) {}
	    U& operator *  () const { return curr->data; }
	    U* operator -> () const { return &(curr->data); }
	    bool operator == (const Iter<U>& other) const
	    { return curr == other.curr; }
	    bool operator != (const Iter<U>& other) const
	    { return curr != other.curr; }
	    Iter<U>& operator ++ ()         // prefix ++
	    { curr = curr->rlink; return *this; }
	    Iter<U> operator ++ (int)       // postfix ++
	    { Iter<U> result = Iter<U>(curr); curr = curr->rlink;
	      return result; }
      };  // end Iter private inner class
      
   public:
      // Iterator types and operations
      typedef Iter<T> iterator;
      typedef Iter<const T> const_iterator;
      iterator begin()       {return iterator(first);}
      const_iterator begin() const {return const_iterator(first);}
      iterator end()       {return iterator(nullptr);}
      const_iterator end() const {return const_iterator(nullptr);}

      // Default constructor, empty list
      List() : count(0), first(nullptr), last(nullptr) {}

      // C++11 initializer list constructor
      // C++11 constructor forwarding initializes attributes
      List(std::initializer_list<T> init) : List()
      {
	for(auto item: init) // range-based for-loop, uses iterators
	                     // under the covers
	  push_back (item);

      }
   
      // Copy constructor
      List(const List<T>& other) : List()
      {
	for (auto item: other) // 
	  push_back (item);
      }
   
      // Destructor
      ~List()
      {
	 // Delete all nodes
	 clear();
      }
      
      // Assignment
      List<T>& operator = (const List<T>& other)
      {
	 // DIFFERENT THAN IN THE TEXTBOOK!!
	 // make a copy of other
	 List<T> copy(other);
	 // swap the contents of this and the copy
	 std::swap(count, copy.count);
	 std::swap(first, copy.first);
	 std::swap(last, copy.last);
	 // on return, destructor will be called on copy variable
	 // which will delete the old data
	 return *this;
      }

      // Accessors
      int size() const { return count; }
      bool empty() const { return size() == 0; }
      // Need const and non-const version for front/back
      T& front()       { return first->data; }
      const T& front() const { return first->data; }
      T& back()       { return last->data; }
      const T& back() const { return last->data; }

      // Insert in front of node at pos, returns iterator to new node
      iterator insert(iterator pos, const T& value)
      {
	// create new node for value
	Node *new_item = new Node (value);
	//node's right link is the node pointed to by pos
	new_item->rlink = pos.curr;
	//Hook up node;s left link
	// check if pos is nullptr
	if(pos.curr == nullptr) // inserting at the end
	  new_item->llink = last;
	else  // node's left link is pos' node;s left link
	  new_item->llink = pos.curr->llink;
	// hook up the link to the new node
	if(new_item->rlink != nullptr)
	  new_item->rlink->llink = new_item;
	// {
	//   Node *right_node = new_item->rlink;
	//   right_node->llink = new_item;
	// }
	
	if(new_item->llink != nullptr)
	  new_item->llink->rlink = new_item;
	// Adjust firstor last if inserted at an end
	if(pos == begin())
	  first = new_item;
	if(pos == end())
	  last = new_item;
	// cout the new node
	count++;
	// return iterator with new node's pointer
	return iterator(new_item);
      }

      // Delete node at pos, returns iterator to next item
      iterator erase(iterator pos)
      {
	// result is iterator to the next item
	iterator result = iterator(pos.curr->rlink);
	// check if first element
	if (pos.curr == first) /// first element
	  first = first->rlink; // point first to new first element
	else
	  // right link of left node points to the right node
	  pos.curr->llink->rlink = pos.curr->rlink;
	//check if last elemnt
	if(pos.curr == last)
	  last = last->llink;
	else
	  // left link of right node points to the left node
	  pos.curr->rlink->llink = pos.curr->llink;
	// make sure the ends are nullptr, if there are nodes
	if(first != nullptr)
	  first->llink = last->rlink = nullptr;
	// "uncount" the node
	count--;
	// delete the pos node
	delete pos.curr;
	// return iterator to the next node
	return result;
	
      }

      // Other modifiers
      void push_front(const T& value) { insert(begin(), value); }
      void push_back(const T& value)  { insert(end(), value); }
      void pop_front() { erase(begin()); }
      void pop_back()  { erase(iterator(last)); }

      // Delete all nodes, reinitialize attributes
      void clear()
      {
	Node *ptr = first;
	while (ptr != nullptr)
	{
	  // first will point to the node to be deleted
	  ptr = ptr->rlink; // "increament" to next node
	  delete first; // delete the first node
	  first = ptr; // go to the new first node
	}

	// Reset last and count
	last = nullptr;
	count = 0;
      }

   private:
      int count;      // number of nodes in list
      Node *first;    // pointer to first node
      Node *last;     // pointer to last node
};  // end List class

#endif
