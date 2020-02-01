// FILE: sequenceTemp.h
// CLASS PROVIDED: sequenceTemp 
// COPYRIGHT Main and Savitch with modifications by CREngland
// This is called "sequenceTemp" because some students already implemented
// sequenceDynamic (with a dynamic array) and sequenceFixed (with a fixed array).
//
// ALIASES and MEMBER CONSTANTS for the sequenceTemp class:
//   alias ____ value_type
//     sequenceTemp::value_type is the data type of the items in the sequenceTemp. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   alias ____ size_type
//     sequenceTemp::size_type is the data type of any variable that keeps track of
//     how many items are in a sequenceTemp.
//

// VALUE SEMANTICS for the sequenceTemp class:
//    Assignments and the copy constructor may be used with sequenceTemp objects.

#ifndef MAIN_SAVITCH_sequenceTemp_H
#define MAIN_SAVITCH_sequenceTemp_H
#include <cstdlib>  // Provides size_t
#include <cassert>  // Provides assert
#include "nodeTemplate.h"  // Provides node class
template <class Item>
class sequenceTemp
{
public:
	// ALIASES
	using value_type = Item;
	using size_type = std::size_t;

	// CONSTRUCTORS and DESTRUCTOR
	sequenceTemp();
	sequenceTemp(const sequenceTemp& source);
	~sequenceTemp();

	// CONSTANT MEMBER FUNCTIONS
	//   size_type size( ) const
	//     Postcondition: The return value is the number of items in the sequenceTemp.
	//
	size_type size() const { return many_nodes; }

	//   bool is_item( ) const
	//     Postcondition: A true return value indicates that there is a valid
	//     "current" item that may be retrieved by activating the current
	//     member function (listed below). A false return value indicates that
	//     there is no valid current item.
	//
	bool is_item() const { return (cursor != nullptr); }
	value_type current() const;

	// MODIFICATION MEMBER FUNCTIONS
	void start();
	void advance();
	void insert(const Item& entry);
	void attach(const Item& entry);
	void remove_current();
	bool erase_one(const Item& entry);
	void operator =(const sequenceTemp& source);
	void operator +=(const sequenceTemp& addend);

private:
	nodeTemplate<Item> * head_ptr;
	nodeTemplate<Item> *tail_ptr;
	nodeTemplate<Item> *cursor;
	nodeTemplate<Item> *precursor;
	size_type many_nodes;
};

// NONMEMBER FUNCTIONS for the bagTemplate class: 
template <class Item>
sequenceTemp<Item> operator +(const sequenceTemp<Item>& s1, const sequenceTemp<Item>& s2);

#endif

// utility function to create a new list from section of an existing list
// Precondition: start_ptr and end_ptr are pointers to nodes on the same
// linked list, with the start_ptr node at or before the end_ptr node.
// Postcondition: head_ptr and tail_ptr are the head and tail pointers
// for a new list that contains the items from start_ptr up to but
// not including end_ptr.  The end_ptr may also be nullptr, in which case
// the new list contains elements from start_ptr to the end of the list.
// Library facilities used: cstdlib
template <class Item>
void list_piece(const nodeTemplate<Item>* start_ptr, const nodeTemplate<Item>* end_ptr, nodeTemplate<Item>*& head_ptr, nodeTemplate<Item>*& tail_ptr) {

	head_ptr = nullptr;
	tail_ptr = nullptr;

	// Handle the case of the empty list.
	if (start_ptr == end_ptr)
		return;

	// Make the head node for the newly created list, and put data in it.
	list_head_insert(head_ptr, start_ptr->data());
	// single node new list: set tail to head
	tail_ptr = head_ptr;

	// Copy the rest of the nodes one at a time, adding at the tail of new list.

	// Move to next node in list to copy
	start_ptr = start_ptr->link();
	// copy nodes from existing list to new list
	// building list from first to last nodes
	while (start_ptr != end_ptr)
	{
		// insert item to copy after tail of new list
		list_insert(tail_ptr, start_ptr->data());
		// reset tail of new list to copied item
		tail_ptr = tail_ptr->link();
		// reset start to next node in list to copy
		start_ptr = start_ptr->link();
	}
}

