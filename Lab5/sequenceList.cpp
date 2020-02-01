// FILE: sequenceList.cpp

//Author:	 Dawid Jasionowski
//Date		 9/28/2018 
// CLASS implemented: sequenceList (see sequenceList.h for documentation)
// INVARIANT for the sequenceList ADT:
//   1. The items in the sequenceList are stored on a linked list,
//      in order from the start of the sequenceList at the head of the list;
//   2. The head pointer of the list is stored in the member variable head_ptr;
//   3. The tail pointer of the list is stored in the member variable tail_ptr;
//   4. If there is a current item, then the cursor points to the node that
//      contains this item; otherwise the cursor is nullptr.
//   5. If there is an item before the current item, then the precursor points
//      to the node that contains this item; otherwise the precursor is nullptr.
//   3. The total number of items in the list is stored in the member variable
//      many_nodes.


#include <cassert>  // Provides assert
#include <cstdlib>  // Provides rand, size_t
#include "node.h"  // Provides node and the linked list functions
#include "sequenceList.h"
using namespace std;

// utility function to create a new list from section of an existing list
// Precondition: start_ptr and end_ptr are pointers to nodes on the same
// linked list, with the start_ptr node at or before the end_ptr node.
// Postcondition: head_ptr and tail_ptr are the head and tail pointers
// for a new list that contains the items from start_ptr up to but
// not including end_ptr.  The end_ptr may also be nullptr, in which case
// the new list contains elements from start_ptr to the end of the list.
// Library facilities used: cstdlib
void list_piece(const node* start_ptr, const node* end_ptr, node*& head_ptr,
	node*& tail_ptr) {

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
	start_ptr = start_ptr->link();
	while (start_ptr != end_ptr)
	{
		list_insert(tail_ptr, start_ptr->data());
		tail_ptr = tail_ptr->link();
		start_ptr = start_ptr->link();
	}
}

// default constructor
//   sequenceList( )
//     Postcondition: The sequenceList has been initialized as an empty sequenceList.
//
sequenceList::sequenceList() {
	head_ptr = tail_ptr = cursor = precursor = nullptr;
	many_nodes = 0;
}

// copy constructor ==>TO COMPLETE FOR LAB
//   sequenceList(const sequenceList& source)
//     Postcondition: The sequenceList has been initialized to the source sequenceList.
//
//  NOTE: There are three possible conditions for current/cursor location copy strategies:
//           no current location-->copy list; set cursor and precursor to nullptr
//           current location at head-->copy list; set cursor to head and precursor to nullptr
//           current location not at head-->copy list in pieces: head to cursor and cursor to tail
//                                          set precursor to cursor
sequenceList::sequenceList(const sequenceList& source) {
	// no current location; copy entire list
	if (source.cursor == nullptr) {
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = precursor = nullptr;
	}
	else if (source.precursor == nullptr) {
		// the current item in the source is at the end
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		// reset the cursor and precursor
		cursor = head_ptr;
		precursor = nullptr;
	}
	else {
		// current item in the source is not at head_ptr
		list_piece(source.head_ptr, source.cursor, head_ptr, precursor); // first part of list
		list_piece(source.cursor, nullptr, cursor, tail_ptr);			// second part of list to copy
		precursor->set_link(cursor); // connect first and second
	}
	many_nodes = source.many_nodes;
}

// the destructor
//   ~sequenceList( )
//     Postcondition: The sequenceList has all the nodes removed.
//
sequenceList::~sequenceList() {
	list_clear(head_ptr);
	many_nodes = 0;
}

// method to return item at cursor
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequenceList.
//
sequenceList::value_type sequenceList::current() const {
	assert(is_item());
	return cursor->data();
}

// method to set cursor to beginning of list
//   void start( )
//     Postcondition: The first item on the sequenceList becomes the current item
//     (but if the sequenceList is empty, then there is no current item).
//
void sequenceList::start() {
	precursor = nullptr;
	cursor = head_ptr;
}

// method to advance cursor
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequenceList, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
void sequenceList::advance() {
	assert(is_item());
	precursor = cursor;
	cursor = cursor->link();
	// last item in list
	if (cursor == nullptr)
		precursor = nullptr;
}

