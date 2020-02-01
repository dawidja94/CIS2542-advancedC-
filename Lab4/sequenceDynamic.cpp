
// Author:	Dawid Jasionowski
// Date:	09/20/2018

// FILE:              sequenceDynamic.cpp
// CLASS IMPLEMENTED: sequenceDynamic (See sequenceDynamic.h for documentation)
// INVARIANT for the sequenceDynamic ADT (i.e. verbalization of rules governing
//   private member function behavior):
//   1. The number of value_types in the sequenceDynamic is in the member variable used
//      (i.e. used = 0 means the sequenceDynamic is empty).
//   2. For an empty sequenceDynamic, we do not care what is stored in any of the
//      array data.  For a non-empty sequenceDynamic, the value_types in the sequenceDynamic are
//      stored in strictly maintained order in data[0] through
//      data[used].  We don't care what's in the rest of data (so don't
//      need to initialize data in the constructor).
//   3. To maintain strict order, current_index is used to keep track
//      of current location in data; when current_index is used-1,
//      we're at the last place in the array.  Also whenever current_index
//      is greater than or equal to used, there is no current value_type.
//   4. capacity keeps track of the current capacity of the array pointed
//      to by data; capacity starts out with the value initial_capacity
//      and is changed by resize as needed (whenever used is greater than
//      or equal to capacity).

#include <cassert>   // Provides assert
#include "sequenceDynamic.h"
using namespace std;

//   sequenceDynamic(size_t initial_capacity = DEFAULT_CAPACITY)
//     Postcondition: The sequenceDynamic has been initialized as an empty sequenceDynamic.
//     The insert/attach functions will work efficiently (without allocating
//     new memory) until this capacity is reached.
//
sequenceDynamic::sequenceDynamic(size_type initial_capacity) {
	// create sequence of initial_capacity
    data = new value_type[initial_capacity];
    capacity = initial_capacity;
    used = 0;
    current_index = 0;
}

//   sequenceDynamic(const sequenceDynamic& source)
//     Postcondition: The sequenceDynamic has capacity set to the sequenceDynamic source parameter.
//     The sequenceDynamic object is filled with data members given by the sequenceDynamic source
//     parameter.
//
sequenceDynamic::sequenceDynamic(const sequenceDynamic& source) {
	//allocate the memory to the same as source
	data = new value_type[source.capacity];
	//set capacity to source capacity
	capacity = source.capacity;
	//set number used to source used
	used = source.used;
	current_index = source.current_index;
	for (size_type i = 0; i < used; i++)
		data[i] = source.data[i];
	
}

//   ~sequenceDynamic()
//     Postcondition: dynamically allocated memory for data member has been released
//
sequenceDynamic::~sequenceDynamic() {
	// release memory
    delete [ ] data;
}

//   size_type count(const value_type& target) const
//     Postcondition: Return value is number of times target is in the sequenceDynamic
//
sequenceDynamic::size_type sequenceDynamic::size() const {
	return used;
}

//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
bool sequenceDynamic::is_item() const {
	// see if current_index is valid
	return (current_index < used);
}

//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequenceDynamic.
//
sequenceDynamic::value_type sequenceDynamic::current() const {
	// ensure that current_index is valid before returning value
	assert(is_item());
	return data[current_index];
}

//   void resize(size_type new_capacity)
//     Postcondition: The sequenceDynamic's current capacity is changed to the
//     new_capacity (but not less that the number of items already on the
//     list). The insert/attach functions will work efficiently (without
//     allocating new memory) until this new capacity is reached.
//
void sequenceDynamic::resize(size_type new_capacity) {
	value_type* larger_array;
	//if the memory is the right size
	if (new_capacity == capacity)
	{
		return;
	}
	if (new_capacity < used)
		new_capacity = used;
	else
	{
		larger_array = new value_type[new_capacity];
		//copy to larger_array
		for (size_type i = 0; i < used; i++)
			larger_array[i] = data[i];
		//release data
		delete[] data;
		//reassign
		data = larger_array;
		//reset capacity
		capacity = new_capacity;
	}
	
}

//   void start( )
//     Postcondition: The first item on the sequenceDynamic becomes the current item
//     (but if the sequenceDynamic is empty, then there is no current item).
//
void sequenceDynamic::start() {
    current_index = 0;
}

//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequenceDynamic, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
void sequenceDynamic::advance() {
	// ensure that current_index is valid
    assert(is_item());
    current_index++;
}

