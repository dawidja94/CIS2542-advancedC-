// FILE: sequenceList.h
// CLASS PROVIDED: sequenceList 
// This is the header file for the project described in Section 5.4
// of "Data Structures and Other Objects Using C++"
// This is called "sequenceList" because some students already implemented
// sequenceFixed (with a fixed array) and sequenceDynamic (with a dynamic array).
//
// ALIASES and MEMBER CONSTANTS for the sequenceList class:
//   alias ____ value_type
//     sequenceList::value_type is the data type of the items in the sequenceList. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   alias ____ size_type
//     sequenceList::size_type is the data type of any variable that keeps track of
//     how many items are in a sequenceList.
//

// VALUE SEMANTICS for the sequenceList class:
//    Assignments and the copy constructor may be used with sequenceList objects.

#ifndef MAIN_SAVITCH_sequenceList_H
#define MAIN_SAVITCH_sequenceList_H
#include <cstdlib>  // Provides size_t
#include "node.h"  // Provides node class

class sequenceList
{
public:
	// ALIASES
	using value_type = node::value_type;
	using size_type = std::size_t;

	// CONSTRUCTORS and DESTRUCTOR
	sequenceList();
	sequenceList(const sequenceList& source);
	~sequenceList();

	// CONSTANT MEMBER FUNCTIONS
	//   size_type size( ) const
	//     Postcondition: The return value is the number of items in the sequenceList.
	//
	size_type size() const { return many_nodes; }

	//   bool is_item( ) const
	//     Postcondition: A true return value indicates that there is a valid
	//     "f" item that may be retrieved by activating the current
	//     member function (listed below). A false return value indicates that
	//     there is no valid current item.
	//
	bool is_item() const { return (cursor != nullptr); }
	value_type current() const;

	
	// MODIFICATION MEMBER FUNCTIONS
	void start();
	void advance();
	void insert(const value_type& entry);
	void attach(const value_type& entry);
	void remove_current();
	bool erase_one(const value_type& entry);
	void operator =(const sequenceList& source);
	void operator +=(const sequenceList& addend);

private:
	node *head_ptr;
	node *tail_ptr;
	node *cursor;
	node *precursor;
	size_type many_nodes;
};

sequenceList operator +(const sequenceList& s1, const sequenceList& s2); 

#endif