// default constructor
//   sequenceTemp( )
//     Postcondition: The sequenceTemp has been initialized as an empty sequenceTemp.
//
template <class Item>
sequenceTemp<Item>::sequenceTemp() {
	head_ptr = tail_ptr = cursor = precursor = nullptr;
	many_nodes = 0;
}

// copy constructor
//   sequenceTemp(const sequenceTemp& source)
//     Postcondition: The sequenceTemp has been initialized to the source sequenceTemp.
//
//  NOTE: There are three possible conditions for current/cursor location copy strategies:
//           no current location-->copy list; set cursor and precursor to nullptr
//           current location at head-->copy list; set cursor to head and precursor to nullptr
//           current location not at head-->copy list in pieces: head to cursor and cursor to tail
//                                          set precursor to cursor
template <class Item>
sequenceTemp<Item>::sequenceTemp(const sequenceTemp& source) {
	if (source.cursor == nullptr)
	{   // There is no current item in the source list:
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = precursor = nullptr;
	}
	else if (source.precursor == nullptr)
	{   // The current item in the source is at its head:
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = head_ptr;
		precursor = nullptr;
	}
	else
	{   // The current item in the source is not at its head:
		list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
		list_piece(source.cursor, (nodeTemplate<Item>*)NULL, cursor, tail_ptr);
		precursor->set_link(cursor);
	}
	many_nodes = source.many_nodes;
}

// the destructor
//   ~sequenceTemp( )
//     Postcondition: The sequenceTemp has all the nodes removed.
//
template <class Item>
sequenceTemp<Item>::~sequenceTemp() {
	list_clear(head_ptr);
	many_nodes = 0;
}

// method to return item at cursor
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequenceTemp.
//
template <class Item>
Item sequenceTemp<Item>::current() const {
	assert(is_item());
	return cursor->data();
}

// method to set cursor to beginning of list
//   void start( )
//     Postcondition: The first item on the sequenceTemp becomes the current item
//     (but if the sequenceTemp is empty, then there is no current item).
//
template <class Item>
void sequenceTemp<Item>::start() {
	precursor = nullptr;
	cursor = head_ptr;
}

// method to advance cursor
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequenceTemp, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
template <class Item>
void sequenceTemp<Item>::advance() {
	assert(is_item());
	precursor = cursor;
	cursor = cursor->link();
	// last item in list
	if (cursor == nullptr)
		precursor = nullptr;
}

// method to insert item before cursor
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequenceTemp
//     before the current item. If there was no current item, then the new entry
//     has been inserted at the front of the sequenceTemp. In either case, the newly
//     inserted item is now the current item of the sequenceTemp.
//
template <class Item>
void sequenceTemp<Item>::insert(const Item& entry) {
	// at front of list, if no prior node
	if (precursor == nullptr)
	{   // The new entry goes at the front:
		list_head_insert(head_ptr, entry);
		cursor = head_ptr;
		// There were no other nodes.
		if (tail_ptr == nullptr)
			tail_ptr = head_ptr;
	}
	else
	{   // The new entry goes between precursor and cursor,
		// and the cursor is set to point at this new entry.
		list_insert(precursor, entry);
		cursor = precursor->link();
	}
	++many_nodes;
}

// method to attach item after cursor ==>TO COMPLETE FOR LAB
//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequenceTemp after
//     the current item. If there was no current item, then the new entry has
//     been attached to the end of the sequenceTemp. In either case, the newly
//     inserted item is now the current item of the sequenceTemp.
//
template <class Item>
void sequenceTemp<Item>::attach(const Item& entry) {
	// First node of the list
	if (tail_ptr == nullptr)
		insert(entry);
	else if (cursor == nullptr)  // no current item
	{   // The new entry goes after the current tail:
		list_insert(tail_ptr, entry);
		precursor = tail_ptr;
		// current item is tail
		cursor = tail_ptr = precursor->link();
		++many_nodes;
	}
	else
	{   // The new entry goes after the current cursor:
		list_insert(cursor, entry);
		precursor = cursor;
		// set current to new node
		cursor = precursor->link();
		// if added at end, reset tail to current
		if (tail_ptr == precursor)
			tail_ptr = cursor;
		++many_nodes;
	}
}