//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequenceDynamic
//     before the current item. If there was no current item, then the new entry
//     has been inserted at the front of the sequenceDynamic. In either case, the newly
//     inserted item is now the current item of the sequenceDynamic.
//
void sequenceDynamic::insert(const value_type& entry) {

	//if at capacity, add additional memory
	if (used == capacity)
		resize(used + 1);
	//if no current item, set current_index to the front
	if (!(is_item()))
		current_index = 0;
	//shift items to make room
	for (size_type i = used; i > current_index; i--)
	{
		data[i] = data[i - 1];
	}
	data[current_index] = entry;
	++used;
	
		
	
}

//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequenceDynamic after
//     the current item. If there was no current item, then the new entry has
//     been attached to the end of the sequenceDynamic. In either case, the newly
//     inserted item is now the current item of the sequenceDynamic.
//
void sequenceDynamic::attach(const value_type& entry) {
	// add additional memory if at capacity
    if (used >= capacity)
        resize (1 + used + used/10); // Increase by 10%
	// If there is no current item,
	// add item at end of sequence
    if (!is_item())
    {
        current_index = used;
        data[current_index] = entry;
    }
    else // There is a current item
    {
		// so move items over to make room
        for(size_type i = used; i > (current_index + 1); i--)
            data[i] = data[i-1];
		// insert item after current_index
        data[current_index + 1] = entry;
		// increment current_index
        current_index++;
    }
	// increment number of items used
	used++;
}

//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequenceDynamic, and the
//     item after this (if there is one) is now the new current item.
//
void sequenceDynamic::remove_current() {
	// ensure that current_index is valid
    assert(is_item());
	// remove item at current_index by shifting items over
    for(size_type i = current_index; i < used-1; i++)
        data[i] = data[i+1];
	// decrement number of items used
    used--;
}

//   bool erase_one(const value_type& entry)
//     Precondition: used > 0
//     Postcondition: If entry was in the sequenceDynamic,
//     then one copy has been removed; otherwise the
//     sequenceDynamic is unchanged.  A true return value
//     indicates that the first copy was removed;
//     false indicates that nothing was removed.
//     Current item is set to first item in sequenceDynamic.
bool sequenceDynamic::erase_one(const value_type& entry) {

	// use flag to keep track of whether item is removed
	bool found = false;
	for (size_type i = 0; i < used; i++)
		// see if item in array and value equal to entry
		if (data[i] == entry) {
			//if found return true
			found = true;
			//set current_index to first item
			current_index = 0;
			//remove item by using the function remove_current();
			remove_current();
			break;
		}


	return found;
}

// Overloaded = operator (as member function)
void sequenceDynamic::operator =(const sequenceDynamic& source) {
	
	value_type* new_data;
	//check for self assignment
	if (this == &source)
		return;
	if (capacity != source.capacity)
	{
		//allocate new memory
		new_data = new value_type[source.capacity];
		//release old memory
		delete[] data;
		//asssign new memory
		data = new_data;
		//new capacity
		capacity = source.capacity;
	}
	used = source.used;
	//set new current_index
	current_index = source.current_index;

	for (size_type i = 0; i < used; i++)
		new_data[i] = source.data[i];
}

// Overloaded += operator (as member function)
void sequenceDynamic::operator +=(const sequenceDynamic& addend) {
	// see if additional memory needed
	if((used + addend.used) > capacity)
		resize(used + addend.used);
	// copy items from addend to current
	size_type addUsed = addend.used;
	for (size_type i = 0; i < addUsed; ++i)
		data[used++] = addend.data[i];
}

// Overloaded + operator (as free function)
sequenceDynamic operator +(const sequenceDynamic& s1, const sequenceDynamic& s2) {
	// create new bagDynamic with size equal to sum of both bagDynamic parameters
	sequenceDynamic result(s1.size() + s2.size());
	// add items from first sequenceDynamic
	result += s1;
	// add items from first sequenceDynamic
	result += s2;
	return result;
}

/*
result 
==========>TEST RESULTS<==========
If you submit this sequenceDynamic class now, you will have
30 points out of the 30 points from this test program.
==========>POINT SUMMARY<==========
Testing insert, attach, and the constant member functions
		POINTS = 3 out of 3
Testing situations where the cursor goes off the sequenceDynamic
		POINTS = 0 out of 0
Testing remove_current member function
		POINTS = 0 out of 0
Testing the resize member function
		POINTS = 5 out of 5
Testing the copy constructor
		POINTS = 5 out of 5
Testing the assignment operator
		POINTS = 6 out of 6
Testing insert/attach when current DEFAULT_CAPACITY exceeded
		POINTS = 3 out of 3
Testing erase_one member function
		POINTS = 8 out of 8
*/