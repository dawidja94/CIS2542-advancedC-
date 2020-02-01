// FILE: nodeTemplate.h
// PROVIDES: A template class for a nodeTemplate in a linked list, and list manipulation
// functions. The template parameter is the type of the data in each nodeTemplate.
// This file also defines a template class: nodeTemplate_iterator<Item>.
// The nodeTemplate_iterator is a forward iterators with two constructors:
// (1) A constructor (with a nodeTemplate<Item>* parameter) that attaches the iterator
// to the specified nodeTemplate in a linked list, and (2) a default constructor that
// creates a special iterator that marks the position that is beyond the end of a
// linked list. There is also a const_nodeTemplate_iterator for use with
// const nodeTemplate<Item>* .
//
// ALIASES for the nodeTemplate<Item> template class:
//   Each nodeTemplate of the list contains a piece of data and a pointer to the
//   next nodeTemplate. The type of the data (nodeTemplate<Item>::value_type) is the Item type
//   from the template parameter. The type may be any of the built-in C++ classes
//   (int, char, ...) or a class with a default constructor, an assignment
//   operator, and a test for equality (x == y).
// NOTE:
//   Many compilers require the use of the new keyword typename before using
//   the expression nodeTemplate<Item>::value_type. Otherwise
//   the compiler doesn't have enough information to realize that it is the
//   name of a data type.
//
// CONSTRUCTOR for the nodeTemplate<Item> class:
//   nodeTemplate(
//     const Item& init_data = Item(),
//     nodeTemplate* init_link = nullptr
//   )
//     Postcondition: The nodeTemplate contains the specified data and link.
//     NOTE: The default value for the init_data is obtained from the default
//     constructor of the Item. In the ANSI/ISO standard, this notation
//     is also allowed for the built-in types, providing a default value of
//     zero. The init_link has a default value of nullptr.
//
// NOTE about two versions of some functions:
//   The data function returns a reference to the data field of a nodeTemplate and
//   the link function returns a copy of the link field of a nodeTemplate.
//   Each of these functions comes in two versions: a const version and a
//   non-const version. If the function is activated by a const nodeTemplate, then the
//   compiler choses the const version (and the return value is const).
//   If the function is activated by a non-const nodeTemplate, then the compiler choses
//   the non-const version (and the return value will be non-const).
// EXAMPLES:
//    const nodeTemplate<int> *c;
//    c->link( ) activates the const version of link returning const nodeTemplate*
//    c->data( ) activates the const version of data returning const Item&
//    c->data( ) = 42; ... is forbidden
//    nodeTemplate<int> *p;
//    p->link( ) activates the non-const version of link returning nodeTemplate*
//    p->data( ) activates the non-const version of data returning Item&
//    p->data( ) = 42; ... actually changes the data in p's nodeTemplate
//
// MEMBER FUNCTIONS for the nodeTemplate<Item> class:
//   const Item& data( ) const <----- const version
//   and
//   Item& data( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is a reference to the  data from this nodeTemplate.
//
//   const nodeTemplate* link( ) const <----- const version
//   and
//   nodeTemplate* link( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is the link from this nodeTemplate.
//   
//   void set_data(const Item& new_data)
//     Postcondition: The nodeTemplate now contains the specified new data.
//   
//   void set_link(nodeTemplate* new_link)
//     Postcondition: The nodeTemplate now contains the specified new link.
//
// FUNCTIONS in the linked list toolkit:
//   template <class Item>
//   void list_clear(nodeTemplate<Item>*& head_ptr) 
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: All nodeTemplates of the list have been returned to the heap,
//     and the head_ptr is now nullptr.
//
//   template <class Item>
//   void list_copy
//   (const nodeTemplate<Item>* source_ptr, nodeTemplate<Item>*& head_ptr, nodeTemplate<Item>*& tail_ptr)
//     Precondition: source_ptr is the head pointer of a linked list.
//     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
//     a new list that contains the same items as the list pointed to by
//     source_ptr. The original list is unaltered.
//
//   template <class Item>
//   void list_head_insert(nodeTemplate<Item>*& head_ptr, const Item& entry) 
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: A new nodeTemplate containing the given entry has been added at
//     the head of the linked list; head_ptr now points to the head of the new,
//     longer linked list.
//
//   template <class Item>
//   void list_head_remove(nodeTemplate<Item>*& head_ptr) 
//     Precondition: head_ptr is the head pointer of a linked list, with at
//     least one nodeTemplate.
//     Postcondition: The head nodeTemplate has been removed and returned to the heap;
//     head_ptr is now the head pointer of the new, shorter linked list.
//
//   template <class Item>
//   void list_insert(nodeTemplate<Item>* previous_ptr, const Item& entry) 
//     Precondition: previous_ptr points to a nodeTemplate in a linked list.
//     Postcondition: A new nodeTemplate containing the given entry has been added
//     after the nodeTemplate that previous_ptr points to.
//
//   template <class Item>
//   size_t list_length(const nodeTemplate<Item>* head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The value returned is the number of nodeTemplates in the linked
//     list.
//
//   template <class nodeTemplatePtr, class SizeType>
//   nodeTemplatePtr list_locate(nodeTemplatePtr head_ptr, SizeType position)
//   The nodeTemplatePtr may be either nodeTemplate<Item>* or const nodeTemplate<Item>*
//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0.
//     Postcondition: The return value is a pointer that points to the nodeTemplate at
//     the specified position in the list. (The head nodeTemplate is position 1, the
//     next nodeTemplate is position 2, and so on). If there is no such position, then
//     the nullptr pointer is returned.
//
//   template <class Item>
//   void list_remove(nodeTemplate<Item>* previous_ptr) 
//     Precondition: previous_ptr points to a nodeTemplate in a linked list, and this
//     is not the tail nodeTemplate of the list.
//     Postcondition: The nodeTemplate after previous_ptr has been removed from the
//     linked list.
//
//   template <class nodeTemplatePtr, class Item>
//   nodeTemplatePtr list_search
//   (nodeTemplatePtr head_ptr, const Item& target) 
//   The nodeTemplatePtr may be either nodeTemplate<Item>* or const nodeTemplate<Item>*
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The return value is a pointer that points to the first
//     nodeTemplate containing the specified target in its data member. If there is no
//     such nodeTemplate, the nullptr pointer is returned.
//
// DYNAMIC MEMORY usage by the toolkit: 
//   If there is insufficient dynamic memory, then the following functions throw
//   bad_alloc: the constructor, list_head_insert, list_insert, list_copy.

