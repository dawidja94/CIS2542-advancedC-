// FILE: sequenceDynamic.h
// CLASS PROVIDED: sequenceDynamic (part of the namespace main_savitch_4)
// There is no implementation file provided for this class since it is
// an exercise from Chapter 4 of "Data Structures and Other Objects Using C++"
//
// ALIASES and MEMBER CONSTANTS for the sequenceDynamic class:
//   alias ____ value_type
//     sequenceDynamic::value_type is the data type of the items in the sequenceDynamic. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   alias ____ size_type
//     sequenceDynamic::size_type is the data type of any variable that keeps track of
//     how many items are in a sequenceDynamic.
//
//   static const size_type DEFAULT_CAPACITY = _____
//     sequenceDynamic::DEFAULT_CAPACITY is the initial capacity of a sequenceDynamic that is
//     created by the default constructor.
//

// DYNAMIC MEMORY USAGE by the List
//   If there is insufficient dynamic memory, then the following functions
//   throw a BAD_ALLOC exception: The constructors, insert, attach.

#ifndef MAIN_SAVITCH_sequenceDynamic_H
#define MAIN_SAVITCH_sequenceDynamic_H
#include <cstdlib>  // Provides size_t

class sequenceDynamic
{
public:
    // ALIAS and MEMBER CONSTANTS
    using value_type = double;
    using size_type = std::size_t;
    static const size_type DEFAULT_CAPACITY = 30;

    // CONSTRUCTORS and DESTRUCTOR
    sequenceDynamic(size_type initial_capacity = DEFAULT_CAPACITY);
    sequenceDynamic(const sequenceDynamic& source);
	~sequenceDynamic( );

	// CONSTANT MEMBER FUNCTIONS
	size_type size() const;
	bool is_item() const;
	value_type current() const;

    // MODIFICATION MEMBER FUNCTIONS
	void resize(size_type new_capacity);
    void start( );
    void advance( );
    void insert(const value_type& entry);
    void attach(const value_type& entry);
    void remove_current( );
	bool erase_one(const value_type& entry);
    void operator =(const sequenceDynamic& source);
	void operator +=(const sequenceDynamic& addend);

private:
    value_type* data;
    size_type used;
    size_type current_index;
	size_type capacity;
};
	
sequenceDynamic operator +(const sequenceDynamic& s1, const sequenceDynamic& s2); // added this overloaded operator

#endif

