// FILE: sequenceFixed.h
// CLASS PROVIDED: sequenceFixed 
//
// TYPEDEFS and MEMBER CONSTANTS for the sequenceFixed class:
//   alias ____ value_type
//     sequenceFixed::value_type is the data type of the items in the sequenceFixed. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   alias ____ size_type
//     sequenceFixed::size_type is the data type of any variable that keeps track of
//     how many items are in a sequenceFixed.
//
//   static const size_type CAPACITY = _____
//     sequenceFixed::CAPACITY is the maximum number of items that a sequenceFixed can hold.
//

// Taken from Data Structures and Other Objects 
// Using C++ by Michael Main and Walter Savitch
// Modifications by CREngland

#ifndef MAIN_SAVITCH_sequenceFixed_H
#define MAIN_SAVITCH_sequenceFixed_H
#include <cstdlib>  // Provides size_t


class sequenceFixed
{
public:
    // aliases and MEMBER CONSTANTS
    using value_type = double;
    using size_type = std::size_t;
	static const size_type CAPACITY = 30;

    // CONSTRUCTOR  
    sequenceFixed( );

    // MODIFICATION MEMBER FUNCTIONS
    void start( );
    void advance( );
    void insert(const value_type& entry);
    void attach(const value_type& entry);
    void remove_current( );
	// remove first item if included**CRE**
	bool erase_one(const value_type& entry);

    // CONSTANT MEMBER FUNCTIONS
    size_type size( ) const;
    bool is_item( ) const;
    value_type current( ) const;

private:
	// relevant items in data[0] to data[used-1]
    value_type data[CAPACITY];
	// number of items stored
    size_type used;
	// current item's reference
    size_type current_index;
};
#endif

