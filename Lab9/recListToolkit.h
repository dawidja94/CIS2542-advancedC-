/*
Author:		Dawid Jasionowski
Date:		10/31/2018
File:		recListToolkit.h
Descr:

Lab9 recursive toolkit function for template
based class
*/



#include "nodeTemplate.h"
#include <iostream>
using namespace std;

template<class Item>
void rec_display_list(const nodeTemplate<Item>* head_ptr) {
	if (head_ptr != nullptr) {
		cout << head_ptr->data() << endl;
		rec_display_list(head_ptr->link());
	}
}

template<class Item>
void rev_display_list(const nodeTemplate<Item>* head_ptr) {

	if(head_ptr != nullptr) {
		rev_display_list(head_ptr->link());   //recursive call first
		cout << head_ptr->data() << endl;
		
	}
}

template<class Item>
std::size_t rec_list_length(const nodeTemplate<Item>* head_ptr) {
	
	if (head_ptr == nullptr)
		return 0;


	else
		return 1 + rec_list_length(head_ptr->link());
	
	
}
template<class Item>
void rec_list_clear(nodeTemplate<Item>*& head_ptr) {

	if (head_ptr == nullptr)
		return;		//return if empty
	if (head_ptr != nullptr) {

		list_head_remove(head_ptr);
		rec_list_clear(head_ptr);
		
	}
}

template <class nodeTemplatePtr, class Item>
nodeTemplatePtr rec_list_search(nodeTemplatePtr head_ptr, const Item& target) {

	//if empty
	if (head_ptr == nullptr)
		return 0;

	if (head_ptr->data() == target) {

		return head_ptr;
	}
		
	else {
		return rec_list_search(head_ptr->link(), target);

	}
	
	
		
	
		

	

}
/*sample run
The number of items in list is 5
List items in order:
11.1
77.7
22.2
33.3
5.5
List items in reverse order:
5.5
33.3
22.2
77.7
11.1

Searching with recursive function...
Input a  value to search (0 to end): 11.1
11.1 has been found!
Input a  value to search (0 to end): 22.2
22.2 has been found!
Input a  value to search (0 to end): 5.5
5.5 has been found!
Input a  value to search (0 to end): -3.2
-3.2 has NOT been found!
Input a  value to search (0 to end): 0

C:\Users\dawid\source\repos\Project7\Debug\Project7.exe (process 13904) exited with code 0.
Press any key to close this window . .
*/


#pragma once