// method to insert item before cursor
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequenceList
//     before the current item. If there was no current item, then the new entry
//     has been inserted at the front of the sequenceList. In either case, the newly
//     inserted item is now the current item of the sequenceList.
//
void sequenceList::insert(const value_type& entry) {
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
//     Postcondition: A new copy of entry has been inserted in the sequenceList after
//     the current item. If there was no current item, then the new entry has
//     been attached to the end of the sequenceList. In either case, the newly
//     inserted item is now the current item of the sequenceList.
//
void sequenceList::attach(const value_type& entry) {
	if (is_item())
	{
		//if cursor has an item
		if (cursor->link() == nullptr)
		{
			//if cursor is at the tail
			list_insert(cursor, entry);
			precursor = cursor;
			cursor = cursor->link();
			tail_ptr = cursor;
		}
		else
		{
			//cursor is not the end or in front
			list_insert(cursor, entry);
			precursor = cursor;
			cursor = cursor->link();
		}
	}
	else
	{
		if (many_nodes == 0)
		{
			//list is empty
			list_head_insert(head_ptr, entry);
			precursor = nullptr;
			cursor = head_ptr;
			tail_ptr = head_ptr;
		}
		else
		{
			
			precursor = tail_ptr;
			list_insert(tail_ptr, entry);
			tail_ptr = tail_ptr->link();
			cursor = tail_ptr;
		}
	}

	many_nodes++;
}

// method to remove item at cursor ==>TO COMPLETE FOR LAB
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequenceList, and
//     the item after this (if there is one) is now the new current item.
//
void sequenceList::remove_current() {
	//if there is item 
	if (is_item())
	{
		
		many_nodes--;
		//if there is no item in front
		if (precursor == nullptr)
		{
			//remove item
			list_head_remove(head_ptr);
			cursor = head_ptr;
		}
		else
		{
			
			cursor = cursor->link();
			list_remove(precursor);
		}
	}

}

// method to erase_one matching item ==>TO COMPLETE FOR LAB
//   bool erase_one(const value_type& entry)
//     Precondition: many_nodes > 0
//     Postcondition: If entry was in the sequenceList,
//     then one copy has been removed; otherwise the
//     sequenceList is unchanged.  A true return value
//     indicates that the first copy was removed;
//     false indicates that nothing was removed.
//     Current item is set to first item in sequenceList.
bool sequenceList::erase_one(const value_type& entry) {
	// use flag to keep track of whether item is removed
	bool found = false;
	node* entry_ptr;
	assert(many_nodes > 0);
	entry_ptr = list_search(head_ptr, entry);
	//if entry was found
	if (entry_ptr == head_ptr) {
		found = true;
		

			//entry_ptr->set_data(head_ptr->data());
			list_head_remove(head_ptr);

			
			--many_nodes;

			
			 
	}
			
		
	cursor = head_ptr; //assigning current item to first item
	return found;
}

// overloaded = assignment operator ==>TO COMPLETE FOR LAB
//  NOTE: There are three possible conditions for current/cursor location copy strategies:
//           no current location-->copy list; set cursor and precursor to nullptr
//           current location at head-->copy list; set cursor to head and precursor to nullptr
//           current location not at head-->copy list in pieces: head to cursor and cursor to tail
//                                          set precursor to cursor
void sequenceList::operator =(const sequenceList& source) {
	
	many_nodes = source.many_nodes;
	list_copy(source.head_ptr, head_ptr, tail_ptr);

	node* index_src;
	index_src = source.head_ptr;
	precursor = head_ptr;

	if (source.cursor == nullptr)
	{
		if (source.precursor == nullptr)
		{
			cursor = nullptr;
			precursor = nullptr;
		}
		else
		{
			precursor = tail_ptr;
			cursor = nullptr;
		}
	}
	else
	{
		if (source.precursor == nullptr)
		{
			cursor = head_ptr;
			precursor = nullptr;
		}
		else
		{
			while (index_src != source.precursor)
			{
				index_src = index_src->link();
				precursor = precursor->link();
			}
			cursor = precursor->link();
		}
	}

}

/*
sample run

==========>TEST RESULTS<==========
If you submit this sequenceList class now, you will have
35 points out of the 35 points from this test program.
==========>POINT SUMMARY<==========
Testing insert, attach, and the constant member functions
		POINTS = 3 out of 3
Testing situations where the cursor goes off the sequenceList
		POINTS = 2 out of 2
Testing remove_current member function
		POINTS = 8 out of 8
Testing the copy constructor
		POINTS = 4 out of 4
Testing the assignment operator
		POINTS = 5 out of 5
Testing insert/attach for somewhat larger sequenceLists
		POINTS = 3 out of 3
Testing erase_one member function
		POINTS = 10 out of 10
*/