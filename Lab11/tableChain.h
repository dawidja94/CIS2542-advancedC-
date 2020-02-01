// FILE: tableChain.h
//Author:		Dawid Jasionowski
//Date:			11/15/2018

// TEMPLATE CLASS PROVIDED: tableChain<RecordType>
//   This class is a container template class for a Table of records.
//   The template parameter, RecordType, is the data type of the records in the
//   Table. It may any type with a default constructor, a copy constructor,
//   an assignment operator, and an integer member variable called key.

// INVARIANT for the Table ADT:
//   1. The number of records in the Table is in the member variable
//      total_records.
//   2. The actual records of the table are stored in a chained hash table.
//      An entry with key i is stored on the linked list with the head
//

// VALUE SEMANTICS for the tableChain<RecordType> template class:
//   Assignments and the copy constructor may be used with Table objects.
//
// DYNAMIC MEMORY USAGE by the tableChain<RecordType> template class:
//   If there is insufficient dynamic memory, then the following functions
//   can call new_handler: the copy constructor, insert, the assignment
//   operator.

#ifndef tableChain_H
#define tableChain_H
#include <cstdlib>    // Provides size_t
#include "hashNodeToolkit.h"    // Provides the hashNode struct and toolkit

template <class RecordType>
class tableChain
{
public:
	// MEMBER CONSTANT
	static const std::size_t TABLE_SIZE = 811;

	// CONSTRUCTORS AND DESTRUCTOR
	tableChain();
	tableChain(const tableChain& source);
	~tableChain();

	// CONSTANT MEMBER FUNCTIONS
	bool is_present(int key) const;
	//   size_t size( ) const
	//     Postcondition: Return value is the total number of records in the
	//     Table.
	//
	void find(int key, bool& found, RecordType& result) const;
	std::size_t size() const { return total_records; }

	// MODIFICATION MEMBER FUNCTIONS
	void insert(const RecordType& entry);
	void remove(int key);
	void operator =(const tableChain& source);

	// **DISPLAY MEMBER FUNCTION**
	void display_all();

private:
	// MEMBER VARIABLES
	hashNode<RecordType> *data[TABLE_SIZE];
	std::size_t total_records;

	// HELPER FUNCTIONS
	std::size_t hash(int key) const;
	hashNode<RecordType>* find_node(int key) const;
};

// HELPER FUNCTIONS
// hash function to return integer index for given key
template <class RecordType>
size_t tableChain<RecordType>::hash(int key) const {
	return (key % TABLE_SIZE);
}

// Postcondition: The return value is a pointer to the record with the
// specified key (if there is one). If there is no such hashNode, the return value
// is the nullptr pointer.
template <class RecordType>
hashNode<RecordType>* tableChain<RecordType>::find_node(int key) const {
	hashNode<RecordType>* cursor;

	cursor = data[hash(key)];
	while ((cursor != nullptr) && ((cursor->data).key != key))
		cursor = cursor->link;

	return cursor;
}

// CONSTRUCTOR for the tableChain<RecordType> template class:
//   tableChain( )
//     Postcondition: The Table has been initialized as an empty Table.
//
template <class RecordType>
tableChain<RecordType>::tableChain() {
	size_t i;

	total_records = 0;
	for (i = 0; i < TABLE_SIZE; i++)
		data[i] = nullptr;
}

// COPY CONSTRUCTOR for the tableChain<RecordType> template class:
//   tableChain(const tableChain<RecordType>&)
//     Postcondition: The Table has been initialized to a copy of
//     the passed tableChain table.
//
template <class RecordType>
tableChain<RecordType>::tableChain(const tableChain<RecordType>& source) {
	size_t i;
	hashNode<RecordType>* tail_ptr; // Needed for list_copy

	for (i = 0; i < TABLE_SIZE; i++)
		list_copy(source.data[i], data[i], tail_ptr);
	total_records = source.total_records;
}

// DESTRUCTOR for the tableChain<RecordType> template class:
//   ~tableChain( )
//     Postcondition: All table entries have been returned to
//     the heap.
//
template <class RecordType>
tableChain<RecordType>::~tableChain() {
	size_t i;

	total_records = 0;
	for (i = 0; i < TABLE_SIZE; i++)
		list_clear(data[i]);
}

// CONSTANT MEMBER FUNCTIONS for the tableChain<RecordType> class:
//   bool is_present(const Item& target) const
//     Postcondition: The return value is true if there is a record in the
//     Table with the specified key. Otherwise, the return value is false.
//
template <class RecordType>
bool tableChain<RecordType>::is_present(int key) const {
	assert(key >= 0);

	return (find_node(key) != nullptr);
}

//   void find(int key, bool& found, RecordType& result) const
//     Postcondition: If a record is in the Table with the specified key, then
//     found is true and result is set to a copy of the record with that key.
//     Otherwise found is false and the result contains garbage.
//
template <class RecordType>
void tableChain<RecordType>::find(int key, bool& found, RecordType& result) const {
	hashNode<RecordType> *cursor;

	cursor = find_node(key);
	found = (cursor != nullptr);
	if (found)
		result = cursor->data;
}