#ifndef MAIN_SAVITCH_nodeTemplate_H  
#define MAIN_SAVITCH_nodeTemplate_H
#include <cstdlib>   // Provides size_t
#include <iterator>  // Provides STL iterator and forward_iterator_tag

template <class Item>
class nodeTemplate
{
public:
	// ALIAS-->so template parameter Item can be used outside class
	using value_type = Item;
	// CONSTRUCTOR
	nodeTemplate(const Item& init_data = Item(), nodeTemplate* init_link = nullptr)
	{
		data_field = init_data; link_field = init_link;
	}
	// MODIFICATION MEMBER FUNCTIONS
	Item& data() { return data_field; }
	nodeTemplate* link() { return link_field; }
	void set_data(const Item& new_data) { data_field = new_data; }
	void set_link(nodeTemplate* new_link) { link_field = new_link; }
	// CONST MEMBER FUNCTIONS
	const Item& data() const { return data_field; }
	const nodeTemplate* link() const { return link_field; }
private:
	Item data_field;
	nodeTemplate *link_field;
};

// FUNCTIONS to manipulate a linked list:
template <class Item>
void list_clear(nodeTemplate<Item>*& head_ptr);

template <class Item>
void list_copy
(const nodeTemplate<Item>* source_ptr, nodeTemplate<Item>*& head_ptr, nodeTemplate<Item>*& tail_ptr);

template <class Item>
void list_head_insert(nodeTemplate<Item>*& head_ptr, const Item& entry);

template <class Item>
void list_head_remove(nodeTemplate<Item>*& head_ptr);

template <class Item>
void list_insert(nodeTemplate<Item>* previous_ptr, const Item& entry);

template <class Item>
std::size_t list_length(const nodeTemplate<Item>* head_ptr);

template <class nodeTemplatePtr, class SizeType>
nodeTemplatePtr list_locate(nodeTemplatePtr head_ptr, SizeType position);

template <class Item>
void list_remove(nodeTemplate<Item>* previous_ptr);

template <class nodeTemplatePtr, class Item>
nodeTemplatePtr list_search(nodeTemplatePtr head_ptr, const Item& target);

// FORWARD ITERATORS to step through the nodeTemplates of a linked list
// A nodeTemplate_iterator of can change the underlying linked list through the
// * operator, so it may not be used with a const nodeTemplate. The
// nodeTemplate_const_iterator cannot change the underlying linked list
// through the * operator, so it may be used with a const nodeTemplate.
// WARNING:
// This classes use std::iterator as its base class;
// Older compilers that do not support the std::iterator class can
// delete everything after the word iterator in the second line:

template <class Item>
class nodeTemplate_iterator
	: public std::iterator<std::forward_iterator_tag, Item>
{
public:
	nodeTemplate_iterator(nodeTemplate<Item>* initial = nullptr)
	{
		current = initial;
	}
	Item& operator *() const
	{
		return current->data();
	}
	nodeTemplate_iterator& operator ++() // Prefix ++
	{
		current = current->link();
		return *this;
	}
	nodeTemplate_iterator operator ++(int) // Postfix ++
	{
		nodeTemplate_iterator original(current);
		current = current->link();
		return original;
	}
	bool operator ==(const nodeTemplate_iterator other) const
	{
		return current == other.current;
	}
	bool operator !=(const nodeTemplate_iterator other) const
	{
		return current != other.current;
	}
private:
	nodeTemplate<Item>* current;
};

template <class Item>
class const_nodeTemplate_iterator
	: public std::iterator<std::forward_iterator_tag, const Item>
{
public:
	const_nodeTemplate_iterator(const nodeTemplate<Item>* initial = nullptr)
	{
		current = initial;
	}
	const Item& operator *() const
	{
		return current->data();
	}
	const_nodeTemplate_iterator& operator ++() // Prefix ++
	{
		current = current->link();
		return *this;
	}
	const_nodeTemplate_iterator operator ++(int) // Postfix ++
	{
		const_nodeTemplate_iterator original(current);
		current = current->link();
		return original;
	}
	bool operator ==(const const_nodeTemplate_iterator other) const
	{
		return current == other.current;
	}
	bool operator !=(const const_nodeTemplate_iterator other) const
	{
		return current != other.current;
	}
private:
	const nodeTemplate<Item>* current;
};

#include "nodeTemplateToolkit.h"
#endif
