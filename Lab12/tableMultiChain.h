/*
	Name:	Dawid Jasionowski
	Date:	11/29/2018
	File:   tableMultiChain.h
	Descr:
	Derived template class (from tableChain) to allow multiple hash keys
	with different data values.
*/
#ifndef tableMultiChain_H
#define tableMultiChain_H
#include <cassert> 
#include <cstdlib> // Provides size_t
#include "tableChain.h" // Provides base hash table class with chaining
#include "hashNodeToolkit.h"

using namespace std;

// derived template class
template <class RecordType>
class tableMultiChain : public tableChain <RecordType> {
public:
	// override base class method since duplicates allowed
	// add entry at *end* of duplicate keys
	void insert(const RecordType& entry) override;
	// additional method to count number of entries for given key
	size_t count(int key) const;
	// additional method to display all entries for given key
	void display_key_values(int key) const;
	// additional method to remove all entries for given key
	void remove_all(int key);
};

// ***ADD METHOD DEFINITIONS HERE***
template <class RecordType>
void tableMultiChain<RecordType>::insert(const RecordType& entry) {
	hashNode<RecordType>* cursor;


	assert(entry.key >= 0);

	cursor = this->find_node(entry.key);

	if (cursor != nullptr) {
		list_insert(cursor, entry);
	}
	else {
		list_head_insert(this->data[this->hash_func(entry.key)], entry);

	}

	this->total_records++;
}



template <class RecordType>
size_t tableMultiChain<RecordType>::count(int key) const {
	hashNode<RecordType>* cursor;
	size_t answer = 0;
	cursor = this->find_node(key);
	while ((cursor != nullptr))
	{
		if (((cursor->data).key == key))
			answer++;
		cursor = cursor->link;

	}

	return answer;
}


template <class RecordType>
void tableMultiChain<RecordType>::display_key_values(int key) const {
	hashNode<RecordType>* cursor;
	

	cursor = this->find_node(key);
	
		while (cursor != nullptr)
		{
			cout << "Displaying key " << key << " values:" << endl;

			for (cursor; cursor != nullptr; cursor = cursor->link)

				cout << '\t' << cursor->data << endl;


		}
	
}

template <class RecordType>
void tableMultiChain<RecordType>::remove_all(int key) {
	hashNode<RecordType> *cursor;
	assert(key >= 0);
	cursor = this->find_node(key);
	while (cursor != nullptr)
	{

		this->remove(key);
		cursor = this->find_node(key);
	}
}
#endif

/*
sample output
Starting table size is 12

***DISPLAY ALL TABLE ENTRIES***
Index = 0
		KEY=811 DATA=100
Index = 1
		KEY=1623 DATA=11
		KEY=1 DATA=11.1
		KEY=1 DATA=11.3
		KEY=1 DATA=11.2
		KEY=5678 DATA=11.4
Index = 2
		KEY=2435 DATA=22
		KEY=2 DATA=22.1
		KEY=2 DATA=22.2
Index = 3
		KEY=3 DATA=33.1
		KEY=3 DATA=33.2
		KEY=4058 DATA=33.9

***TEST CASE #1***
		-->no matching key
		-->removing 0 links; KEY = 0

		-->SUCCESS: table size is now 12

***DISPLAY ALL TABLE ENTRIES***
Index = 0
		KEY=811 DATA=100
Index = 1
		KEY=1623 DATA=11
		KEY=1 DATA=11.1
		KEY=1 DATA=11.3
		KEY=1 DATA=11.2
		KEY=5678 DATA=11.4
Index = 2
		KEY=2435 DATA=22
		KEY=2 DATA=22.1
		KEY=2 DATA=22.2
Index = 3
		KEY=3 DATA=33.1
		KEY=3 DATA=33.2
		KEY=4058 DATA=33.9

***TEST CASE #2***
		-->one matching key
		-->removing 1 links; KEY = 811
Displaying key 811 values:
		KEY=811 DATA=100

		-->SUCCESS: table size is now 11

***DISPLAY ALL TABLE ENTRIES***
Index = 1
		KEY=1623 DATA=11
		KEY=1 DATA=11.1
		KEY=1 DATA=11.3
		KEY=1 DATA=11.2
		KEY=5678 DATA=11.4
Index = 2
		KEY=2435 DATA=22
		KEY=2 DATA=22.1
		KEY=2 DATA=22.2
Index = 3
		KEY=3 DATA=33.1
		KEY=3 DATA=33.2
		KEY=4058 DATA=33.9

***TEST CASE #3***
		-->three matching keys from middle
		-->removing 3 links; KEY = 1
Displaying key 1 values:
		KEY=1 DATA=11.1
		KEY=1 DATA=11.3
		KEY=1 DATA=11.2
		KEY=5678 DATA=11.4

		-->SUCCESS: table size is now 8

***DISPLAY ALL TABLE ENTRIES***
Index = 1
		KEY=1623 DATA=11
		KEY=5678 DATA=11.4
Index = 2
		KEY=2435 DATA=22
		KEY=2 DATA=22.1
		KEY=2 DATA=22.2
Index = 3
		KEY=3 DATA=33.1
		KEY=3 DATA=33.2
		KEY=4058 DATA=33.9

***TEST CASE #4***
		-->two matching keys from end
		-->removing 2 links; KEY = 2
Displaying key 2 values:
		KEY=2 DATA=22.1
		KEY=2 DATA=22.2

		-->SUCCESS: table size is now 6

***DISPLAY ALL TABLE ENTRIES***
Index = 1
		KEY=1623 DATA=11
		KEY=5678 DATA=11.4
Index = 2
		KEY=2435 DATA=22
Index = 3
		KEY=3 DATA=33.1
		KEY=3 DATA=33.2
		KEY=4058 DATA=33.9

***TEST CASE #5***
		-->two matching keys from beginning
		-->removing 2 links; KEY = 3
Displaying key 3 values:
		KEY=3 DATA=33.1
		KEY=3 DATA=33.2
		KEY=4058 DATA=33.9

		-->SUCCESS: table size is now 4

***DISPLAY ALL TABLE ENTRIES***
Index = 1
		KEY=1623 DATA=11
		KEY=5678 DATA=11.4
Index = 2
		KEY=2435 DATA=22
Index = 3
		KEY=4058 DATA=33.9

C:\Users\dawid\source\repos\LabTest\Debug\LabTest.exe (process 7356) exited with code 0.
Press any key to close this window . . .


*/