// MODIFICATION MEMBER FUNCTIONS
//   void insert(const RecordType& entry)
//     Precondition: entry.key >= 0. Also if entry.key is not already a key in
//     the table, then the Table has space for another record
//     (i.e., size( ) < CAPACITY).
//     Postcondition: If the table already had a record with a key equal to
//     entry.key, then that record is replaced by entry. Otherwise, entry has
//     been added as a new record of the Table.
//
template <class RecordType>
void tableChain<RecordType>::insert(const RecordType& entry) {
	hashNode<RecordType>* cursor; // set to point to existing hashNode with given key

	assert(entry.key >= 0);

	// Set cursor to point to existing hashNode with given key (if there is one)
	cursor = find_node(entry.key);
	if (cursor != nullptr) {   
		// Add in existing spot
		cursor->data = entry;
	}
	else {   
		// Add in a new spot
		list_head_insert(data[hash(entry.key)], entry);
		total_records++;
	}
}

//   void remove(int key)
//     Postcondition: If a record was in the Table with the specified key, then
//     that record has been removed; otherwise the table is unchanged.
//
template <class RecordType>
void tableChain<RecordType>::remove(int key) {

	assert(key >= 0);
	hashNode<RecordType>* cursor;
	int index = hash(key);
	cursor = data[index];
	hashNode<RecordType>* prev = nullptr;
	while (cursor != nullptr)
	{
		if ((cursor->data).key == key)
		{
			if (prev == nullptr)
			{
				data[index] = cursor->link;
			}
			else
			{
				prev->link = cursor->link;
			}
			this->total_records--;
			delete cursor;
			return;
		}
		prev = cursor;
		cursor = cursor->link;
	}
}

template <class RecordType>
void tableChain<RecordType>::operator =(const tableChain<RecordType>& source) {
	size_t i;
	hashNode<RecordType>* tail_ptr; // Needed for list_copy

	if (this == &source)
		return; // Avoid self-assignment

	for (i = 0; i < TABLE_SIZE; i++) {
		list_clear(data[i]);
		list_copy(source.data[i], data[i], tail_ptr);
	}
	total_records = source.total_records;
}

// **DISPLAY MEMBER FUNCTION**
template <class RecordType>
void tableChain<RecordType>::display_all() {
	std::cout << "\n\n***DISPLAY ALL TABLE ENTRIES***" << std::endl;
	// loop through each array element
	for (size_t i = 0; i < TABLE_SIZE; i++) {
		// see if element not empty
		if (data[i] != nullptr) {
			std::cout << "Index = " << i << std::endl;
			// display all values in location
			for (hashNode<RecordType>* cursor = data[i]; cursor != nullptr; cursor = cursor->link) {
				std::cout << '\t' << cursor->data << std::endl;
			}
		}
	}
}


/*
output

The table size is 9

***DISPLAY ALL TABLE ENTRIES***
Index = 0
        KEY=811 DATA=100
Index = 1
        KEY=5678 DATA=11.1
        KEY=3245 DATA=11.2
        KEY=1623 DATA=11.3
        KEY=1 DATA=11.4
Index = 2
        KEY=2435 DATA=22.1
        KEY=2 DATA=22.2
Index = 3
        KEY=3 DATA=33.1
        KEY=4058 DATA=33.2

-->removing no link: key 0
-->SUCCESS: no change in size 9

-->removing only link: key 811
-->SUCCESS: table size is 8

***DISPLAY ALL TABLE ENTRIES***
Index = 1
        KEY=5678 DATA=11.1
        KEY=3245 DATA=11.2
        KEY=1623 DATA=11.3
        KEY=1 DATA=11.4
Index = 2
        KEY=2435 DATA=22.1
        KEY=2 DATA=22.2
Index = 3
        KEY=3 DATA=33.1
        KEY=4058 DATA=33.2

-->removing middle link: 3245
-->SUCCESS: table size is 7

***DISPLAY ALL TABLE ENTRIES***
Index = 1
        KEY=5678 DATA=11.1
        KEY=1623 DATA=11.3
        KEY=1 DATA=11.4
Index = 2
        KEY=2435 DATA=22.1
        KEY=2 DATA=22.2
Index = 3
        KEY=3 DATA=33.1
        KEY=4058 DATA=33.2

-->removing last link: key 2
-->SUCCESS: table size is 6

***DISPLAY ALL TABLE ENTRIES***
Index = 1
        KEY=5678 DATA=11.1
        KEY=1623 DATA=11.3
        KEY=1 DATA=11.4
Index = 2
        KEY=2435 DATA=22.1
Index = 3
        KEY=3 DATA=33.1
        KEY=4058 DATA=33.2

-->removing first link: key 3
-->SUCCESS: table size is 5

***DISPLAY ALL TABLE ENTRIES***
Index = 1
        KEY=5678 DATA=11.1
        KEY=1623 DATA=11.3
        KEY=1 DATA=11.4
Index = 2
        KEY=2435 DATA=22.1
Index = 3
        KEY=4058 DATA=33.2

C:\Users\dawid\Desktop\Project1\Debug\Project1.exe (process 12324) exited with code 0.
Press any key to close this window . . .



*/
#endif