// method to remove item at cursor
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequenceTemp, and
//     the item after this (if there is one) is now the new current item.
//
template <class Item>
void sequenceTemp<Item>::remove_current() {
	assert(is_item());
	if (cursor == head_ptr)
	{   // Remove the front node:
		list_head_remove(head_ptr);
		cursor = head_ptr;
		if (cursor == nullptr)
			tail_ptr = nullptr; // No more nodes on the list.
	}
	else
	{   // Remove a node that is not at the head:
		list_remove(precursor);
		// reset cursor to next item
		cursor = precursor->link();
		// end of list
		if (cursor == nullptr)
		{   // We just removed the old tail node:
			tail_ptr = precursor;
			// invalid cursor
			precursor = nullptr;
		}
	}
	--many_nodes;
}

// method to erase_one matching item
//   bool erase_one(const value_type& entry)
//     Precondition: many_nodes > 0
//     Postcondition: If entry was in the sequenceTemp,
//     then one copy has been removed; otherwise the
//     sequenceTemp is unchanged.  A true return value
//     indicates that the first copy was removed;
//     false indicates that nothing was removed.
//     Current item is set to first item in sequenceTemp.
template <class Item>
bool sequenceTemp<Item>::erase_one(const Item& entry) {
	// ensure items in bag
	assert(many_nodes > 0);
	// use flag to keep track of whether item is removed
	bool found = false;
	// set cursor to beginning
	start();
	// loop through items until entry found and remove item
	while (is_item()) {
		if (current() == entry) {
			remove_current();
			found = true;
			break;  // only remove first item
		}
		advance();  // go to next item in container
	}

	// position current to first item
	start();
	// return found flag
	return found;
}

// overloaded = assignment operator
//  NOTE: There are three possible conditions for current/cursor location copy strategies:
//           no current location-->copy list; set cursor and precursor to nullptr
//           current location at head-->copy list; set cursor to head and precursor to nullptr
//           current location not at head-->copy list in pieces: head to cursor and cursor to tail
//                                          set precursor to cursor
template <class Item>
void sequenceTemp<Item>::operator =(const sequenceTemp<Item>& source) {
	// Check for possible self-assignment
	if (this == &source)
		return;
	// release old nodes
	list_clear(head_ptr);
	// copy list
	if (source.cursor == nullptr)
	{   // There is no current item in the source list:
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = precursor = nullptr;
	}
	else if (source.precursor == nullptr)
	{   // The current item in the source is at its head:
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = head_ptr;
		precursor = nullptr;
	}
	else
	{   // The current item in the source is not at its head:
		// copy from head to current
		list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
		// copy from current to tail
		list_piece(source.cursor, (nodeTemplate<Item>*)NULL, cursor, tail_ptr);
		precursor->set_link(cursor);
	}
	many_nodes = source.many_nodes;
}

// Overloaded += operator (as member function)
// items added to end of container; cursor and precursor not modified
template <class Item>
void sequenceTemp<Item>::operator +=(const sequenceTemp<Item>& addend) {
	if (addend.many_nodes > 0) {
		node *copy_head_ptr, *copy_tail_ptr;
		// copy all items from addend
		list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);
		// current list is empty
		if (head_ptr == nullptr) {
			// copied list becomes new list
			head_ptr = copy_head_ptr;
			tail_ptr = copy_tail_ptr;
		}
		else {
			// attach copied list to end of current sequenceTemp container
			tail_ptr->set_link(copy_head_ptr);
			tail_ptr = copy_tail_ptr;
		}
		// increment number of nodes
		many_nodes += addend.many_nodes;
	}
}

// Overloaded + operator (as free function)
template <class Item>
sequenceTemp<Item> operator +(const sequenceTemp<Item>& s1, const sequenceTemp<Item>& s2) {
	// create new sequenceTemp from existing sequenceTemp
	sequenceTemp result(s1);
	// add items from second sequenceTemp
	result += s2;
	return result;
}

