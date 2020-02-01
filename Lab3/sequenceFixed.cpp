// Dawid Jasionowski
// 9/12/2018

// FILE: sequenceFixed.cpp
// CLASS IMPLEMENTED: sequenceFixed (see sequenceFixed1.h for documentation)
// INVARIANT for the sequenceFixed ADT:
//   1. The number of items in the sequenceFixed is in the member variable used;
//   2. For an empty sequenceFixed, we do not care what is stored in any of data;
//      for a non-empty sequenceFixed the items in the sequenceFixed are stored in
//      sequenceFixed order from data[0] through data[used-1], and we don't care
//      what's in the rest of data.
//   3. If there is a current item, then that item is in data[current_index];
//      Otherwise, current_index equals used.

// Taken from Data Structures and Other Objects 
// Using C++ by Michael Main and Walter Savitch
// Modifications by CREngland
//

#include <cassert>  // Provides assert
#include "sequenceFixed.h"
using namespace std;

// CONSTRUCTOR for the sequenceFixed class:
//   sequenceFixed( )
//     Postcondition: The sequenceFixed has been initialized as an empty sequenceFixed.
sequenceFixed::sequenceFixed( ): used(0), current_index(0) {}


//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequenceFixed.
sequenceFixed::size_type sequenceFixed::size() const 
{
	return used;
}

//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
bool sequenceFixed::is_item() const 
{
	// see if current_index is valid
	return (current_index < used);
}

//   void start( )
//     Postcondition: The first item on the sequenceFixed becomes the current item
//     (but if the sequenceFixed is empty, then there is no current item).
void sequenceFixed::start( ) 
{
    current_index = 0;
}

//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequenceFixed.
sequenceFixed::value_type sequenceFixed::current() const 
{
	// ensure that current_index is valid
	assert(is_item());
	return data[current_index];
}

//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequenceFixed, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
void sequenceFixed::advance( ) 
{
	// ensure that current_index is valid
    assert(is_item( ));
    current_index++;
}

//   void insert(const value_type& entry)
//     Precondition: size( ) < CAPACITY.
//     Postcondition: A new copy of entry has been inserted in the sequenceFixed
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequenceFixed. In either case, the newly
//     inserted item is now the current item of the sequenceFixed.
// SEE TEXTBOOK PAGES 131-132 FOR EXPLANATION
void sequenceFixed::insert(const value_type& entry) {
    // ensure that there is available space for new item
    assert(size( ) < CAPACITY);

    // If there is no current item,
	// then set current_index to the front so that
    // the new entry will be placed at the front of the array.
    if (!is_item( ))
        current_index = 0;

    // Starting at end of relevant items, shift items over to make room
    for (size_type i = used; i > current_index; i--)
        data[i] = data[i-1];
	// insert new entry at current_index
    data[current_index] = entry;
	// increment number of items used
    used++;
}

//     Precondition: size( ) < CAPACITY.
//     Postcondition: A new copy of entry has been inserted in the sequenceFixed after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequenceFixed. In either case, the newly
//     inserted item is now the current item of the sequenceFixed.
void sequenceFixed::attach(const value_type& entry) {
	if (used > 0)
	{
		value_type temp = entry, newTemp;
		for (size_type i = current_index + 1; i < used; i++)
		{
			newTemp = data[i];
			data[i] = temp;
			temp = newTemp;
		}
		data[used] = temp;
		current_index += 1;
		used += 1;
	}
	else
	{
		data[current_index] = entry;
		used += 1;
	}
}

//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequenceFixed, and the
//     item after this (if there is one) is now the new current item.
// SEE TEXTBOOK PAGES 130-131 FOR EXPLANATION
void sequenceFixed::remove_current( ) {
	//ensure that current_index is valid
	if (is_item()) {
		//
		for (size_type i = current_index; i < used; i++)
		{
			data[i] = data[i + 1];
		}
	}	
		used--;
	
	
}

//   bool erase_one(const value_type& entry)
//     Precondition: used > 0
//     Postcondition: If entry was in the sequenceFixed,
//     then one copy has been removed; otherwise the
//     sequenceFixed is unchanged.  A true return value
//     indicates that the first copy was removed;
//     false indicates that nothing was removed.
//     Current item is set to first item in sequenceFixed.
bool sequenceFixed::erase_one(const value_type& entry) {

	// use flag to keep track of whether item is removed
	bool found = false;
	for (size_type i = 0; i < used; i++)
		// see if item in array and value equal to entry
	if (data[i] == entry) {
		//if found return true
		found = true;

		current_index = 0;
		//remove item by using the function remove_current();
		remove_current();
		break;
	}
	

	return found;
}